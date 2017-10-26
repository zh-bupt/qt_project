#ifndef BORROWBOARD_H
#define BORROWBOARD_H

#include <QFrame>

namespace Ui {
class BorrowBoard;
}

class BorrowBoard : public QFrame
{
    Q_OBJECT

public:
    explicit BorrowBoard(QWidget *parent = 0);
    ~BorrowBoard();

private slots:
    void on_btn_borrow_clicked();

    void on_btn_clear_clicked();

private:
    Ui::BorrowBoard *ui;
};

#endif // BORROWBOARD_H
