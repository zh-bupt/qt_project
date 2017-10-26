/**
  *图书管理类：
  *在该类中集中管理所有图书
  *功能包括：
  *读取、写入图书文件
  *购入、借阅、归还图书
  *查询图书
**/
#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <vector>
#include "QFile"
#include "book.h"
#include "QString"
#include "QMap"
#include "enumeration.h"

class Book;

class BookManager
{
public:
    friend bool Compare(Book book1, Book book2);
    BookManager(QString file_path,QString introduction_file_path);
    ~BookManager();
    void SaveAllBooks();//将数据保存到文件
    void SaveBookIntroduction(QString isbn,QString introduction);
    void BuyBooks(Book &book, QString introduction);//购入图书
    QStringList getBookList();//得到图书书名的一个列表
    bool BorrowBook(QString user_id, QString ISBN);//借书
    bool ReturnBook(QString user_id, QString isbn);//还书
    bool OrderBook(QString user_id, QString isbn, QString date);//预约图书
    bool HandleOrder(QString user_id, QString isbn);
    bool isBookAvailable(QString isbn);//图书是否可借
    bool hasBook(QString isbn);
    QMap<QString,QString> SearchByISBN(QString ISBN);//通过ISBN搜索图书
    bool SearchByISBN(QString ISBN,Book &book);
    std::vector<Book> SearchByAuthor(QString author);//通过作者搜索图书
    std::vector<Book> SearchByTitle(QString title);//通过书名搜索图书
    std::vector<Book> SearchByCategory(QString category);//通过类别搜索图书
    std::vector<Book> SearchByPublishingCompany(QString publishing_company);//通过出版社搜索图书
    QString getIntroduction(QString ISBN);//返回图书简介
    QList<QString> getBorrowList(QString ISBN);
    QList<QMap<QString,QString>> getOrderList(QString ISBN);
    void ModifyBookInfo(QMap<QString,QString> info, QString isbn, QString introduction);//todo:修改图书信息
    bool SearchBook(QString isbn, std::vector<Book>::iterator &callback);
//    QList<Book> getTop10();
private:
    QString file_path;
    QString introduction_file_path;
    QFile *file=NULL;
    QFile *introduction_file=NULL;
    std::vector<Book> book_list;

};


#endif // BOOKMANAGER_H
