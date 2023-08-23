#include "windowper.h"
#include "ui_windowper.h"

#include "editaccount.h"
#include "mainwindow.h"
#include "search.h"

#include <QPixmap>

#include <stdexcept>
#include <QMessageBox>
#include <iostream>

WindowPer::WindowPer(QWidget *parent,Twitterak* ptr) :
    QDialog(parent),
    ui(new Ui::WindowPer),
    appPtr(ptr)
{

    std::cerr << "WindowPer::WindowPer->start\n";
    ui->setupUi(this);

    QPixmap pix(":/img/BG2.jpeg");
    ui -> BG -> setPixmap(pix.scaled(this -> width() , this -> height()));

    ui ->tweetTxt ->setEnabled(false);
    ui ->editBtn  ->setEnabled(false);
    ui ->cancelBtn->setEnabled(false);

    std::cerr << "WindowPer::WindowPer->1\n";
    char userType;
    try
    {
        userType = appPtr->bringType();
    }
    catch (std::invalid_argument& err)
    {
        QMessageBox::warning(this,"error",QString::fromStdString(err.what()));
    }

    if (userType == 'a')
    {
        ui -> addBtn   -> setEnabled(false);
        ui -> saveBtn  -> setEnabled(false);
        ui -> editBtn  -> setEnabled(false);
        ui -> cancelBtn-> setEnabled(false);
    }
    std::cerr << "WindowPer::WindowPer->2\n";
    showTweet();
    std::cerr << "WindowPer::WindowPer->end\n";
    setFollowers();
}

WindowPer::~WindowPer()
{
    delete ui;
}
void WindowPer::showTweet()
{
    ui ->cancelBtn->setEnabled(false);
    ui->nextBtn  ->setEnabled(appPtr->getMainUser()->canShowNextTweet());
    ui->preBtn   ->setEnabled(appPtr->getMainUser()->canShowLastTweet());

    try
    {
        std::string tweetStr = appPtr->getMainUser()->getTweet()->getTweetStr();
        ui->tweetTxt->setPlainText(QString::fromStdString(tweetStr));
        setLikes();
    }
    catch (std::invalid_argument& err)
    {
        //QMessageBox::warning(this,"eror",QString::fromStdString(err.what()));
        ui->tweetTxt->setPlainText("There is no tweet yet :)");
    }
}
void WindowPer::on_settingBtn_clicked()
{
    EditAccount op(this,appPtr);
    op.setWindowTitle("Account");
    op.setModal(true);
    op.exec();
}


void WindowPer::on_exitBtn_clicked()
{
    QApplication :: quit();
}

void WindowPer::on_logoutBtn_clicked()
{
    this -> hide();

    MainWindow w;
    w.setWindowTitle("Twitterak(LA)");
    w.show();
}

void WindowPer::on_addBtn_clicked()
{
    ui ->cancelBtn->setEnabled(true);
    ui->nextBtn->setEnabled(false);
    ui->preBtn ->setEnabled(false);
    ui->tweetTxt->setEnabled(true);
    ui->tweetTxt->setPlainText("");
}


void WindowPer::on_saveBtn_clicked()//have a problem
{
    ui->tweetTxt->setEnabled(false);
    std::string tweetText = ui->tweetTxt->toPlainText().toStdString();
    appPtr->addTweet(tweetText);
    showTweet();   
}

void WindowPer::on_userSearchBtn_clicked()
{
    Search op(this,appPtr);
    op.setModal(true);
    op.setWindowTitle("Search");
    op.exec();
}

void WindowPer::on_deleteAccBtn_clicked()
{
    std::string userName = appPtr->getMainUser()->getUserName();

    appPtr->deleteUser(userName);

    close();
}

void WindowPer::on_editBtn_clicked()
{
   // ui->tweetTxt->setEnabled(true);//
}


void WindowPer::on_nextBtn_clicked()
{
    try
    {
        appPtr->getMainUser()->goToNextTweet();
        showTweet();
    }
    catch(std::out_of_range& err)
    {
        QMessageBox::warning(this,"error",QString::fromStdString(err.what()));
    }

}

void WindowPer::on_preBtn_clicked()
{
    try
    {
        appPtr->getMainUser()->goToLastTweet();
        showTweet();
    }
    catch(std::out_of_range& err)
    {
        QMessageBox::warning(this,"error",QString::fromStdString(err.what()));
    }
}
void WindowPer::setFollowers()
{
    try
    {
        int followers = appPtr->getMainUser()->getfollowersNum();
        ui->followersTxt->setText("followers: " + QString::number(followers));
    }
    catch (std::invalid_argument& err)
    {
        QString message = QString::fromStdString(err.what());
        ui->followersTxt->setText("followers: " + message);
    }
    try
    {
        int followings = appPtr->getMainUser()->getfollowingsNum();
        ui->label->setText("followings: " + QString::number(followings ));
    }
    catch (std::invalid_argument& err)
    {
        QString message = QString::fromStdString(err.what());
        ui->label->setText("followings: " + message);
    }
}

void WindowPer::on_cancelBtn_clicked()
{
    ui->tweetTxt->setEnabled(false);
    showTweet();
    ui->tweetTxt->setEnabled(false);
}
void WindowPer::setLikes()
{
    try
    {
        int likesNum = appPtr->getMainUser()->getTweet()->getLikeNum();
        ui->likeTxt->setText("Likes" + QString::number(likesNum));
    }
    catch (...)
    {
        std::cerr << "UserAccount::setLikes\n" ;
    }
}
