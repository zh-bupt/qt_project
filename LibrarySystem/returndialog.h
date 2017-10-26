#ifndef RETURNDIALOG_H
#define RETURNDIALOG_H

#include <QDialog>
#include "QString"
#include "mainwindow.h"
#include "QStandardItemModel"

namespace Ui {
class ReturnDialog;
}

class ReturnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReturnDialog(QWidget *parent = 0, QString isbn="");
    ~ReturnDialog();
    void initViews();

private slots:
    void on_btn_return_clicked();

    void on_btn_renew_clicked();

private:
    Ui::ReturnDialog *ui;
    QString ISBN;
    MainWindow *mainwindow;
    QStandardItemModel *model=NULL;
};

#endif // RETURNDIALOG_H
