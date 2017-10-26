#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "usermanager.h"
#include "QString"
#include "global.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    QString getUserId();
private slots:

    void on_login_clicked();

private:
    Ui::LoginDialog *ui;
    QString user_id;
};

#endif // LOGINDIALOG_H
