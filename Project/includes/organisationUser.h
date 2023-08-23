#ifndef organisationUser_H
#define organisationUser_H

#include "includes/baseUser.h"

class OrganisationUser : public BaseUser
{
public:
    OrganisationUser();
    OrganisationUser(std::string,std::string,std::string,std::string,std::string);

    virtual void readFromFile(int)            override;
    virtual void readFromFile(std::ifstream&) override;

    virtual void setBirthDate(std::string)override;
    virtual void setBiography(std::string)override;
    virtual void setPhoneNum (std::string)override;


    virtual int getfollowingsNum() const;


    void setBoss(std::string);
    std::string getBoss(){return boss;}

    virtual std::string getInfo()override;
private:
    std::string boss ;
    std::string biography;

};

#endif
