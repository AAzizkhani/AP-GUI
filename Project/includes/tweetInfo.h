#ifndef TWEETINFO_H
#define TWEETINFO_H

class Tweet;

class TweetInfo
{
public:
    TweetInfo(int u=0,int i=0)
    {setTweetInfo(u,i);}

    void setTweetInfo(int u=0,int i=0)
    {userId = u ; tweetId = i;}
//private:
    int userId ;
    int tweetId;
};

#endif // TWEETINFO_H
