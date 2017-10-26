#ifndef USERCENTERBOARD_H
#define USERCENTERBOARD_H

#include <QFrame>
#include "global.h"
#include "user.h"
#include "QStandardItemModel"

namespace Ui {
class UserCenterBoard;
}

class UserCenterBoard : public QFrame
{
    Q_OBJECT

public:
    explicit UserCenterBoard(QWidget *parent = 0);
    ~UserCenterBoard();
    void setUserId(QString id);
    void initViews();

private slots:
    void on_book_list_doubleClicked(const QModelIndex &index);

    void on_btn_edit_info_clicked();

private:
    Ui::UserCenterBoard *ui;
    QStandardItemModel *model2;
    QString user_id;
};

#endif // USERCENTERBOARD_H
