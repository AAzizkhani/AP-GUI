#ifndef baseUser_H
#define baseUser_H

#include <unordered_set>
#include <string>
#include <fstream>

#include "includes/tweet.h"
#include "includes/Date.h"
#include "includes/tweetInfo.h"


class BaseUser 
{
public:
    BaseUser ();
    BaseUser (std::string, std::string, std::string,std::string);
    virtual ~BaseUser ();

    virtual void readFromFile(int);
    virtual void readFromFile(std::ifstream&);

    virtual void setId         (int);
    virtual void setCurTweetNum(int);
    virtual void setFirsrName  (std::string);
    virtual void setUserName   (std::string);
    virtual void setLink       (std::string);
    virtual void setPassword   (std::string);
    virtual void setLastPass   (std::string);
    virtual void setBiography  (std::string);
    virtual void setCountry    (std::string);
    virtual void setPhoneNum   (std::string);
    virtual void setBirthDate  (std::string);
    virtual void setProfilePic (std::string);
    virtual void setHeaderColor(std::string);

    virtual void addTweet      (std::string,TweetInfo);
    void clearCurrentTweet();

    void setTweet     (int);
    void goToNextTweet   ();
    void goToLastTweet   ();
    bool canShowNextTweet();
    bool canShowLastTweet();
    Tweet* getTweet      ();

    void addFollowings   (int);
    void addFollowers    (int);
    bool isFollow        (int);
    void likeBy          (int);

    virtual int getfollowingsNum    () const{return followings.size();}

    int         getId               () const{return id         ;}
    int         getAllTweets        () const{return allTweets  ;}
    int         getcurrentTweetNum  () const{return allTweets  ;}
    std::string getFirstName        () const{return firsName   ;}   
    int         getfollowersNum     () const{return followers.size() ;}
    std::string getUserName         () const{return userName   ;}
    std::string getLink             () const{return link       ;}
    std::string getPassword         () const{return password   ;}
    std::string getLastPass         () const{return previousPassword;}
    std::string getBiogarghy        () const{return biography  ;}
    std::string getCountry          () const{return country    ;}
    std::string getPhoneNum         () const{return phoneNumber;}
    std::string getProfilePic       () const{return profilePic ;}
    std::string getHeaderColor      () const{return headerColor;}
    std::string getBirthDate        () const{return birthDate.getDateStr();}

    virtual void save   ();
    virtual std::string getInfo();

private:
    int id ;
    int currentTweetNum {1};
    int allTweets       {1};

    std::string firsName;
    std::string userName;
    std::string password;
    std::string previousPassword;
    std::string phoneNumber;
    std::string biography;
    std::string link;
    std::string country;
    std::string profilePic;
    std::string headerColor;
    Date        birthDate;

    Tweet* currenTweet {nullptr};

    std::unordered_set<int>followings ;
    std::unordered_set<int>followers  ;

    //date

};

#endif
