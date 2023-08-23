#ifndef WINDOWPER_H
#define WINDOWPER_H

#include <QDialog>

//logic
#include "includes/twitterak.h"

namespace Ui {
class WindowPer;
}

class WindowPer : public QDialog
{
    Q_OBJECT

public:
    explicit WindowPer(QWidget *parent = nullptr, Twitterak* = nullptr);

    ~WindowPer();

    void showTweet();
    void setFollowers();
    void setLikes();


private slots:
    void on_settingBtn_clicked();

    void on_exitBtn_clicked();

    void on_logoutBtn_clicked();

    void on_addBtn_clicked();

    void on_saveBtn_clicked();

    void on_userSearchBtn_clicked();

    void on_deleteAccBtn_clicked();

    void on_editBtn_clicked();

    void on_nextBtn_clicked();

    void on_preBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::WindowPer *ui;
    //logic
    Twitterak* appPtr ;
};

#endif // WINDOWPER_H
