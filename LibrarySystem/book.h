/**
图书分类：
A马克思主义、列宁主义、毛泽东思想、邓小平理论
B 哲学、宗教
C社会科学总论
D 政治、法律
E 军事
F 经济
G 文化、科学、教育、体育
H 语言、文字
I 文学
J 艺术
K 历史、地理
N 自然科学总论
O 数理科学和化学
P天文学、地球科学
Q 生物科学
R 医药、卫生
S 农业科学
T 工业技术
U 交通运输
V 航空、航天
X环境科学、劳动保护科学（安全科学）
Z 综合性图书
**/
#ifndef BOOK_H
#define BOOK_H

#include <vector>
#include "QString"
#include "QJsonObject"
#include "QDate"
#include "user.h"
#include "QMap"
#include "QList"
#include "enumeration.h"

class User;//前向引用申明

class Book
{
public:
    Book();
    Book(QMap<QString,QString> data);
    Book(QJsonObject obj);
    QJsonObject getBookJson();
    void setNumber(int number);
    bool ReturnBook(QString user_id);
    bool BorrowBook(QString user_id);
    bool HandleOrder(QString user_id);
    void OrderBook(QString user_id, QString date);
    QString getTitle();//返回图书书名
    void setTitle(QString title);
    QString getISBN();//返回图书ISBN号
    void setISBN(QString isbn);
    QString getAuthor();//返回图书作者
    void setAuthor(QString author);
    QString getPublishingCompany();//返回图书出版社
    void setPublishingCompany(QString company);
    QString getDate();//返回图书购入日期
    QString getCategory();//返回图书类别
    int getBorrowNumber();
    int getTotalBorrowNumber();
    void setCategory(QString category);
    int getOrderNumber();
    QList<QString> getBorrowList();
    QList<QMap<QString,QString>> getOrderList();
    int getNumber();//返回图书存量
    bool isAvailable();
    int total_borrow_number=0;
private:
    QString category;//图书类型
    QString ISBN;//图书序列号
    QString author;//图书作者名
    QString title;//图书名
    QString publishing_company;//图书出版社
    QString date;//图书购入时间
    int number;//图书数量
    int order_number=0;
    int borrow_number=0;
    std::vector<QString> borrow_list;//借阅此图书的用户列表
    std::vector<QMap<QString,QString>> order_list;//订阅此图书的读者列表
};

#endif // BOOK_H
