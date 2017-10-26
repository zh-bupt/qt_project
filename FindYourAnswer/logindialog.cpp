#include "logindialog.h"
#include "ui_logindialog.h"
#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include "signupdialog.h"
#include "string"
#include "fileexception.h"
#include "log.h"
#include "QDateTime"
#include <iostream>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    mainWindow = (MainWindow *) parentWidget();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

int LoginDialog::getUserId()
{
    return this->userId;
}

void LoginDialog::on_btn_login_clicked()
{
    if (ui->btn_login->text() == "登录") {
        QString name = ui->le_name->text();
        QString password = ui->le_password->text();
        QSqlQuery query;
        QString queryString = "select * from user where name =:name";
        query.prepare(queryString);
        query.bindValue(":name", name);
        if (query.exec()){
            if (query.next()){
                if (query.value("name").toString() == name && query.value("password").toString() == password){
                    this->userId = query.value("id").toInt();
                    accept();
                } else {
                    QMessageBox::warning(this, "警告", "用户名密码不匹配!", QMessageBox::Yes);
                    ui->le_password->clear();
                    qDebug() << "用户名和密码不匹配!";
                }
            } else {
                QMessageBox::information(this, "提示", "用户名不存在", QMessageBox::Yes);
                ui->le_name->clear();
                ui->le_password->clear();
            }
        } else {
            QMessageBox::warning(this,"警告","数据库错误", QMessageBox::Yes);
            qDebug() << "wrong";
        }
    }

    if (ui->btn_login->text() == "注册") {
        QString name = ui->le_name->text();
        QString password = ui->le_password->text();
        QSqlQuery query;
        QString queryString = "select * from user where name =:name";
        query.prepare(queryString);
        query.bindValue(":name", name);
        if (query.exec()){
            if (query.next()){
                QMessageBox::information(this, "提示", "该用户名已存在", QMessageBox::Yes);
                ui->le_name->clear();
            } else {
                if (password != "") {
                    QString queryString2 = QString("insert into user (name, password) values ( :name, :password)");
                    query.prepare(queryString2);
                    query.bindValue(":name", name);
                    query.bindValue(":password", password);
                    if (query.exec()) {
                        ui->btn_login->setText("登录");
                        ui->pushButton->setVisible(true);
                        //记录日志
                        QDateTime currentTime = QDateTime::currentDateTime();
                        QString timeString = currentTime.toString("yyyy.MM.dd hh:mm:ss");
                        std::string s = timeString.toStdString() + "::" + "创建用户:" + name.toStdString() + "\n";
                        Log log(s);
                        try {
                            log.write();
                        } catch (FileException &e){
                            QMessageBox::warning(this, "警告", "文件打开错误", QMessageBox::Yes);
                        }
                        std::cout << log << std::endl;

                        QMessageBox::information(this,"提示", "注册成功", QMessageBox::Yes);
                    } else {
                        QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
                    }
                } else {
                    QMessageBox::information(this, "提示", "密码为空", QMessageBox::Yes);
                }
            }
        } else {
            QMessageBox::warning(this,"警告","数据库错误", QMessageBox::Yes);
            qDebug() << "wrong";
        }
    }
}

void LoginDialog::on_btn_cancel_clicked()
{
    if (ui->btn_login->text() == "登录") {
        close();
    } else {
        ui->btn_login->setText("登录");
        ui->pushButton->setVisible(true);
    }
}



void LoginDialog::on_pushButton_clicked()
{
    ui->btn_login->setText("注册");
    ui->pushButton->setVisible(false);
}
