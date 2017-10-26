#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <QDialog>

namespace Ui {
class QuestionDialog;
}

class QuestionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionDialog(QWidget *parent = 0);
    ~QuestionDialog();

private slots:
    void on_btn_commit_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::QuestionDialog *ui;
};

#endif // QUESTIONDIALOG_H
