#ifndef MODIFYUSERINFODIALOG_H
#define MODIFYUSERINFODIALOG_H

#include <QDialog>

namespace Ui {
class ModifyUserInfoDialog;
}

class ModifyUserInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyUserInfoDialog(QWidget *parent = 0, QString id="");
    ~ModifyUserInfoDialog();

private slots:
    void on_btn_comfirm_clicked();

    void on_btn_cancel_clicked();

    void on_show_password_clicked();

private:
    void initViews();
    bool checkInfo();
    Ui::ModifyUserInfoDialog *ui;
    QString id="";
};

#endif // MODIFYUSERINFODIALOG_H
