/**
  *Global类：
  *在该类中定义了一些重要的静态全局变量
  *包括usermanager对象，bookmanager对象，log对象，当前登录者的ID
**/
#ifndef GLOBAL_H
#define GLOBAL_H
#include "usermanager.h"
#include "bookmanager.h"
#include "log.h"
#include "QString"
#include "QDir"
#include "book.h"


class Global
{
public:
    Global();
    static UserManager *usermanager;
    static BookManager *bookmanager;
    static Log *log;
    static QDir *dir;
    static QString user_id;
    static void setCurrentUser(QString id);
    static QString getCurrentUser();
    static bool ReadJson(QFile *file,QJsonObject &object);
    static bool WriteJson(QFile *file,QJsonObject object);
};


#endif // GLOBAL_H
