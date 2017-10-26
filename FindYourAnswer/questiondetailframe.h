#ifndef QUESTIONDETAILFRAME_H
#define QUESTIONDETAILFRAME_H

#include <QFrame>
#include <QString>
#include <list>
#include "comment.h"
#include "question.h"
#include "mainwindow.h"
#include <QStandardItemModel>

namespace Ui {
class QuestionDetailFrame;
}

class MainWindow;


class QuestionDetailFrame : public QFrame
{
    Q_OBJECT

public:
    explicit QuestionDetailFrame(QWidget *parent = 0, int questionId = 0);
    ~QuestionDetailFrame();

private slots:
    void on_btn_comment_clicked();

    void on_btn_back_clicked();

    void on_tb_comment_doubleClicked(const QModelIndex &index);

signals:
    void updateFocusList();

private:
    Ui::QuestionDetailFrame *ui;
    MainWindow *mainWindow;
    int questionId;
    QString questionTitle;
    QString questionContext;
    Question question = Question();
    std::list<Comment> questionComment;
    QStandardItemModel * model= nullptr;
    void initviews();
};

#endif // QUESTIONDETAILFRAME_H
