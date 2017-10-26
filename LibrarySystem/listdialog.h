#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>
#include <QComboBox>

namespace Ui {
class ListDialog;
}

class ListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListDialog(QWidget *parent = 0,int flag=0,QString tag="");
    ~ListDialog();

private slots:
    void on_btn_confirm_clicked();

private:
    void initViews();
    void disPlayBookList();
    void disPlayUserList();

    Ui::ListDialog *ui;
    int flag;
    QString tag;
};

#endif // LISTDIALOG_H
