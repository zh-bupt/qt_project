#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    int getUserId();

private slots:
    void on_btn_login_clicked();

    void on_btn_cancel_clicked();


    void on_pushButton_clicked();

private:
    Ui::LoginDialog *ui;
    int userId;
    MainWindow * mainWindow;
};

#endif // LOGINDIALOG_H
