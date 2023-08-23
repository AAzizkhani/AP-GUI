#include "login.h"
#include "ui_login.h"

#include "windowper.h"

#include <QPixmap>
#include <QDir>

//logic
#include <QString>
#include <QMessageBox>
#include <stdexcept>
#include <iostream>

Login::Login(QWidget *parent,Twitterak* ptr) :
    QDialog(parent),
    ui(new Ui::Login),
    appPtr(ptr)
{
    ui->setupUi(this);

    QPixmap pix(":/img/BG1.jpeg");
    ui -> BG -> setPixmap(pix.scaled(this -> width() , this -> height()));

    //if (appPtr -> Bringtype())
}

Login::~Login()
{
    delete ui;
}

void Login::on_enterBtn_clicked()
{
    QString userName = ui -> usernameTxtBar->text();
    QString password = ui -> passwordTxtBar->text();

    try
    {
        std::cerr << "Login::on_enterBtn_clicked->start try\n";
        appPtr->loadMainUser(userName.toStdString(),password.toStdString());
        std::cerr << "Login::on_enterBtn_clicked->after try2\n";
        WindowPer op(this,appPtr);
        this -> hide();
        op.setWindowTitle("Main App");
        op.setModal(true);
        op.exec();
    }
    catch (std::invalid_argument& err)
    {
        QMessageBox::warning(this,"error",QString::fromStdString(err.what()));
    }
    catch (std::out_of_range& err)
    {
        QMessageBox::warning(this,"error",QString::fromStdString(err.what())+"line49");
    }
}

void Login::on_seePassBtn_clicked()
{
    ui->passwordTxtBar->setEchoMode(QLineEdit::Normal);
}
//ui->passwordTxtBar->setEchoMode(QLineEdit::Normal);
//ui -> seePassBtn -> setIcon(QIcon(":/icon/icons8-invisible-96.png"));
//ui -> seePassBtn -> setIconSize(QSize(31 , 31));

//ui->passwordTxtBar->setEchoMode(QLineEdit::Password);
//ui -> seePassBtn -> setIcon(QIcon(":/icon/icons8-eye-96.png"));
//ui -> seePassBtn -> setIconSize(QSize(31 , 31));
void Login::on_unseePassBtn_clicked()
{
    ui->passwordTxtBar->setEchoMode(QLineEdit::Password);

}
