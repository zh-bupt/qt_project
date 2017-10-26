#ifndef USERQUESTIONFRAME_H
#define USERQUESTIONFRAME_H

#include <QFrame>
#include <QString>
#include <list>
#include "question.h"
#include "comment.h"
#include "QStandardItemModel"
#include "mainwindow.h"

namespace Ui {
class UserQuestionFrame;
}

using std::list;

class UserQuestionFrame : public QFrame
{
    Q_OBJECT

public:
    explicit UserQuestionFrame(QWidget *parent = 0, QString userName = "");
    ~UserQuestionFrame();

private slots:
    void on_btn_return_clicked();

    void on_btn_cancel_focus_clicked();

    void on_tb_question_doubleClicked(const QModelIndex &index);

    void on_tb_comment_doubleClicked(const QModelIndex &index);

signals:
    void updateFocusList();

private:
    Ui::UserQuestionFrame *ui;
    QString userName;
    list<Question> questionList;
    list<Comment> commentList;
    int id;
    QStandardItemModel *commentModel = nullptr;
    QStandardItemModel *questionModel = nullptr;
    MainWindow *mainWindow = nullptr;

    void getCommentList();
    void getQuestionList();
    void setTableView();
};

#endif // USERQUESTIONFRAME_H
