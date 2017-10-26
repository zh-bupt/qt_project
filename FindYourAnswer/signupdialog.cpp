#include "signupdialog.h"
#include "ui_signupdialog.h"
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QMessageBox>

SignupDialog::SignupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignupDialog)
{
    ui->setupUi(this);
}

SignupDialog::~SignupDialog()
{
    delete ui;
}

void SignupDialog::on_btn_signup_clicked()
{
    QString userName = ui->le_user_name->text();
    QString password = ui->le_password->text();
    QSqlQuery query;
    if (query.exec(QString("select * from user where name = %1").arg(userName))) {
        if (query.next()) {
            QMessageBox::information(this, "提示", "该用户名已存在", QMessageBox::Yes);
            ui->le_user_name->clear();
        } else {
            if (password != "") {
                if (query.exec(QString("insert into user (name, password) values ( %1, %2)").arg(userName).arg(password))) {
                    accept();
                } else {
                    QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
                }
            } else {
                QMessageBox::information(this, "提示", "密码为空", QMessageBox::Yes);
            }
        }
    } else {
        if (password != "") {
            if (query.exec(QString("insert into user (name, password) values ( %1, %2)").arg(userName).arg(password))) {
                accept();
            } else {
                QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
            }
        } else {
            QMessageBox::information(this, "提示", "密码为空", QMessageBox::Yes);
        }
        QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
    }
}

void SignupDialog::on_btn_cancel_clicked()
{
    close();
}
