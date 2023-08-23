#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>

#include "includes/baseUser.h"

using namespace std ;

const int securityLevel {1} ;

BaseUser::BaseUser()
{
    //empty
}

void BaseUser::readFromFile(int id)
{
    ifstream input("user"+ to_string(id) +".txt",ios::in);
    if(!input)
        cout << "BaseUser::readFromFile->cant't open user"+ to_string(id) +".txt\n";
    else
        readFromFile(input);

    input.close();

    clearCurrentTweet();

    int inputId {0};

    ifstream followingsFile("user"+ to_string(id) +"followings.txt",ios::in);
    if(!followingsFile)
        cerr << "BaseUser::readFromFile->cant't open user"+ to_string(id) +"followings.txt\n";

    while(followingsFile>>inputId)
        followings.insert(inputId);

    followingsFile.close();

    ifstream followersFile("user"+ to_string(id) +"followers.txt",ios::in);
    if(!followersFile)
        cerr << "BaseUser::readFromFile->cant't open user"+ to_string(id) +"followers.txt\n";

    while(followersFile>>inputId)
        followers.insert(inputId);

    followersFile.close();

}
void BaseUser::readFromFile(ifstream& input)
{
    std::cerr << "BaseUser::readFromFile->start\n";
    std::string temp;

    input >> temp;  id        =stoi (temp.substr(1));
    input >> temp;  setFirsrName    (temp.substr(1));
    input >> temp;  setUserName     (temp.substr(1));
    input >> temp;  setPassword     (temp.substr(1));
    input >> temp;  setLastPass     (temp.substr(1));
    input >> temp;  setPhoneNum     (temp.substr(1));
    input >> temp;  setBiography    (temp.substr(1));
    input >> temp;  setLink         (temp.substr(1));
    input >> temp;  setCountry      (temp.substr(1));
    input >> temp;  setHeaderColor  (temp.substr(1));
    input >> temp;  allTweets = stoi(temp.substr(1));
    input >> temp;  setProfilePic   (temp.substr(1));
    input >> temp;  setBirthDate    (temp.substr(1));

    try
    {
        setTweet(currentTweetNum);
    }
    catch (...)
    {
        cerr << "user : '" << userName << "' has no Tweet\n" ;
    }

    std::cerr << "BaseUser::readFromFile->end\n";
}
BaseUser::BaseUser(string name, string uName, string pass,string phone)
{
    setFirsrName(name) , setUserName(uName) , setPassword(pass) , setPhoneNum(phone);
}
void BaseUser::setId (int input)
{
    id = input ;
}
void BaseUser::setFirsrName(string fName)
{
    if(fName.size() == 0)
        throw invalid_argument("Name can't be empty");
    for(const auto& i: fName)
    {
        if(i == ' ')
            throw invalid_argument("Name containt space");
    }
    firsName = fName;
}
void BaseUser::setUserName(string uName)
{

    if (uName.size() < 5)
        throw invalid_argument("! Username is to short");


    for (size_t i = 0; i < uName.size(); ++i) //get without @
    {
        if ( !('a' <= uName[i] && uName[i] <= 'z') &&
             !('A' <= uName[i] && uName[i] <= 'Z')) 
        {
            throw invalid_argument("! Username contain invalid character");
        }
    }

    string reservedWord[]{ "exit","edit","help","login","logout","profile","signup","tweet"}; //sort string for binery search and add more

    for(const string& i : reservedWord)
    {
        if(i == uName)
            throw invalid_argument("! You can't use reserved key");
    }

    userName = uName;
}

void BaseUser::setPassword(string pass) 
{
    if(pass != password)
        if (pass == previousPassword)
            throw invalid_argument("! You can not use your previous password");

    bool isCaptal {0} ; bool isSmall  {0} ;
    bool isNumber {0} ; bool isChar   {0} ;
    bool longPas  {pass.size()>8 ? true : false };

    for(size_t i {0} ; i < pass.size() ; ++i)
    {
        if     ('a' <= pass[i] && pass[i] <='z') isSmall  = true ;
        else if('0' <= pass[i] && pass[i] <='9') isNumber = true ;
        else if('A' <= pass[i] && pass[i] <='Z') isCaptal = true ;
        else                                     isChar   = true ;
    }

    if(isCaptal+isChar+isSmall+isNumber+longPas > securityLevel) //const int define in class defenition
    {
        setLastPass(password);
        password = pass ;
    }
    else
        throw invalid_argument("! Password is too easy") ;
    
}
void BaseUser::setLastPass(string input)
{
    previousPassword = input ;
}
void BaseUser::setBiography(string bio)
{
    if (bio.size() < 160)
        biography = bio;
    else
        throw invalid_argument("! Len of biography is too long...");
}
void BaseUser::setCountry(string country)
{
    this->country = country;
}
void BaseUser::setLink(string inputLink)
{
    if (inputLink.find("https://") == string :: npos)
    {
        link = "https://" + inputLink;
    }
    else
    {
        link = inputLink;
    }

}
void BaseUser::setPhoneNum(string phone)
{
    for (size_t i = 0 ; i < phone.size() ; ++i)
    {
        if (!(phone[i] >= '0' && phone[i] <= '9'))
        {
            throw invalid_argument ("! You most enter a number");
        }
    }
    phoneNumber = phone;
}

