#include "mention.h"
#include "ui_mention.h"

Mention::Mention(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Mention)
{
    QPixmap pix(":/img/BG2.jpeg");
    ui -> BG -> setPixmap(pix.scaled(this -> width() , this -> height()));
    ui->setupUi(this);
}

Mention::~Mention()
{
    delete ui;
}

void Mention::on_exitBtn_clicked()
{
    QApplication :: quit();
}
