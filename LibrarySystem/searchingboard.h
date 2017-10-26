#ifndef SEARCHINGBOARD_H
#define SEARCHINGBOARD_H

#include <QFrame>
#include "QString"
#include "global.h"

namespace Ui {
class SearchingBoard;
}

class SearchingBoard : public QFrame
{
    Q_OBJECT

public:
    explicit SearchingBoard(QWidget *parent = 0);
    ~SearchingBoard();

private slots:
    void on_btn_search_clicked();

    void on_btn_rewrite_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_btn_borrow_clicked();

    void on_btn_subscribe_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    void Search(QString key, int flag);
    void SearchByISBN(QString isbn);
    void SearchByOthers(QString key,int flag);
    void SearchByCategory();
//    void ShowTop10();
    void initViews();
    QString isbn;
    Ui::SearchingBoard *ui;
};

#endif // SEARCHINGBOARD_H
