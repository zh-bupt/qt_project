#include "accountframe.h"
#include "ui_accountframe.h"
#include "questionframe.h"
#include "global.h"
#include <QSqlQuery>
#include <QVariant>
#include <QMessageBox>
#include "logindialog.h"

AccountFrame::AccountFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AccountFrame)
{
    ui->setupUi(this);
    mainWindow = (MainWindow*)parentWidget();
    ui->lb_welcome->setText(QString("欢迎:%1!").arg(Global::currentUser->getName()));
}

AccountFrame::~AccountFrame()
{
    delete ui;
}

void AccountFrame::on_btn_change_password_clicked()
{
    QString password = ui->le_new_password->text();
    if (password != ""){
        QSqlQuery query;
        QString queryString = "update user set password = :password where name = :name";
        query.prepare(queryString);
        query.bindValue(":password", password);
        query.bindValue(":name", Global::currentUser->getName());
        if (query.exec()) {
            QMessageBox::information(this,"提示", "修改成功", QMessageBox::Yes);
        } else {
            QMessageBox::warning(this,"警告", "数据库错误", QMessageBox::Yes);
        }
    } else {
        QMessageBox::information(this,"提示", "密码为空", QMessageBox::Yes);
    }

}

void AccountFrame::on_btn_logout_clicked()
{
    mainWindow->hide();
    LoginDialog * dlg = new LoginDialog();
    dlg->show();
    if (dlg->exec() == QDialog::Accepted) {
        mainWindow->show();
        Global::setCurrentUser(dlg->getUserId());
        mainWindow->setFocusList();
        mainWindow->initView();
    }
}

void AccountFrame::on_btn_return_clicked()
{
    QuestionFrame *questionFrame = new QuestionFrame(mainWindow);
    mainWindow->setView(questionFrame);
}
