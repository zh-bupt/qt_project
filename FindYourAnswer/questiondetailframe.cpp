#include "questiondetailframe.h"
#include "ui_questiondetailframe.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFont>
#include "questionframe.h"
#include "commentdialog.h"
#include <QBrush>
#include <QColor>
#include "global.h"
#include <QMessageBox>
#include <QRegExp>
#include "focusdialog.h"

QuestionDetailFrame::QuestionDetailFrame(QWidget *parent, int questionId) :
    QFrame(parent),
    ui(new Ui::QuestionDetailFrame)
{
    ui->setupUi(this);
    mainWindow = (MainWindow*) parentWidget();
    this->questionId = questionId;
    question.setId(questionId);
    QSqlQuery query;
    QString queryString = "select * from question where id = :id";
    query.prepare(queryString);
    query.bindValue(":id", questionId);
    if (query.exec()) {
        while (query.next()) {
            question.setTitle(query.value("title").toString());
            question.setContext(query.value("context").toString());
        }
    }

    queryString = "select * from comment where question_id = :id";
    query.prepare(queryString);
    query.bindValue(":id", questionId);
    if (query.exec()) {
        while (query.next()) {
            int id = query.value("id").toInt();
            int creatorId = query.value("creator_id").toInt();
            QString context = query.value("context").toString();
            QString createdTIme = query.value("created_time").toString();
            int praiseNum = query.value("praise_num").toInt();
            Comment c = Comment(id,creatorId, context, createdTIme, praiseNum);
            questionComment.push_back(c);
        }
    }

    initviews();
}

QuestionDetailFrame::~QuestionDetailFrame()
{
    delete ui;
}

void QuestionDetailFrame::initviews()
{
    ui->lb_title->setText(question.getTitle());
    ui->lb_title->setFont(QFont("Songti SC", 20, QFont::Bold));
    ui->text_question->setText(question.getContext());
    model = new QStandardItemModel();
    int i = 0;
    foreach (Comment c, questionComment) {
        qDebug() << c.getId() << c.getCreator() << c.getContext() << c.getCreatedTime() << c.getPraiseNum();
        model->setItem(i, 0,new QStandardItem(c.getCreator()));
        model->item(i, 0)->setFont(QFont("Songti SC", 25,QFont::Black));
        model->setItem(i, 1, new QStandardItem(QString::number(c.getId())));
        model->item(i, 1)->setForeground(QBrush(QColor(255,255,255)));
        model->setItem(i+1, new QStandardItem(c.getContext()));
        model->setItem(i+2, 0, new QStandardItem(c.getCreatedTime()));
        model->setItem(i+2, 1, new QStandardItem("点赞数:" + QString::number(c.getPraiseNum())));
        i += 4;
    }
    ui->tb_comment->setModel(model);
    ui->tb_comment->setColumnWidth(0, 200);
    ui->tb_comment->resizeRowsToContents();
}

void QuestionDetailFrame::on_btn_comment_clicked()
{
    CommentDialog *dialog = new CommentDialog(this, questionId);
    dialog->show();
    if (dialog->exec() == QDialog::Accepted) {
        QuestionDetailFrame *frame = new QuestionDetailFrame(mainWindow, questionId);
        mainWindow->setView(frame);
        qDebug() << "评论成功";
    }
}

void QuestionDetailFrame::on_btn_back_clicked()
{
    mainWindow->removeWidget(this);
}

void QuestionDetailFrame::on_tb_comment_doubleClicked(const QModelIndex &index)
{
    int rowClicked = index.row();
    if (rowClicked % 4 == 2 && index.column() == 1) {
        int row = rowClicked - 2;
        int commentId = ui->tb_comment->model()->index(row, 1).data().toString().toInt();
        QSqlQuery query;
        QString queryString = QString("select * from praise_list where comment_id = %1 and user_id = %2")
                .arg(commentId)
                .arg(Global::currentUser->getId());
        qDebug() << queryString;
        query.exec(queryString);
        if (query.next()) {
            QMessageBox::information(this,"提示","你已经赞过此回答", QMessageBox::Yes);
            qDebug() << "已赞";
        } else {
            QString praiseString = index.data().toString();
            QRegExp reg("[0-9]+");
            reg.indexIn(praiseString);
            int praiseNum = reg.cap(0).toInt() + 1;
            QString updateString = QString("update comment set praise_num = %1 where id = %2")
                    .arg(praiseNum)
                    .arg(commentId);
            qDebug() << updateString;
            if (query.exec(updateString)){
                qDebug() << "praise success.";
                QString updatePraiseList = QString("insert into praise_list (comment_id, user_id) values ( %1, %2)")
                        .arg(commentId)
                        .arg(Global::currentUser->getId());
                qDebug() << updatePraiseList;
                if (query.exec(updatePraiseList)) {
                    qDebug() << "database success.";
                    QMessageBox::information(this,"提示","点赞成功", QMessageBox::Yes);
                } else {
                    QMessageBox::warning(this,"警告","数据库错误", QMessageBox::Yes);
                    qDebug() << "database wrong.";
                }
                model->setItem(row + 2, 1, new QStandardItem("点赞数:"+QString::number(praiseNum)));
                ui->tb_comment->update();
            } else {
                QMessageBox::warning(this,"警告","数据库错误", QMessageBox::Yes);
                qDebug() << "database wrong.";
            }
        }
    }

    if (rowClicked % 4 == 0 && index.column() == 0){
        QString userName = index.data().toString();
        FocusDialog *dlg = new FocusDialog(this,userName);
        dlg->show();
        if (dlg->exec() == QDialog::Accepted){
            emit updateFocusList();
            qDebug() << "关注成功";
        }
    }
}
