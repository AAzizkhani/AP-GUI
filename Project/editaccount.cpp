#include "editaccount.h"
#include "ui_editaccount.h"

#include <QColorDialog>
#include <QColor>
#include <QPixmap>
#include <QFileDialog>
#include <iostream>
#include <QMessageBox>

EditAccount::EditAccount(QWidget *parent,Twitterak* ptr, bool myPage) :
    QDialog(parent),
    ui(new Ui::EditAccount),
    appPtr(ptr)
{
    ui->setupUi(this);
    QPixmap pix(":/img/BG.jpg");
    ui -> BG -> setPixmap(pix.scaled(this -> width() , this -> height()));


    BaseUser* pageOwner {nullptr};
    if(myPage)
    {
        pageOwner = appPtr->getMainUser();
    }
    else
    {
        pageOwner = appPtr->getTempUser();
    }

    ui -> nameTxtBar     -> setText(QString::fromStdString(pageOwner->getFirstName()));
    ui -> usernameTxtBar -> setText(QString::fromStdString(pageOwner->getUserName()) );
    ui -> passwordTxtBar -> setText(QString::fromStdString(pageOwner->getPassword()) );
    ui -> numberTxtBar   -> setText(QString::fromStdString(pageOwner->getPhoneNum()) );
    ui -> countryTxtBar  -> setText(QString::fromStdString(pageOwner->getCountry())  );
    ui -> linkTxtBar     -> setText(QString::fromStdString(pageOwner->getLink())     );
    ui -> dateTxtBar     -> setText(QString::fromStdString(pageOwner->getBirthDate()));
    ui -> bioTxtedit     -> setPlainText(QString::fromStdString(pageOwner->getBiogarghy()));

    std::string text = appPtr->getBoss(pageOwner) != "" ? appPtr->getBoss(pageOwner) : appPtr->getCompany(pageOwner);
    ui -> orguserTxtBar  -> setText(QString::fromStdString(text));

    QString toQstring = QString :: fromUtf8(pageOwner->getProfilePic().c_str());
    QPixmap pixx(toQstring);
    ui -> Pic -> setPixmap(pixx.scaled(ui -> Pic -> width() ,ui -> Pic -> height() , Qt :: KeepAspectRatio));

    //ui -> dateTxtBar     -> setText(QString::fromStdString(appPtr->getMainUser()->getFirstName()));
    if (!myPage ||appPtr->bringType() == 'a')
    {
        ui -> nameTxtBar     -> setEnabled(false);
        ui -> orguserTxtBar  -> setEnabled(false);
        ui -> numberTxtBar   -> setEnabled(false);
        ui -> countryTxtBar  -> setEnabled(false);
        ui -> linkTxtBar     -> setEnabled(false);
        ui -> dateTxtBar     -> setEnabled(false);
        ui -> bioTxtedit     -> setEnabled(false);
        ui -> colorBtnchoose -> setEnabled(false);
        ui -> photoBtnchoose -> setEnabled(false);

        if(!myPage)
        {
            ui->orguserTxtBar->setEnabled(false);
            ui->usernameTxtBar->setEnabled(false);
            ui->passwordTxtBar->setEnabled(false);
            ui->passwordTxtBar->setEchoMode(QLineEdit::Password);
            ui->enterBtn ->setEnabled(false);
            ui->cancelBtn->setEnabled(false);
            ui->colorBtnchoose->setEnabled(false);
            ui->photoBtnchoose->setEnabled(false);
        }

        ui -> HeaderColor-> setPalette(QPalette("black"));

        QPixmap pix(":/img/781-7812555_anonymous-mask-png-transparent-images-anonymous-icon-red.jpeg");
        ui -> Pic -> setPixmap(pix.scaled(ui -> Pic -> width() ,ui -> Pic -> height() , Qt :: KeepAspectRatio));

    }

    if(appPtr->bringType() == 'o' || appPtr->bringType() == 'p')
{
        appPtr->bringType() == 'o' ? ui ->munTxt->setText("Manager") :  ui->munTxt->setText("company") ;
        QString toQstring = QString :: fromUtf8(appPtr -> getMainUser() ->getHeaderColor().c_str());
        ui -> HeaderColor-> setPalette(QPalette(toQstring));

        if (pageOwner ->getProfilePic() !="")
        {
            QString toQstring = QString :: fromUtf8(pageOwner ->getProfilePic().c_str());

            QPixmap pix(toQstring);
            ui -> Pic -> setPixmap(pix.scaled(ui -> Pic -> width() ,ui -> Pic -> height() , Qt :: KeepAspectRatio));
            pageOwner ->setProfilePic(toQstring.toStdString());
        }
        else
        {
            if (appPtr->bringType() == 'o')
            {
                QPixmap pix(":/img/DotORG_logo.svg.png");
                ui -> Pic -> setPixmap(pix.scaled(ui -> Pic -> width() ,ui -> Pic -> height() , Qt :: KeepAspectRatio));
            }
            else if (appPtr->bringType() == 'p')
            {
                QPixmap pix(":/img/user-128.png");
                ui -> Pic -> setPixmap(pix.scaled(ui -> Pic -> width() ,ui -> Pic -> height() , Qt :: KeepAspectRatio));
            }
        }
        std::cerr << "EditAccount::EditAccount-> secend if end  \n";
    }
}

