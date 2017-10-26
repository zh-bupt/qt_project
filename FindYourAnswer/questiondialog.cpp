#include "questiondialog.h"
#include "ui_questiondialog.h"
#include "global.h"
#include "question.h"
#include "QMessageBox"
#include "log.h"
#include "fileexception.h"
#include "string"
#include "QDebug"
#include "QDateTime"
#include "iostream"

using std::string;

QuestionDialog::QuestionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionDialog)
{
    ui->setupUi(this);
}

QuestionDialog::~QuestionDialog()
{
    delete ui;
}

void QuestionDialog::on_btn_commit_clicked()
{
    int creatorId = Global::currentUser->getId();
    QString title = ui->le_title->text();
    QString content = ui->te_context->toPlainText();
    if (title == "" || content == "") {
        QMessageBox::information(this, "提示", "标题或内容为空", QMessageBox::Yes);
    } else {
        Question q = Question(creatorId, title, content);
        QDateTime currentTime = QDateTime::currentDateTime();
        QString timeString = currentTime.toString("yyyy.MM.dd hh:mm:ss");
        std::string s = timeString.toStdString() + "::" + "创建问题:" + q.getTitle().toStdString() + "\n";
        Log log(s);
        std::cout << log << std::endl;
        try {
            log.write();
        } catch (FileException &e){
            QMessageBox::warning(this, "警告", "文件打开错误", QMessageBox::Yes);
        }
        q.save();
        accept();
    }
}

void QuestionDialog::on_btn_cancel_clicked()
{
    close();
}
