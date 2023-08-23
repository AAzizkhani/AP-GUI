#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "includes/twitterak.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    //static flags for validate any type of users in signup window to windowper and editaccount
    static bool flagO;
    static bool flagP;
    static bool flagA;

    ~MainWindow();

private slots:

    void on_loginBtn_clicked();

    void on_signupBtn_clicked();

    void on_helpBtn_clicked();

    void on_aboutBtn_clicked();

    void on_exitBtn_clicked();

private:
    Ui::MainWindow *ui;

    //*****logic*******
    Twitterak myApp;
};
#endif // MAINWINDOW_H
