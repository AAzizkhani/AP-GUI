#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

//logic***
#include "includes/twitterak.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr, Twitterak* = nullptr);
    ~Login();

private slots:

    void on_enterBtn_clicked();


    void on_seePassBtn_clicked();

    void on_unseePassBtn_clicked();

private:
    Ui::Login *ui;

    //logic ***
    Twitterak* appPtr ;

};

#endif // LOGIN_H
