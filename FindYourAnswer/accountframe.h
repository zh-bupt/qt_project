#ifndef ACCOUNTFRAME_H
#define ACCOUNTFRAME_H

#include <QFrame>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class AccountFrame;
}

class AccountFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AccountFrame(QWidget *parent = 0);
    ~AccountFrame();

private slots:
    void on_btn_change_password_clicked();

    void on_btn_logout_clicked();

    void on_btn_return_clicked();

private:
    Ui::AccountFrame *ui;
    MainWindow * mainWindow;
};

#endif // ACCOUNTFRAME_H
