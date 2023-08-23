#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include "editaccount.h"

#include <QDialog>

//logic
#include "includes/twitterak.h"

namespace Ui {
class UserAccount;
}

class UserAccount : public QDialog
{
    Q_OBJECT

public:
    explicit UserAccount(QWidget *parent = nullptr,Twitterak* = nullptr, char = 'u');
    ~UserAccount();

    void showTweet     ();
    void showTweetHasgtag();
    void showTweetUser   ();

    void goToNextUser ();
    void goToNextHasgtag();
    void goToLastUser ();
    void goToLastHasgtag();

    void checkBtnFollow();
    void setLikes      ();
    void setBtn        ();

private slots:

    void on_settingBtn_clicked();

    void on_exitBtn_clicked();

    void on_userSearchBtn_clicked();


    void on_nextBtn_clicked();


    void on_preBtn_clicked();

    void on_followBtn_clicked();

    void on_likeBtn_clicked();

    void on_quteTweetBtn_clicked();

    void on_mentionBtn_clicked();

    void on_retweetBtn_clicked();


private:
    Ui::UserAccount *ui;

    EditAccount *op;

    Twitterak* appPtr;
    char mode ;
};

#endif // USERACCOUNT_H
