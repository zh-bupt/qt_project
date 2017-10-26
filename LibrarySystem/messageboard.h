#ifndef MESSAGEBOARD_H
#define MESSAGEBOARD_H

#include <QFrame>
#include "QStandardItemModel"

namespace Ui {
class MessageBoard;
}

class MessageBoard : public QFrame
{
    Q_OBJECT

public:
    explicit MessageBoard(QWidget *parent = 0);
    ~MessageBoard();
    void initViews();

private slots:
    void on_order_table_doubleClicked(const QModelIndex &index);

    void on_borrow_table_doubleClicked(const QModelIndex &index);

private:
    void displayBorrowBooks();
    void displayOrderBooks();
    Ui::MessageBoard *ui;
    QStandardItemModel *borrow_model=NULL;
    QStandardItemModel *order_model=NULL;
};

#endif // MESSAGEBOARD_H
