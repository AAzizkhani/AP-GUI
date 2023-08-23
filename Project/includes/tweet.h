#ifndef TWEET_H
#define TWEET_H

#include <string>
#include <unordered_set>

#include "includes/tweetInfo.h"

class Tweet 
{
public:
    Tweet();
    Tweet(std::string,int,int,TweetInfo);
    Tweet(int,int);
    Tweet(TweetInfo);
    ~Tweet();

    void setTweetStr(std::string);
    void save ();
    void addLike(int);


    int getLikeNum ();
    int getTweetId ()                     const {return tweetId ;}
    int getUserId  ()                     const {return  userId ;}
    std::string getTweetStr()             const ;
    std::unordered_set<int> getLikeSet () const {return  likeSet;}
    std::unordered_set<int> getMentions() const {return  likeSet;}

    TweetInfo getTweetInfo();

private:

    int tweetId;
    int userId ;
    std::string tweetStr;
    TweetInfo retweetFrom;

    std::unordered_set<int> likeSet ;
    std::unordered_set<int> mentions;
};

#endif
