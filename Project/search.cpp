#include "search.h"
#include "ui_search.h"

#include "useraccount.h"

#include <QPixmap>

//logic
#include <QMessageBox>
#include <iostream>

Search::Search(QWidget *parent,Twitterak* ptr) :
    QDialog(parent),
    ui(new Ui::Search),
    appPtr(ptr)
{
    if(appPtr == nullptr)std::cerr << "Search::Search-> ptr is empty\n";
    ui->setupUi(this);

    QPixmap pix(":/img/BG1.jpeg");
    ui -> BG -> setPixmap(pix.scaled(this -> width() , this -> height()));

}

Search::~Search()
{
    delete ui;
}

void Search::on_searchBtn_clicked()
{
    try
    {
        std::string userName {ui->searchTxtBar->text().toStdString()};


        appPtr->loadTempUser(userName);
        this -> close();
        UserAccount test(this,appPtr);
        test.setModal(true);
        test.exec();

    }
    catch (std::invalid_argument& err)
    {
        QMessageBox::warning(this,"eror",QString::fromStdString(err.what()));
    }
    catch(...)
    {
        QMessageBox::warning(this,"eror","wtffff");
    }
}

void Search::on_searchHashTagBtn_clicked()
{
    try
    {
        std::cerr << "Search::on_searchHashTagBtn_clicked->start\n";
        std::string hashtah {ui->searchTxtBar->text().toStdString()};

        appPtr->creatHashtagVec(hashtah);
        std::cerr << "Search::on_searchHashTagBtn_clicked->2\n";
        this -> close();

        UserAccount test(this,appPtr,'h');
        test.setModal(true);
        test.exec();
    }
    catch (std::invalid_argument& err)
    {
        QMessageBox::warning(this,"eror",QString::fromStdString(err.what()));
    }
    catch(...)
    {
        QMessageBox::warning(this,"eror","wtffff");
    }
}

