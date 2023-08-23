#ifndef DATE_H
#define DATE_H

#include <string>

class Date
{
public:
    Date();
    Date(int,int,int);
    Date(std::string);

    void setDate (std::string);
    void setYear (int);
    void setMonth(int);
    void setDay  (int);

    std::string getDateStr()const;
private:

    int year {-1};
    int month{-1};
    int day  {-1};
};


#endif // DATE_H
