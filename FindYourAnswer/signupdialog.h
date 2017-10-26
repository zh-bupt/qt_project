#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>

namespace Ui {
class SignupDialog;
}

class SignupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDialog(QWidget *parent = 0);
    ~SignupDialog();

private slots:
    void on_btn_signup_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::SignupDialog *ui;
};

#endif // SIGNUPDIALOG_H
