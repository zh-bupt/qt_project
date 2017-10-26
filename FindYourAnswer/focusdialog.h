#ifndef FOCUSDIALOG_H
#define FOCUSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class FocusDialog;
}

class FocusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FocusDialog(QWidget *parent = 0, QString focusedName = "");
    ~FocusDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FocusDialog *ui;
    QString focusedName;
};

#endif // FOCUSDIALOG_H
