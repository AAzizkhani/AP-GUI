#include "includes/personalUser.h"

using namespace std;

PersonalUser::PersonalUser()
{
    //empty
}
PersonalUser::PersonalUser(string name, string uName, string pass,string phone)
:BaseUser( name,  uName,  pass, phone)
{
    setPhoneNum(phone);
}

void PersonalUser::setBoss(string input)  
{
    bossName = input ;
}
void PersonalUser::setPhoneNum(string input)
{
    if(input.size() == 0)
        throw invalid_argument("Phone number can't be empty");
    BaseUser::setPhoneNum(input);
}
