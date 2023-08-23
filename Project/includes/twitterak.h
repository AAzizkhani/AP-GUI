#ifndef TWITTERAK_H
#define TWITTERAK_H

#include <unordered_map>
#include <forward_list>
#include <vector>

#include "includes/tweetInfo.h"
#include "includes/personalUser.h"
#include "includes/organisationUser.h"
#include "includes/anonymousUser.h"

class userInfo
{
public:
    std::string password;
    int  id ;
    char type ;
};


class Twitterak
{
public:
    Twitterak();
    ~Twitterak();

    void ChangUserName(std::string);

    void setMainUser(std::string,std::string,std::string
                    ,std::string,std::string,char);


    void loadMainUser (std::string ,std::string);
    void addTweet     (std::string ,TweetInfo = {0,0});
    void deleteUser   (std::string);
    void clearMainUser();

    void setTempUserForHasgtag  ();
    void loadTempUser (std::string);
    void clearTempUser();

    void follow  ();
    bool isFollow();
    void like    ();

    char bringType(std::string);
    char bringType();

    std::vector<std::string> searchForHasgtags(std::string);
    void addHashtags     (std::string);
    bool canBeInHashtag  (char);
    void saveHastagMap   ();
    void getInfoHastagMap();

    void changeBoss(std::string);
    std::string getBoss(BaseUser*);
    void changeCompany(std::string);
    std::string getCompany(BaseUser*);

    void creatHashtagVec (std::string);
    void goToNextHashtag   ();
    void goToLastHashtag   ();
    bool canShowNextHashtag();
    bool canShowLastHashtag();

    BaseUser* getMainUser(){return mainUser;}
    BaseUser* getTempUser(){return tempUser;}

private:
    std::unordered_map<std::string ,userInfo >usersMap ;
    std::unordered_map<std::string ,std::vector<TweetInfo> >hashtagsMap ;

    BaseUser* mainUser ;
    BaseUser* tempUser ;
    std::vector<TweetInfo> currentHashtagVec;

    int numberOfUsers  ;
    int hashTagIndex {};

    BaseUser* makeUser(std::string);
};

#endif // TWITTERAK_H