EditAccount::~EditAccount()
{
    delete ui;
}

void EditAccount::on_colorBtnchoose_clicked()
{
    QColor color = QColorDialog :: getColor(Qt :: red , this , "Choose a color!");
    if (color.isValid())
    {
        ui -> HeaderColor-> setPalette(QPalette(color));

        QString toQstring = color.name(QColor :: HexRgb);
        std :: string toString = toQstring.toUtf8().constData();
        appPtr -> getMainUser() ->setHeaderColor(toString);
    }
}

void EditAccount::on_photoBtnchoose_clicked()
{
    QString filter = "All files (*.*) ;; .jpeg (*.jpeg) ;; .png (*.png) ;; .jpg (*.jpg)";

    QString fileName = QFileDialog :: getOpenFileName(this , "Choose a picture" , "/home" , filter);
    QPixmap pix5(fileName);
    ui -> Pic -> setPixmap(pix5.scaled(ui -> Pic -> width() ,ui -> Pic -> height() , Qt :: KeepAspectRatio));

    std :: string fileNameString = fileName.toUtf8().constData();//
    appPtr -> getMainUser() ->setProfilePic(fileNameString); //
}

void EditAccount::on_cancelBtn_clicked()
{
    close();
}


void EditAccount::on_enterBtn_clicked()
{
    try
    {

        std::string input;
        input  = ui -> nameTxtBar     ->text().toStdString();   appPtr->getMainUser()->setFirsrName (input);
        input  = ui -> usernameTxtBar ->text().toStdString();   appPtr->ChangUserName               (input);
        input  = ui -> passwordTxtBar ->text().toStdString();   appPtr->getMainUser()->setPassword  (input);
        input  = ui -> numberTxtBar   ->text().toStdString();   appPtr->getMainUser()->setPhoneNum  (input);
        input  = ui -> countryTxtBar  ->text().toStdString();   appPtr->getMainUser()->setCountry   (input);
        input  = ui -> linkTxtBar     ->text().toStdString();   appPtr->getMainUser()->setLink      (input);
        input  = ui -> dateTxtBar     ->text().toStdString();   appPtr->getMainUser()->setBirthDate (input);
        input  = ui -> Pic            ->text().toStdString();   appPtr->getMainUser()->setProfilePic(input);

        input  = ui -> bioTxtedit     ->toPlainText().toStdString();
        appPtr->getMainUser()->setBiography(input);

        input = ui -> orguserTxtBar   ->text().toStdString();
        if(appPtr->bringType() == 'o')
            appPtr->changeBoss(input);
        else if(appPtr->bringType() == 'p')
        {
            std::cerr << "EditAccount::on_enterBtn_clicked      yy\n";
            appPtr->changeCompany(input);
        }

        close();
    }
    catch (std::invalid_argument& err)
    {
       QMessageBox::warning(this,"error",QString::fromStdString(err.what()));
    }
}