void BaseUser::setBirthDate(string inputDate)
{
    if(inputDate.size()>0)
        birthDate.setDate(inputDate);
    else
        cerr << "bitrhday dosen't exist\n";
}

void BaseUser::setHeaderColor(string inputColor)
{
    string reservedColors[8] { "blue ","green ","red ","yellow ","black ","white ","orange ","purple " };
    for (int i = 0 ; i < 8 ; i++)
        if (reservedColors[i] == inputColor)
             throw invalid_argument ("! Your color does not exist");
    headerColor = inputColor;
    
}

void BaseUser::setProfilePic(string inputFileAddress)
{
    profilePic = inputFileAddress;
}

BaseUser::~BaseUser()
{
    clearCurrentTweet();
}


void BaseUser::addTweet (string tweetText,TweetInfo retweetFrom)
{

    //tweetsSet.insert(tweetsSet.size()+1);
    cerr << "BaseUser::addTweet->add tweet " << allTweets << " to " << userName << '\n' ;
    currenTweet = new Tweet(tweetText,id,allTweets,retweetFrom);
    ++allTweets;
    save();
}
void BaseUser::clearCurrentTweet()
{
    delete currenTweet;
    currenTweet = nullptr ;
}
bool BaseUser::canShowNextTweet()
{
    return currentTweetNum < allTweets - 1;
}

bool BaseUser::canShowLastTweet()
{
    return currentTweetNum > 1 ;
}
void BaseUser::goToNextTweet   ()
{
    if(canShowNextTweet())
    {
        ++currentTweetNum;
        setTweet(currentTweetNum);
    }
    else
        throw out_of_range("! There is no next tweet");
}

void BaseUser::goToLastTweet()
{
    if(canShowLastTweet())
    {
        --currentTweetNum;
        setTweet(currentTweetNum);
    }
    else
        throw out_of_range("! There is no previous tweet");
}
Tweet* BaseUser::getTweet()
{
    if(currenTweet == nullptr)
    {
        setTweet(currentTweetNum);
    }

    return currenTweet;
}
void BaseUser::setTweet (int tweetId)
{
    if(tweetId < allTweets)
    {
        clearCurrentTweet();
        currenTweet = new Tweet (id,tweetId );
    }
    else
    {
        cerr << "BaseUser::setTweet->tweet don't exist\n";
        throw invalid_argument("BaseUser::setTweet->tweet dosen't exist");
    }


}

void BaseUser::save()
{
    clearCurrentTweet();

    ofstream output("user"+ to_string(id) +".txt",ios::out);
    if(!output)
        cerr << "Base::save->cant't open user"+ to_string(id) +".txt\n";

    output << this->getInfo();
    output.close();

    ofstream followingsFile("user"+ to_string(id) +"followings.txt",ios::out);
    if(!followingsFile)
        cerr << "Base::save->cant't open user"+ to_string(id) +"followings.txt\n";

    for(const auto& i : followings)
        followingsFile << i << ' ';

    followingsFile.close();

    ofstream followersFile("user"+ to_string(id) +"followers.txt",ios::out);
    if(!followersFile)
        cerr << "Base::save->cant't open user"+ to_string(id) +"followers.txt\n";

    for(const auto& i : followers)
        followersFile << i << ' ';

    followersFile.close();
}
string BaseUser::getInfo()
{
    ostringstream output ;

    output <<":"   << id                << "\n:" << firsName
           <<"\n:" << userName          << "\n:" << password
           <<"\n:" << previousPassword  << "\n:" << phoneNumber
           <<"\n:" << biography         << "\n:" << link
           <<"\n:" << country           << "\n:" << headerColor
           <<"\n:" << allTweets         << "\n:" << profilePic
           <<"\n:" << birthDate.getDateStr();

    return output.str();
}
void BaseUser::addFollowings(int id)
{
    if(followings.count(id))
        followings.erase(id);
    else
        followings.insert(id);
}
void BaseUser::addFollowers (int id)
{
    if(followers.count(id))
        followers.erase(id);
    else
        followers.insert(id);
}
bool BaseUser::isFollow(int id)
{
    return followings.count(id);
}
void BaseUser::likeBy (int id)
{
    currenTweet->addLike(id);
}
void BaseUser::setCurTweetNum(int input)
{
    if(!( 0 < input && input < allTweets))
        throw out_of_range("can't set current Tweet");

    currentTweetNum = input;
}
