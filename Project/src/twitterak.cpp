#include "includes/twitterak.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <stdio.h>

using namespace std;

Twitterak::Twitterak():mainUser{nullptr},tempUser{nullptr},numberOfUsers{0}
{
    getInfoHastagMap();
    ifstream input("main.txt",ios::in);
    if(!input)
        cerr << "Twitterak::Twitterak()->can't read\n";

    string userName,password ;
    int id ;
    char type ;
    while(input >> userName >> password >> id >> type)
    {
        usersMap[userName];
        usersMap[userName].password = password;
        usersMap[userName].id       = id ;
        usersMap[userName].type     = type;

        numberOfUsers = id > numberOfUsers ? id : numberOfUsers;
    }
    numberOfUsers++;
    input.close();
}
BaseUser* Twitterak::makeUser(string userName)
{
    BaseUser* tempPtr {nullptr};

    if(!usersMap.count(userName))
        throw invalid_argument("! User dosen't exist");
    else if(usersMap[userName].type == 'p')
        tempPtr =new PersonalUser    ;
    else if(usersMap[userName].type == 'a')
        tempPtr =new AnonymousUser   ;
    else if(usersMap[userName].type == 'o')
        tempPtr =new OrganisationUser;
    else
        throw invalid_argument ("file isn't corret ...main.txt");

    tempPtr->readFromFile(usersMap[userName].id);
    return tempPtr;
}
void Twitterak::setMainUser(string name   ,string userName,string password
                           ,string manager,string phone   ,char   type    )
{
    clearMainUser();

    if(usersMap.count(userName))//check user name
        throw invalid_argument("! Dublicated user name");

    if     (type == 'p')//creat personall user
    {
        mainUser =new PersonalUser(name,userName,password,phone);
    }
    else if(type == 'a')
    {
        mainUser =new AnonymousUser(userName,password);
    }
    else if(type == 'o')
    {
        if(!usersMap.count(manager))
            throw invalid_argument("! Manager user name dosen't exist niger");

        mainUser =new OrganisationUser(name,userName,password,phone,manager);
    }
    else
    {
        throw invalid_argument("! You haven't select a type");
    }

    mainUser->setId( numberOfUsers );
    usersMap[userName];
    usersMap[userName].password = password;
    usersMap[userName].id       = numberOfUsers ;
    usersMap[userName].type     = type;

    numberOfUsers++ ;
}
void Twitterak::loadMainUser(string userName,string password)
{
    clearMainUser();
    std::cerr << "Twitterak::loadMainUser->after clear try\n";
    if(!usersMap.count(userName))
        throw invalid_argument("! User name didn't found");
    else if(usersMap[userName].password != password)
        throw invalid_argument("! Incorect password");

    mainUser = makeUser(userName) ;
    std::cerr << "Twitterak::loadMainUser->after clear end\n";
}
void Twitterak::clearMainUser()
{
    //clog << "Twitterak::clearMainUser->start\n";
    if(mainUser != nullptr)
    {
        //clog << "Twitterak::clearMainUser->" << mainUser->getUserName() << " saved and pointer deleted\n";
        mainUser->save();
    }
    delete mainUser;
    mainUser = nullptr;
}
void Twitterak::deleteUser(string userName)
{
    int allTweets = mainUser->getAllTweets();
    clearMainUser();
    if(!usersMap.count(userName))
    {
        cerr << "Twitterak::deleteUser->can delete user name\n";
        throw invalid_argument("! User name don't exist");
    }
    int id = usersMap[userName].id;
    usersMap.erase(userName);
    string path = "user"+ to_string(id) +".txt";
    if(remove(path.data()) == 0)
    {
        cerr<< "delete " << path  << "line 114\n";
    }
    for(int i {1}; i < allTweets ; ++i)
    {
        path = "user"+ to_string(id) + "tweet" + to_string(i) +".txt";
        if(remove(path.data()) == 0)
        {
            cerr<< "delete " << path  << "line 123\n";
        }
    }

}
Twitterak::~Twitterak()
{
    saveHastagMap();
    ofstream output("main.txt",ios::out);
    if(!output)
        cerr << "cant't open main.txt \n";


    for (const auto& i : usersMap)
    {
        output << i.first       << ' ' << (i.second).password << ' '
               << (i.second).id << ' ' << (i.second).type     << '\n';
    }
    output.close();

    clearTempUser();
    clearMainUser();
}
void Twitterak::addTweet(string tweetText,TweetInfo retweetFrom)
{
    addHashtags(tweetText);
    mainUser->addTweet(tweetText,retweetFrom);
}
void Twitterak::loadTempUser (string userName)
{
    if(!usersMap.count(userName))
    {
        cerr << "Twitterak::loadTempUser->user name dont exist\n" ;
        throw invalid_argument("! User name don't exist");
    }

    clearTempUser();
    tempUser = makeUser(userName);

}
void Twitterak::clearTempUser()
{
    if(mainUser != tempUser && tempUser != nullptr)
    {
        tempUser->save();
        delete tempUser;
    }

    tempUser = nullptr;
}
void Twitterak::follow()
{
    if      (mainUser == nullptr) throw invalid_argument("main user dosen't exist") ;
    else if (tempUser == nullptr) throw invalid_argument("temp user dosen't exist") ;

    tempUser->addFollowers (mainUser->getId());
    mainUser->addFollowings(tempUser->getId());
}
bool Twitterak::isFollow()
{
    return mainUser->isFollow(tempUser->getId());
}
void Twitterak::like()
{
    if      (mainUser == nullptr) throw invalid_argument("main user dosen't exist") ;
    else if (tempUser == nullptr) throw invalid_argument("temp user dosen't exist") ;

    tempUser->likeBy(mainUser->getId());
}
char Twitterak::bringType(string userName)
{
    if(!usersMap.count(userName))
        throw invalid_argument ("user name dosen't exist");

    return usersMap[userName].type;
}
char Twitterak::bringType()
{
    if(mainUser == nullptr)
        throw invalid_argument("main user dosen't exist");
    return bringType(mainUser->getUserName());
}
vector<string> Twitterak::searchForHasgtags(string tweetText)
{
    vector<std::string>allHashtags;

    for(size_t i {0} ; i < tweetText.size() ; ++i)
    {
        if( tweetText[i] == '#')
        {
            string temp {};
            for(size_t j {i+1} ; j < tweetText.size() && canBeInHashtag(tweetText[j]) ; ++j)
            {
                temp += tweetText[j];
            }
            if(temp != "")
            {
                cerr << "Twitterak::searchForHasgtags->temp: " << temp << '\n';
                allHashtags.push_back(temp);
            }
        }
    }
    return allHashtags;
}
void Twitterak::addHashtags(string tweetText)
{
    if(mainUser == nullptr)
    {
        cerr << "Twitterak::addHashtags->main user is empty \n";
        throw invalid_argument("main user dosn't exist");
    }

    TweetInfo info(mainUser->getId(),mainUser->getAllTweets());
    vector<std::string>allHashtags = searchForHasgtags(tweetText);
    for(const auto& hastag :allHashtags)
    {
        hashtagsMap[hastag];
        hashtagsMap[hastag].push_back(info);
    }
}
bool Twitterak::canBeInHashtag(char input)
{
    if     ('a' < input && input < 'z' )
        return true ;
    else if('A' < input && input < 'Z' )
        return true ;
    else if( input == '_')
        return true ;

    return false;
}
void Twitterak::saveHastagMap ()
{
    ofstream output("hasgtag.txt",ios::out);
    if(!output)
        cerr << "cant't write hasgtag.txt \n";


    for (const auto& mapSlot : hashtagsMap)
    {
        output << mapSlot.first << ' ' ;
        for(const auto& i : mapSlot.second)
        {
            output << i.userId   << ' ' << i.tweetId  << ' ';
        }
        output << 0 << ' ' << 0 << '\n';
    }
    output.close();
}
void Twitterak::getInfoHastagMap()
{
    ifstream input("hasgtag.txt",ios::in);
    if(!input)
        cerr << "cant't read hasgtag.txt \n";

    string hashtag;
    while(input >> hashtag)
    {
        int userId , tweetId;
        hashtagsMap[hashtag];
        while(input >> userId >> tweetId && userId != 0)
        {
            TweetInfo tempInfoHolder(userId,tweetId);
            hashtagsMap[hashtag].push_back(tempInfoHolder) ;
        }
    }
    input.close();
}
void Twitterak::changeBoss(string bossUser)
{
    OrganisationUser* temp {nullptr};
    temp = dynamic_cast<OrganisationUser*>(mainUser);
    if(temp != nullptr)
    {
        std::clog << "Twitterak::changeBoss>active";
        if(!usersMap.count(bossUser) || usersMap[bossUser].type != 'o')
        {
            throw invalid_argument("manager dosen't exist");
        }
        temp->setBoss(bossUser);
    }
    else
    {
        throw invalid_argument("this account dosen't have this part");
    }
}
string Twitterak::getBoss(BaseUser* input)
{
    OrganisationUser* temp {nullptr};
    temp = dynamic_cast<OrganisationUser*>(input);
    if(temp != nullptr)
    {
        std::clog << "Twitterak::changeBoss>active";
        return temp->getBoss();
    }

    return "";
}
void Twitterak::changeCompany(string company)
{
    PersonalUser* temp {nullptr};
    temp = dynamic_cast<PersonalUser*>(mainUser);
    if(temp != nullptr)
    {
        if(!usersMap.count(company) || !(usersMap[company].type != 'o'))
        {
            throw invalid_argument("company dosen't exist");
        }
        temp->setBoss(company);
    }
    else
    {
        throw invalid_argument("this account dosen't have this part");
    }
}
string Twitterak::getCompany(BaseUser* input)
{
    PersonalUser* temp {nullptr};
    temp = dynamic_cast<PersonalUser*>(input);
    if(temp != nullptr)
    {
        return temp->getBoss();
    }

    return "";
}
void Twitterak::creatHashtagVec(string inputHashtag)
{
    if(!hashtagsMap.count(inputHashtag))
    {
        throw invalid_argument ("this hasgtag dosn't exist");
    }
    currentHashtagVec = hashtagsMap[inputHashtag];
    cerr << "\nvector" << currentHashtagVec.size() << endl ;
    setTempUserForHasgtag();
}
void Twitterak::goToNextHashtag()
{
    if(canShowNextHashtag())
    {
        ++hashTagIndex;
        setTempUserForHasgtag();
    }
    else
        throw out_of_range("! There is no next tweet");
}
void Twitterak::goToLastHashtag()
{
    if(canShowLastHashtag())
    {
        --hashTagIndex;
        setTempUserForHasgtag();
    }
    else
        throw out_of_range("! There is no last tweet");
}

bool Twitterak::canShowNextHashtag()
{
    return hashTagIndex < (int)currentHashtagVec.size() - 1 ;
}
bool Twitterak::canShowLastHashtag()
{
    return hashTagIndex > 0 ;
}
void Twitterak::setTempUserForHasgtag ()
{
    clearTempUser();
    BaseUser* tempUser = new BaseUser;
    tempUser->readFromFile(currentHashtagVec[hashTagIndex].userId);


    string userName = tempUser->getUserName();
    delete tempUser;

    loadTempUser(userName);
    this->tempUser->setCurTweetNum(currentHashtagVec[hashTagIndex].tweetId);
}
void Twitterak::ChangUserName(string input)
{
    if(input == mainUser->getUserName())
        return;
    if (usersMap.count(input))
        throw invalid_argument("Dublicated user name");

    string lastUserName = mainUser->getUserName();
    mainUser->setUserName(input);

    usersMap[input] = usersMap[lastUserName];
    usersMap.erase(lastUserName);

}
