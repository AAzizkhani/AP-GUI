#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>

//logic
#include "includes/twitterak.h"

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent ,Twitterak* );
    ~Search();

private slots:
    void on_searchBtn_clicked();

    void on_searchHashTagBtn_clicked();

private:
    Ui::Search *ui;
    Twitterak* appPtr;
};

#endif // SEARCH_H
