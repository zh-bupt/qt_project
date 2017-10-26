#ifndef BOOKDETAILS_H
#define BOOKDETAILS_H

#include <QDialog>
#include "global.h"
#include "user.h"

namespace Ui {
class BookDetails;
}

class BookDetails : public QDialog
{
    Q_OBJECT

public:
    explicit BookDetails(QWidget *parent = 0, QString isbn="");
    ~BookDetails();
private:
    static const int FROM_MESSAGE_BOARD=0x1010;
    static const int FROM_SEARCH_BOARD=0x0101;
    void initViews();

    Ui::BookDetails *ui;
    QString isbn;
    int skip_from;
private slots:
    void on_pushButton_clicked();
    void on_borrowBtn_clicked();
    void on_orderBtn_clicked();
};

#endif // BOOKDETAILS_H

