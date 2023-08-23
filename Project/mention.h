#ifndef MENTION_H
#define MENTION_H

#include <QDialog>

namespace Ui {
class Mention;
}

class Mention : public QDialog
{
    Q_OBJECT

public:
    explicit Mention(QWidget *parent = nullptr);
    ~Mention();

private slots:
    void on_exitBtn_clicked();

private:
    Ui::Mention *ui;
};

#endif // MENTION_H
