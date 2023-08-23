#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "signup.h"
#include "login.h"
#include "windowper.h"

#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/img/BG.jpg");
    ui -> BG -> setPixmap(pix.scaled(this -> width() , this -> height()));

    QPixmap pix1(":/img/LogoW_auto_x2_colored_toned_light_ai.jpg");
    ui -> Logo -> setPixmap(pix1.scaled(ui -> Logo -> width() , ui -> Logo -> height() , Qt :: KeepAspectRatio));

}

//bool MainWindow :: flagO = false;
//bool MainWindow :: flagP = false;
//bool MainWindow :: flagA = false;

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginBtn_clicked()
{
    Login op(this,&myApp);
    op.setModal(true);
    op.setWindowTitle("Login");
    op.exec();
}

void MainWindow::on_signupBtn_clicked()
{
    SignUp op(this,&myApp);
    op.setModal(true);
    op.setWindowTitle("Signup");
    op.exec();
}

void MainWindow::on_helpBtn_clicked()
{
    QMessageBox :: information(this , "Help" , "If you have an account press login\nif you not,make one with signup!");
}

void MainWindow::on_aboutBtn_clicked()
{
    QMessageBox :: about(this , "About this app" , "This app created by group of LA\n Losers All the time!\nenjoy!");
}

void MainWindow::on_exitBtn_clicked()
{
    QApplication :: quit();
}

