#include "includes/organisationUser.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std ;

OrganisationUser::OrganisationUser()
{
    //empty
}

OrganisationUser::OrganisationUser(string name, string uName, string pass,string phone,string bossName)
:BaseUser(name, uName, pass,phone)
{
    setBoss(bossName);
    setPhoneNum(phone);
}
void OrganisationUser::setBoss(string input)
{
    boss = input ;
}
string OrganisationUser::getInfo()
{
    ostringstream output ;

    output <<":"<< boss << '\n' << BaseUser::getInfo();
    cerr << "OrganisationUser::getInfo-> we use virual get info \n" ;

    return output.str();
}

 void OrganisationUser::readFromFile(int id)
{
    ifstream input("user"+ to_string(id) +".txt",ios::in);
    if(!input)
        cout << "BaseUser::readFromFile->cant't open user"+ to_string(id) +".txt\n";
    else
        readFromFile(input);

    input.close();
}
 void OrganisationUser::readFromFile(ifstream& input)
{
    std::string temp;
    input >> temp;  setBoss    (temp.substr(1));

    BaseUser::readFromFile(input);
}
void OrganisationUser::setBiography(string input)
{
    if(input.size() > 1100)
        throw invalid_argument("Biography is too long");
    BaseUser::setBiography(input);
}
void OrganisationUser::setBirthDate(string input)
{
    if(input != "")
        throw invalid_argument("You can't set birthDay for organision account");
}
int OrganisationUser::getfollowingsNum()const
{
    throw invalid_argument("You can't see organision account num");
    std::cerr << "OrganisationUser::getfollowingsNum()const\n";
    return -1;
}
void OrganisationUser::setPhoneNum (string input)
{
    if(input.size() == 0)
        throw invalid_argument("Phone number can't be empty");
    BaseUser::setPhoneNum(input);
}
