#ifndef COMMENTDIALOG_H
#define COMMENTDIALOG_H

#include <QDialog>

namespace Ui {
class CommentDialog;
}

class CommentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommentDialog(QWidget *parent = 0, int questionId = 0);
    ~CommentDialog();

private slots:
    void on_btn_commit_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::CommentDialog *ui;
    int questionId;
};

#endif // COMMENTDIALOG_H
