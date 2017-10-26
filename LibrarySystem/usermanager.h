/**
  *读者管理类：
  *在该类中集中管理所有读者
  *功能包括：
  *读取、写入读者文件
  *借阅、归还图书
  *查询读者信息
**/
#ifndef USERMANAGER_H
#define USERMANAGER_H
#include<vector>
#include<QFile>
#include<QString>
#include"user.h"
#include<QDebug>

class User;

class UserManager
{
public:
    User *current_user=NULL;
    UserManager(QString file_path);
    ~UserManager();
    User getUser(QString userId);
    bool getCurrentUser(User &user);
    void setCurrentUser(QString id);
    bool SaveUser();
    void ReadUser();
    int BorrowBook(QString isbn, QString date);
    int ReturnBook(QString isbn, QString date);
    int RenewBook(QString isbn);
    void OrderBook(QString isbn,QString date);
    int HandleOrder(QString isbn);
    void ModifyUserInfo(QMap<QString,QString> info,QString id);
    bool canStillBorrowBook();//是否能继续借书
private:
    static unsigned userNumber;
    std::vector<User> userlist;
    QString file_path;
    QFile *file=NULL;
};

#endif // USERMANAGER_H
