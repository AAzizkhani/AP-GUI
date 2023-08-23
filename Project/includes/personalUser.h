#ifndef PersonalUser_H
#define PersonalUser_H

#include "baseUser.h"

class PersonalUser : public BaseUser
{
public:
    PersonalUser();
    PersonalUser(std::string,std::string,std::string,std::string);

    void setBoss(std::string);

    virtual void setPhoneNum   (std::string)override;
    
    std::string getBoss() {return bossName;}

private:
    std::string bossName ;

};

#endif
