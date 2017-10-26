#include "focusdialog.h"
#include "ui_focusdialog.h"
#include "global.h"
#include <QSqlQuery>
#include <QVariant>
#include <list>
#include "user.h"
#include <QDebug>
#include "global.h"
#include <string>
#include <iostream>
#include "log.h"
#include "fileexception.h"
#include <QMessageBox>
#include <QDateTime>

FocusDialog::FocusDialog(QWidget *parent, QString focusedName) :
    QDialog(parent),
    ui(new Ui::FocusDialog)
{
    ui->setupUi(this);
    this->focusedName = focusedName;
    qDebug() << focusedName;
    QSqlQuery query;
    QString queryString = "select * from user where name = :name";
    query.prepare(queryString);
    query.bindValue(":name", focusedName);
    if (query.exec()){
        while (query.next()){
            int focusedId = query.value("id").toInt();
            int focusingId = Global::currentUser->getId();
            QSqlQuery query2;
            QString queryString2 = QString("select * from focus_list where focusing = %1 and focused = %2")
                                       .arg(focusingId)
                                       .arg(focusedId);
            qDebug() << queryString2;
            query2.exec(queryString2);
            if (query2.next()) {
                ui->label->setText(QString("您已经关注过%1").arg(focusedName));
                ui->pushButton->setVisible(false);
            } else {
                ui->label->setText(QString("是否关注%1").arg(focusedName));
            }
        }
    }
}

FocusDialog::~FocusDialog()
{
    delete ui;
}

void FocusDialog::on_pushButton_clicked()
{
    std::list<User> userList = Global::currentUser->getFocusList();
    foreach (User u, userList) {
        if (u.getName() == focusedName){
            close();
            return;
        }
    }
    QSqlQuery queryUser;
    QString queryString = "select * from user where name = :name";
    queryUser.prepare(queryString);
    queryUser.bindValue(":name", focusedName);
    if (queryUser.exec()){
        while(queryUser.next()){
            int focusedId = queryUser.value("id").toInt();
            QSqlQuery queryFocusList;
            QString queryString2 = "insert into focus_list (focusing, focused) values (:focusingId, :focusedId)";
            queryFocusList.prepare(queryString2);
            queryFocusList.bindValue(":focusingId", Global::currentUser->getId());
            queryFocusList.bindValue(":focusedId", focusedId);
            if (queryFocusList.exec()){
                qDebug() << "success.";
                //记录日志
                QDateTime currentTime = QDateTime::currentDateTime();
                QString timeString = currentTime.toString("yyyy.MM.dd hh:mm:ss");
                std::string info = timeString.toStdString() + "::" + Global::currentUser->getName().toStdString() + "关注了" + focusedName.toStdString() + "\n";
                Log log(info);
                try{
                    log.write();
                } catch (FileException &e) {
                    QMessageBox::warning(this, "警告", "文件打开错误", QMessageBox::Yes);
                }
                std::cout << log;
            }
        }
    }
    accept();
}

void FocusDialog::on_pushButton_2_clicked()
{
    close();
}
