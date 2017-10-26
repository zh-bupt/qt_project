#ifndef USER_H
#define USER_H

#include <QString>
#include <vector>
#include "QJsonValue"
#include "QJsonObject"
#include "QMap"
#include "book.h"
#include "bookmanager.h"
#include "enumeration.h"
#include "QDateTime"

class Book;
class BookManager;

class User{
public:
    static const int OVERDUE=0x11110;
    static const int BOOK_UNSEARCHED=0x11111;
    static const int RETURN_SECCEEDED=0x11112;
    static const int RETURN_FAILED=0x11116;
    static const int BORROW_SECCEEDED=0x11113;
    static const int BORROW_FAILED=0x11114;
    static const int USER_UNSEARCHED=0x11115;
    static const int RENEW_SECCEEDED=0x11116;
    static const int RENEW_EXCEEDED=0x11117;
    static const int OK=0x11120;
    static const int ORDER_DAYS=45;

    User();
    User(QString info);
    User(QJsonObject object);//通过一个Json对象创建User类
    QJsonObject getUserJson();//返回一个User类的所有信息到一个Json对象中
    int getNumberOfBook();//返回借阅书籍的总数
    int getBorrowNumber();//返回所能借阅的图书数量
    QString getId();
    QString getPassword();
    void setPassword(QString password);
    QString getName();
    void setName(QString name);
    QString getAcademy();
    void setAcademy(ACADEMY academy);
    QString getType();
    void setType(TYPE type);
    int getFine();
    void setFine(int fine);
    QString getDeadline(QString isbn, int type);
    std::vector<QMap<QString,QString>> getBorrowedBookList();
    std::vector<QMap<QString,QString>> getOrderedBookList();
    int BorrowBook(QString isbn,QString date);
    int ReturnBook(QString isbn,QString date);
    int RenewBook(QString isbn);
    void OrderBook(QString isbn,QString date);
    int HandleOrder(QString isbn);
    void setAuthority();
    bool isNull=true;
    TYPE user_type;//用户类型
    ACADEMY academy;//用户所属院系
private:
    int calculateFine(int days);
    QString name;//新加的成员变量，表示用户姓名
    QString id;
    QString password;
    int fine_number=0;//新增的成员变量，表示欠款数
    int borrow_number;//用户所能同时借数的最大值
    int borrow_days;//用户每本数所能借的最长时间
    std::vector<QMap<QString,QString>> borrowed_books;//用户所借书的书单，只包括序列号和借书日期
    std::vector<QMap<QString,QString>> ordered_books;//用户所预约的书单，包含了序列号和预约日期
};

#endif // USER_H
