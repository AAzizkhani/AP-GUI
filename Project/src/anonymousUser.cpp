#include "includes/anonymousUser.h"

using namespace std ;

AnonymousUser::AnonymousUser()
{
    //empty
}

AnonymousUser::AnonymousUser(string uName,string pass)
:BaseUser("AnonymousUser",uName,pass,"")
{
    //empty
}
void AnonymousUser::addTweet (string tweet,TweetInfo retweetFrom)
{
    if(!isFollow(retweetFrom.userId))
        throw invalid_argument("You must follow this person");

    BaseUser::addTweet(tweet,retweetFrom);
}
