#include <iostream>
#include <stdexcept>
#include <ctime>
#include <sstream>

#include "includes/Date.h"

#define thisYear 1401

using namespace std;


Date::Date(){}
Date::Date(int year ,int month ,int day)
{
    setYear (year) ;
    setMonth(month);
    setDay  (day)  ;
}

void Date::setYear (int input)
{
    if(!(0 < input && input < thisYear ))
    {
        throw invalid_argument("! Year is not correct");
    }
    year = input;
}

void Date::setMonth(int input)
{
    if(!(0 < input && input < 13))
    {
        throw invalid_argument("! Month is not correct");
    }
    month = input;
}

void Date::setDay  (int input)
{
    if(!(0 < input && input < 31+(month < 7)))
    {
        throw invalid_argument("! Day is not correct");
    }
    day = input;
}

std::string Date::getDateStr()const
{
    if(year < 0)
        return "";
    ostringstream output ;
    output << year  << '/' ;
    if(month < 10 ) output << '0';
    output << month << '/';
    if(day   < 10 ) output << '0';
    output << day;
    return output.str();
}
Date::Date(string input)
{
    setDate(input);
}

void Date::setDate (string input)
{
    //1300 / 02 / 01
    //0123 4 56 7 89
    int year,month,day;
    try
    {
        year  = stoi(input.substr(0,4));
        cerr << "year:" << year << '\n';
        month = stoi(input.substr(5,2));
        cerr << "month:"<<month << '\n';
        day   = stoi(input.substr(8  ));
        cerr << "day :" << day  << '\n';
    }
    catch (...)
    {
        throw invalid_argument("! Uncorrect date input");
    }
    setYear (year) ;
    setMonth(month);
    setDay  (day)  ;
}

//string Date::getTime()
//{
//    time_t thisTime = time(0);
//    char* outputTime = ctime(&thisTime);
//    return outputTime;
//}
