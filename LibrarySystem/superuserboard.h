#ifndef SUPERUSERBOARD_H
#define SUPERUSERBOARD_H

#include <QFrame>

namespace Ui {
class SuperUserBoard;
}

class SuperUserBoard : public QFrame
{
    Q_OBJECT

public:
    static const int BOOK_LIST=0x10001;
    static const int USER_LIST=0x10002;
    static const int MODIFY_USER_INFO=0x10003;
    static const int MODIFY_BOOK_INFO=0x10004;

    explicit SuperUserBoard(QWidget *parent = 0);
    ~SuperUserBoard();

private slots:
    void on_btn_confirm_clicked();

    void on_btn_clear_clicked();

    void on_btn_search_user_clicked();

    void on_btn_search_book_clicked();

    void on_book_borrow_info_clicked();

    void on_user_borrow_info_clicked();

    void on_modify_book_info_clicked();

    void on_modify_user_info_clicked();

private:
    Ui::SuperUserBoard *ui;
    QString isbn="";
    QString user_id="";
};

#endif // SUPERUSERBOARD_H
