#include "userquestionframe.h"
#include "ui_userquestionframe.h"
#include <QSqlQuery>
#include <QVariant>
#include <QMessageBox>
#include <QDebug>
#include "questiondetailframe.h"
#include "cancelfocusdialog.h"
#include "global.h"
#include "fileexception.h"
#include <iostream>
#include "log.h"

UserQuestionFrame::UserQuestionFrame(QWidget *parent, QString userName) :
    QFrame(parent),
    ui(new Ui::UserQuestionFrame)
{
    ui->setupUi(this);
    mainWindow = (MainWindow*)parentWidget();
    this->userName = userName;
    QSqlQuery query;
    QString queryString = "select * from user where name = :name";
    query.prepare(queryString);
    query.bindValue(":name", userName);
    if (query.exec()) {
        if (query.next()) {
            this->id = query.value("id").toInt();
        }
    } else {
        QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
    }
    getCommentList();
    getQuestionList();
    setTableView();
}

UserQuestionFrame::~UserQuestionFrame()
{
    delete ui;
}

void UserQuestionFrame::on_btn_return_clicked()
{
    mainWindow->backToPreviousView();
    mainWindow->removeWidget(this);
}

void UserQuestionFrame::on_btn_cancel_focus_clicked()
{
    CancelFocusDialog *dlg = new CancelFocusDialog(this,userName);
    dlg->show();
    if (dlg->exec() == QDialog::Accepted) {
        QSqlQuery query;
        QString queryString = QString("delete from focus_list where focusing = %1 and focused = %2")
                .arg(Global::currentUser->getId())
                .arg(this->id);
        qDebug() << queryString;
        if (query.exec(queryString)) {
            QDateTime currentTime = QDateTime::currentDateTime();
            QString timeString = currentTime.toString("yyyy.MM.dd hh:mm:ss");
            std::string info = timeString.toStdString() + "::" + Global::currentUser->getName().toStdString() + "取消了对" + this->userName.toStdString() + "的关注" + "\n";
            Log log(info);
            std::cout << log;
            try {
                log.write();
            } catch (FileException &e){
                QMessageBox::warning(this, "警告", "文件打开错误", QMessageBox::Yes);
            }
            qDebug() << "删除成功";
        } else {
            QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
        }
    }
    mainWindow->backToPreviousView();
    mainWindow->removeWidget(this);
    emit updateFocusList();
}

void UserQuestionFrame::getCommentList()
{
    QSqlQuery query;
    QString queryString = "select * from comment where creator_id = :id";
    query.prepare(queryString);
    query.bindValue(":id", id);
    if (query.exec()) {
        while (query.next()) {
            QString content = query.value("context").toString();
            int praiseNum = query.value("praise_num").toInt();
            int questionId = query.value("question_id").toInt();
            QString createdTime = query.value("created_time").toString();
            Comment c = Comment(this->id, content, questionId);
            c.setPraiseNum(praiseNum);
            c.setCreatedTime(createdTime);
            //获得问题标题
            QString title;
            QSqlQuery queryTitle;
            if (queryTitle.exec(QString("select * from question where id = %1").arg(questionId))) {
                if (queryTitle.next()) {
                    title = queryTitle.value("title").toString();
                }
            } else {
                QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
            }
            qDebug() << "问题标题" << title;
            c.setQuestionTitle(title);

            commentList.push_back(c);
        }
    } else {
        QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
    }
}

void UserQuestionFrame::getQuestionList()
{
    QSqlQuery query;
    QString queryString = QString("select * from question where creator_id = %1").arg(this->id);
    if (query.exec(queryString)) {
        while (query.next()) {
            QString title = query.value("title").toString();
            QString content = query.value("context").toString();
            int id = query.value("id").toInt();
            QString createdTime = query.value("created_time").toString();

            Question q = Question(id, title, content,createdTime, userName);
            this->questionList.push_back(q);
        }
    } else {
        QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
    }
}

void UserQuestionFrame::setTableView()
{
    //加载问题列表
    questionModel = new QStandardItemModel();
    ui->tb_question->verticalHeader()->hide();
    questionModel->setColumnCount(4);
    questionModel->setHeaderData(0, Qt::Horizontal, "提问者");
    questionModel->setHeaderData(1, Qt::Horizontal, "标题");
    questionModel->setHeaderData(2, Qt::Horizontal, "时间");
    int i = 0;
    foreach (Question q, questionList) {
        questionModel->setItem(i, 0, new QStandardItem(q.getCreator()));
        questionModel->setItem(i, 1, new QStandardItem(q.getTitle()));
        questionModel->setItem(i, 2, new QStandardItem(q.getCreatedTime()));
        questionModel->setItem(i++, 3, new QStandardItem(QString::number(q.getId())));
    }

    ui->tb_question->setModel(questionModel);
    ui->tb_question->resizeRowsToContents();
    ui->tb_question->setColumnWidth(3,0);
    ui->tb_question->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tb_question->setColumnWidth(0, 98);
    ui->tb_question->setColumnWidth(1, 180);
    ui->tb_question->setColumnWidth(2, 120);

    //加载回答列表
    commentModel = new QStandardItemModel();
    ui->tb_comment->verticalHeader()->hide();
    ui->tb_comment->horizontalHeader()->hide();
    i = 0;
    foreach (Comment c, commentList) {
        commentModel->setItem(i, 0, new QStandardItem("题目:" + c.getQuestionTitle()));
        commentModel->item(i, 0)->setFont(QFont("Songti SC", 25,QFont::Black));
        commentModel->setItem(i, 1, new QStandardItem(QString::number(c.getQuestionId())));
        commentModel->item(i, 1)->setForeground(QBrush(QColor(255,255,255)));
        commentModel->setItem(i + 1, 0, new QStandardItem(c.getContext()));
        commentModel->setItem(i + 2, 0, new QStandardItem(c.getCreatedTime()));
        commentModel->setItem(i + 2, 1, new QStandardItem("点赞数:" + QString::number(c.getPraiseNum())));
        i += 4;
    }

    ui->tb_comment->setModel(commentModel);
    ui->tb_comment->setColumnWidth(0, 300);
    ui->tb_comment->setColumnWidth(1, 100);
    ui->tb_comment->resizeRowsToContents();
    ui->tb_comment->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void UserQuestionFrame::on_tb_question_doubleClicked(const QModelIndex &index)
{
    if (index.column() == 1) {
        int id = ui->tb_question->model()->index(index.row(), 3).data().toInt();
        QuestionDetailFrame *frame = new QuestionDetailFrame(mainWindow, id);
        mainWindow->setView(frame);
    }
}

void UserQuestionFrame::on_tb_comment_doubleClicked(const QModelIndex &index)
{
    int rowClicked = index.row();
    if (rowClicked % 4 == 0 && index.column() == 0){
        int questionId = commentModel->index(rowClicked, 1).data().toInt();
        QuestionDetailFrame *frame = new QuestionDetailFrame(mainWindow, questionId);
        mainWindow->setView(frame);
    }
}
