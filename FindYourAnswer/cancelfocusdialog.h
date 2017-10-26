#ifndef CANCELFOCUSDIALOG_H
#define CANCELFOCUSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class CancelFocusDialog;
}

class CancelFocusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CancelFocusDialog(QWidget *parent = 0, QString name = "");
    ~CancelFocusDialog();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_confirm_clicked();

private:
    Ui::CancelFocusDialog *ui;
};

#endif // CANCELFOCUSDIALOG_H
