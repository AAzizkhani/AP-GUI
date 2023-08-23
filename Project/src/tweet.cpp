#include "includes/tweet.h"
#include "includes/baseUser.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std ;
class BaseUser ;

Tweet::Tweet()
{
    //empty
}
Tweet::Tweet(string input,int userId ,int tweetId,TweetInfo retweetFrom)
{
    setTweetStr(input);
    this->tweetId     = tweetId;
    this->userId      = userId ;
    this->retweetFrom = retweetFrom;
}
Tweet::Tweet(int userId ,int tweetId)
{
    this->tweetId = tweetId;
    this->userId  = userId ;

    string path = "user" + to_string(userId) + "tweet" + to_string(tweetId) + ".txt";
    ifstream input (path,ios::in);

    if(!input)
    {
        cerr << path << "donsn't exist to read \n";
        throw out_of_range(path + "donsn't exist");
    }
    string inputTweet ;
    int userInfoId , tweetInfoId;
    input >> userInfoId >> tweetInfoId;
    cerr << "userInfoId " << userInfoId << "  tweetInfoId " << tweetInfoId  << endl ;

    retweetFrom.userId  = userInfoId;
    retweetFrom.tweetId = tweetInfoId;

    input >> inputTweet ;
    tweetStr  = inputTweet.substr(1);

    while(input >> inputTweet && inputTweet.size()>0 && inputTweet[0] != ':')
    {
        tweetStr += " " + inputTweet;
    }

    input.close();

    path = "user" + to_string(userId) + "tweet" + to_string(tweetId) + "like.txt";
    ifstream inputLike (path,ios::in);

    if(!inputLike)
    {
        cerr << path << "donsn't exist to read \n";
        throw out_of_range(path + "donsn't exist");
    }

    int inputId {};
    while(inputLike >> inputId)
        likeSet.insert(inputId);

    inputLike.close();
}
void Tweet::setTweetStr(string input)
{
    tweetStr = input ;
}
Tweet::~Tweet()
{
    save();
}
void Tweet::save ()
{
    string path = "user" + to_string(userId) + "tweet" + to_string(tweetId) + ".txt";
    ofstream file (path,ios::out);

    if(!file)
        cerr << "~Tweet():can't open and write in " << path << '\n' ;

    file << retweetFrom.userId << ' ' << retweetFrom.tweetId << "\n:" << tweetStr <<"\n";
    file.close();

    path = "user" + to_string(userId) + "tweet" + to_string(tweetId) + "like.txt";
    ofstream fileLike (path,ios::out);

    if(!fileLike)
        cerr << "~Tweet():can't open and write in " << path << '\n' ;

    for(const auto& i:likeSet)
        fileLike << i << ' ' ;

    fileLike.close();

}
void Tweet::addLike(int id)
{
    if(likeSet.count(id))
        likeSet.erase(id);
    else
        likeSet.insert(id);
}
int Tweet::getLikeNum ()
{
    return likeSet.size();
}
 TweetInfo Tweet::getTweetInfo()
{
    TweetInfo temp(userId,tweetId);
    return temp;
}
string Tweet::getTweetStr()const
{
    string tempTweetStr {};
    if(retweetFrom.userId != 0)
    {
        BaseUser* tempUser = new BaseUser;
        tempUser->readFromFile(retweetFrom.userId);
        tempTweetStr += "@" + tempUser->getUserName() + "\n";
        delete tempUser;

        Tweet* tempTweet = new Tweet(retweetFrom);
        tempTweetStr += tempTweet->getTweetStr();
        tempTweetStr += "\n****************\n";
        delete tempTweet;
    }

    tempTweetStr +=  tweetStr;

    return tempTweetStr;
}
Tweet::Tweet(TweetInfo t):Tweet(t.userId,t.tweetId)
{
    //empty
}
