#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include "logindialog.h"
#include "global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Global global;
    //创建一个sqlite数据库链接
    QSqlDatabase db;
    if (QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("test.db");
        db.setUserName("root");
        db.setPassword("123456");
    }
    if(!db.open())
        qDebug() << "database open failed!";
    else{
        qDebug() << "database open succeeded!";
        LoginDialog loginDialog;
        if (loginDialog.exec() == QDialog::Accepted){
            Global::setCurrentUser(loginDialog.getUserId());
            MainWindow w;
            w.show();
            return a.exec();
        }
    }
    db.close();
    return a.exec();
}
