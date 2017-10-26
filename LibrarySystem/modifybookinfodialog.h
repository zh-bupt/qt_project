#ifndef MODIFYBOOKINFODIALOG_H
#define MODIFYBOOKINFODIALOG_H

#include <QDialog>

namespace Ui {
class ModifyBookInfoDialog;
}

class ModifyBookInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyBookInfoDialog(QWidget *parent = 0,QString isbn="");
    ~ModifyBookInfoDialog();

private slots:
    void on_btn_confirm_clicked();

    void on_btn_cancel_clicked();

private:
    void initViews();
    bool checkInfo();
    Ui::ModifyBookInfoDialog *ui;
    QString ISBN="";
};

#endif // MODIFYBOOKINFODIALOG_H
