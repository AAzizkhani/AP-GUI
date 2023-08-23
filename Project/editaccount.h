#ifndef EDITACCOUNT_H
#define EDITACCOUNT_H

#include <QDialog>

//logic
#include "includes/twitterak.h"

namespace Ui {
class EditAccount;
}

class EditAccount : public QDialog
{
    Q_OBJECT

public:
    explicit EditAccount(QWidget *parent = nullptr,Twitterak* = nullptr,bool = true);
    ~EditAccount();

private slots:
    void on_colorBtnchoose_clicked();

    void on_photoBtnchoose_clicked();

    void on_cancelBtn_clicked();

    void on_enterBtn_clicked();

private:
    Ui::EditAccount *ui;
    //logic
    Twitterak* appPtr;
};

#endif // EDITACCOUNT_H
