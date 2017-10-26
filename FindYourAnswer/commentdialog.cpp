#include "commentdialog.h"
#include "ui_commentdialog.h"
#include <QSqlQuery>
#include <QVariant>
#include "comment.h"
#include "global.h"
#include <QMessageBox>
#include <QDateTime>
#include <string>
#include <log.h>
#include "fileexception.h"
#include <iostream>

CommentDialog::CommentDialog(QWidget *parent, int questionId) :
    QDialog(parent),
    ui(new Ui::CommentDialog)
{
    ui->setupUi(this);
    this->questionId = questionId;
}

CommentDialog::~CommentDialog()
{
    delete ui;
}

void CommentDialog::on_btn_commit_clicked()
{
    QString context = ui->te_comment->toPlainText();
    int creatorId = Global::currentUser->getId();
    if (context != "") {
        Comment c = Comment(creatorId, context, questionId);
        c.save();
        //写入日志
        QDateTime currentTime = QDateTime::currentDateTime();
        QString timeString = currentTime.toString("yyyy.MM.dd hh:mm:ss");
        std::string s = timeString.toStdString() + "::" + "创建回答:" + c.getContext().toStdString() + "\n";
        Log log(s);
        std::cout << log << std::endl;
        try {
            log.write();
        } catch (FileException &e){
            QMessageBox::warning(this, "警告", "文件打开错误", QMessageBox::Yes);
        }
        accept();
    } else {
        QMessageBox::information(this, "提示", "回答不能为空", QMessageBox::Yes);
    }
}

void CommentDialog::on_btn_cancel_clicked()
{
    close();
}
