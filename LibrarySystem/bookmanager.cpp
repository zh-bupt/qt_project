#include "bookmanager.h"
#include "QDebug"
#include "QJsonDocument"
#include "QStringList"
#include "QMap"
#include "global.h"
#include "QTextStream"
#include "QJsonArray"
#include "QList"

BookManager::BookManager(QString file_path, QString introduction_file_path)
{
    this->file_path=file_path;
    this->introduction_file_path=introduction_file_path;
    qDebug()<<file_path;
    file=new QFile(file_path);
    if(file->open(QIODevice::ReadOnly)){
        qDebug()<<"book file opened!!";
        Global::log->i("file book.json opened!!\n");
        QByteArray data=file->readAll();
        QJsonParseError error;
        QJsonDocument document(QJsonDocument::fromJson(data,&error));
        qDebug()<<error.errorString();
        if(!document.isNull()&&error.error==QJsonParseError::NoError){
            if(document.isObject()){
                QJsonObject object=document.object();
                QJsonObject::iterator iter=object.begin();
                while(iter!=object.end()){
                    Book book(iter.value().toObject());
                    book_list.push_back(book);
                    iter++;
                }
            }
        }else{
            qDebug()<<"book read filed!";
            Global::log->e("file book.json read failed!!\n");
        }
        file->close();
        qDebug()<<"book file closed!";
        Global::log->i("file book.json closed!!\n");
    }else{
        qDebug()<<"file open failed!";
        Global::log->e("file book.json open failed!!\n");
    }
    file=NULL;
}

BookManager::~BookManager(){
    qDebug()<<"BookManager destoryed!!";
    this->SaveAllBooks();
}

void BookManager::SaveAllBooks(){
    qDebug()<<file_path;
    file=new QFile(file_path);
    if(!file->open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"file book.json open failed!!";
        exit(0);
    }else{
        qDebug()<<"file book.json opened!!";
        QJsonObject all;
        std::vector<Book>::iterator iter=book_list.begin();
        while(iter!=book_list.end()){
            QString ISBN=iter->getISBN();
            qDebug()<<"add book "+ISBN;
            QJsonObject obj=iter->getBookJson();
            all.insert(ISBN,obj);
            iter++;
        }
        QJsonDocument document(all);
        file->write(document.toJson());
        file->close();
        qDebug()<<"file book.json closed";
    }
    file=NULL;
}

void BookManager::SaveBookIntroduction(QString isbn,QString introduction){
    QJsonObject obj;
    introduction_file=new QFile(introduction_file_path);
    if(Global::ReadJson(introduction_file,obj)){
        if(obj.contains(isbn)){
            QJsonObject temp=obj.value(isbn).toObject();
            temp.remove("introduction");
            temp.insert("introduction",introduction);
            obj.remove(isbn);
            obj.insert(isbn,temp);
        }else{
            QJsonObject temp;
            temp.insert("introduction",introduction);
            obj.insert(isbn,temp);
        }
        introduction_file=new QFile(introduction_file_path);
        if(Global::WriteJson(introduction_file,obj)){
            qDebug()<<isbn+" 的简介添加成功！";
        }else{
            qDebug()<<isbn+" 的简介添加失败！";
        }
    }
    introduction_file=NULL;
}


void BookManager::BuyBooks(Book &book,QString introduction){
    this->book_list.push_back(book);
    this->SaveAllBooks();//保存数据
    this->SaveBookIntroduction(book.getISBN(),introduction);//Save introduction
    Global::log->i("brought book "+book.getISBN()+"-"+book.getTitle()+"\n");
 }

QStringList BookManager::getBookList(){
    QStringList strlist;
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        strlist.append(iter->getTitle());
        iter++;
    }
    return strlist;
}

QMap<QString, QString> BookManager::SearchByISBN(QString ISBN){
    QMap<QString,QString> info;
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        if(iter->getISBN()==ISBN){
            info.insert("ISBN",iter->getISBN());
             info.insert("title",iter->getTitle());
             info.insert("author",iter->getAuthor());
             info.insert("number",QString::number(iter->getNumber()));
             info.insert("publishing_company",iter->getPublishingCompany());
             info.insert("introduction",this->getIntroduction(ISBN));
             info.insert("category",iter->getCategory());
             info.insert("total_borrow_number",QString::number(iter->getTotalBorrowNumber()));
            return info;
        }
        iter++;
    }
    return info;
}

bool BookManager::SearchBook(QString isbn,std::vector<Book>::iterator &callback){
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        if(iter->getISBN()==isbn){
            callback=iter;
            return true;
        }
        iter++;
    }
    return false;
}

bool BookManager::SearchByISBN(QString ISBN, Book &book){
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        if(iter->getISBN()==ISBN){
            book=*iter;
            return true;
        }
        iter++;
    }
    return false;
}

std::vector<Book> BookManager::SearchByAuthor(QString author){
    std::vector<Book> results;
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        if(iter->getAuthor().contains(author,Qt::CaseInsensitive))
            results.push_back(*iter);
        iter++;
    }
    return results;
}

//根据书名查询图书
std::vector<Book> BookManager::SearchByTitle(QString title){
    std::vector<Book> results;
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        if(iter->getTitle().contains(title,Qt::CaseInsensitive))
            results.push_back(*iter);
        iter++;
    }
    return results;
}

//根据种类查询图书
std::vector<Book> BookManager::SearchByCategory(QString category){
    qDebug()<<"Search By Category!";
    std::vector<Book> result;
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        if(iter->getCategory()==category)
            result.push_back(*iter);
        iter++;
    }
    return result;
}

/**
 * @brief BookManager::SearchByPublishingCompany
 * @param publishing_company
 * @return
 */
std::vector<Book> BookManager::SearchByPublishingCompany(QString publishing_company){
    std::vector<Book> result;
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        if(iter->getPublishingCompany()==publishing_company)
            result.push_back(*iter);
        iter++;
    }
    return result;
}

//QList<Book> BookManager::getTop10(){
//    std::sort(book_list.begin(),book_list.end(),Compare);
//    int i=0;
//    std::vector<Book>::iterator iter=book_list.begin();
//    QList<Book> result;
//    for(;i < 10 && iter!=book_list.end();i++,iter++){
//        result.append(*iter);
//    }
//    return result;
//}

/**
 * @brief BookManager::getIntroduction
 * @param ISBN
 * @return
 */
QString BookManager::getIntroduction(QString ISBN){
    introduction_file=new QFile(introduction_file_path);
    QJsonObject obj;
    if(Global::ReadJson(introduction_file,obj)){
        introduction_file->close();
        introduction_file=NULL;
        if(obj.contains(ISBN)){
            QJsonObject book=obj.value(ISBN).toObject();
            return book.value("introduction").toString();
        }
    }else{
        qDebug()<<"introduction file open failed!";
    }
    introduction_file=NULL;
    return "";
}

//todo
QList<QString> BookManager::getBorrowList(QString ISBN){
    QList<QString> user_list;
    introduction_file=new QFile(introduction_file_path);
    QJsonObject obj;
    if(Global::ReadJson(introduction_file,obj)){
        introduction_file->close();
        introduction_file=NULL;
        if(obj.contains(ISBN)){
            QJsonObject book=obj.value(ISBN).toObject();
            QJsonArray array=book.value("borrow_list").toArray();
            for(int i=0;i<array.size();i++){
                user_list.append(array.at(i).toString());
            }
        }
    }else{
        qDebug()<<"introduction file open failed!";
    }
    introduction_file=NULL;
    return user_list;
}

QList<QMap<QString,QString>> BookManager::getOrderList(QString ISBN){
    QList<QMap<QString,QString>> user_list;
    introduction_file=new QFile(introduction_file_path);
    QJsonObject obj;
    if(Global::ReadJson(introduction_file,obj)){
        introduction_file->close();
        introduction_file=NULL;
        if(obj.contains(ISBN)){
            QJsonObject book=obj.value(ISBN).toObject();
            QJsonArray array=book.value("order_list").toArray();
            for(int i=0;i<array.size();i++){
                QJsonObject temp=array.at(i).toObject();
                QMap<QString,QString> map;
                map.insert("user_id",temp.value("user_id").toString());
                map.insert("date",temp.value("date").toString());
                user_list.append(map);
            }
        }
    }else{
        qDebug()<<"introduction file open failed!";
    }
    introduction_file=NULL;
    return user_list;
}

//图书是否可借
bool BookManager::isBookAvailable(QString isbn){
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        if(isbn==iter->getISBN()){
            if(iter->getNumber()>iter->getOrderNumber()){
                qDebug()<< isbn + "还剩余:"+iter->getOrderNumber();
                return true;
            }else{
                return false;
            }
        }
        iter++;
    }
    return false;
}

bool BookManager::hasBook(QString isbn){
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        if(isbn==iter->getISBN()){
            if(iter->getNumber() > 0){
                qDebug()<< isbn + "还剩余:"+iter->getOrderNumber();
                return true;
            }else{
                return false;
            }
        }
        iter++;
    }
    return false;
}


bool BookManager::BorrowBook(QString user_id,QString ISBN){
    std::vector<Book>::iterator iter=book_list.begin();
    while(iter!=book_list.end()){
        if(ISBN==iter->getISBN()){
            if(iter->BorrowBook(user_id)){
                introduction_file=new QFile(introduction_file_path);
                QJsonObject obj;
                if(Global::ReadJson(introduction_file,obj)){
                    introduction_file->close();
                    introduction_file=NULL;
                    if(obj.contains(ISBN)){
                        QJsonObject book=obj.value(ISBN).toObject();
                        QJsonArray array=book.value("borrow_list").toArray();
                        book.remove("borrow_list");
                        array.append(user_id);
                        book.insert("borrow_list",array);
                        obj.remove(ISBN);
                        obj.insert(ISBN,book);
                    }
                    introduction_file=new QFile(introduction_file_path);
                    if(Global::WriteJson(introduction_file,obj)){
                        qDebug()<<ISBN+" 的借阅列表更新成功！";
                    }else{
                        qDebug()<<ISBN+" 的借阅列表更新失败！";
                    }
                }else{
                    qDebug()<<"introduction file open failed!";
                }
                introduction_file=NULL;
                return true;
            }else{
                return false;
            }
        }
        iter++;
    }
    return false;
}

bool BookManager::ReturnBook(QString user_id,QString isbn){
    std::vector<Book>::iterator iter;
    if(SearchBook(isbn,iter)){
        if(iter->ReturnBook(user_id)){
            introduction_file=new QFile(introduction_file_path);
            QJsonObject obj;
            if(Global::ReadJson(introduction_file,obj)){
                introduction_file->close();
                introduction_file=NULL;
                if(obj.contains(isbn)){
                    QJsonObject book=obj.value(isbn).toObject();
                    QJsonArray array=book.value("borrow_list").toArray();
                    for(int i=0;i<array.size();i++){
                        if(array.at(i).toString()==user_id){
                            array.removeAt(i);
                        }
                    }
                    book.remove("borrow_list");
                    book.insert("borrow_list",array);
                    obj.remove(isbn);
                    obj.insert(isbn,book);
                }
                introduction_file=new QFile(introduction_file_path);
                if(Global::WriteJson(introduction_file,obj)){
                    qDebug()<<isbn+" 的借阅列表更新成功！";
                }else{
                    qDebug()<<isbn+" 的借阅列表更新失败！";
                }
            }else{
                qDebug()<<"introduction file open failed!";
            }
            introduction_file=NULL;
            this->SaveAllBooks();
            return true;
        }else
            return false;
    }
    return false;
}

bool BookManager::OrderBook(QString user_id, QString isbn,QString date){
    std::vector<Book>::iterator iter;
    if(SearchBook(isbn,iter)){
        qDebug() << "预借图书："+iter->getTitle();
        iter->OrderBook(user_id,date);
        //更新 order list
        introduction_file=new QFile(introduction_file_path);
        QJsonObject obj;
        if(Global::ReadJson(introduction_file,obj)){
            introduction_file->close();
            introduction_file=NULL;
            if(obj.contains(isbn)){
                QJsonObject book=obj.value(isbn).toObject();
                QJsonArray array=book.value("order_list").toArray();
                QJsonObject order;
                order.insert("date",date);
                order.insert("user_id",user_id);
                array.append(order);
                book.remove("order_list");
                book.insert("order_list",array);
                obj.remove(isbn);
                obj.insert(isbn,book);
            }
            introduction_file=new QFile(introduction_file_path);
            if(Global::WriteJson(introduction_file,obj)){
                qDebug()<<isbn+" 的预约列表更新成功！";
            }else{
                qDebug()<<isbn+" 的预约列表更新失败！";
            }
        }else{
            qDebug()<<"introduction file open failed!";
        }
        introduction_file=NULL;
        this->SaveAllBooks();
        return true;
    }
    return false;
}

//may have bug
bool BookManager::HandleOrder(QString user_id, QString isbn){
    std::vector<Book>::iterator iter;
    if(SearchBook(isbn,iter)){
        bool result;
        if(iter->HandleOrder(user_id)){
            result=true;
        }else{
            result=false;
        }
        //更新 order list
        introduction_file=new QFile(introduction_file_path);
        QJsonObject obj;
        if(Global::ReadJson(introduction_file,obj)){
            introduction_file->close();
            introduction_file=NULL;
            if(obj.contains(isbn)){
                QJsonObject book=obj.value(isbn).toObject();
                QJsonArray array=book.value("order_list").toArray();
                for (int i=0;i<array.size();i++){
                    QJsonObject temp=array.at(i).toObject();
                    if(temp.value("user_id").toString()==user_id){
                        array.removeAt(i);
                    }
                }
                book.remove("order_list");
                book.insert("order_list",array);
                obj.remove(isbn);
                obj.insert(isbn,book);
            }
            introduction_file=new QFile(introduction_file_path);
            if(Global::WriteJson(introduction_file,obj)){
                qDebug()<<isbn+" 的预约列表更新成功！";
            }else{
                qDebug()<<isbn+" 的预约列表更新失败！";
            }
        }else{
            qDebug()<<"introduction file open failed!";
        }
        introduction_file=NULL;

        //更新借阅列表
        if(result){
            introduction_file=new QFile(introduction_file_path);
            QJsonObject obj;
            if(Global::ReadJson(introduction_file,obj)){
                introduction_file->close();
                introduction_file=NULL;
                if(obj.contains(isbn)){
                    QJsonObject book=obj.value(isbn).toObject();
                    QJsonArray array=book.value("borrow_list").toArray();
                    book.remove("borrow_list");
                    array.append(user_id);
                    book.insert("borrow_list",array);
                    obj.remove(isbn);
                    obj.insert(isbn,book);
                }
                introduction_file=new QFile(introduction_file_path);
                if(Global::WriteJson(introduction_file,obj)){
                    qDebug()<<isbn+" 的借阅列表更新成功！";
                }else{
                    qDebug()<<isbn+" 的借阅列表更新失败！";
                }
            }else{
                qDebug()<<"introduction file open failed!";
            }
            introduction_file=NULL;
        }

        this->SaveAllBooks();
        return result;
    }
    return false;
}

//todo:修改书籍的信息
void BookManager::ModifyBookInfo(QMap<QString, QString> info, QString isbn,QString introduction){
    std::vector<Book>::iterator book;
    if(this->SearchBook(isbn,book)){
        if(info.contains("title")){
            book->setTitle(info.value("title"));
        }
        if(info.contains("author")){
            book->setAuthor(info.value("author"));
        }
        if(info.contains("publishing_company")){
            book->setPublishingCompany(info.value("publishing_company"));
        }
        if(info.contains("category")){
            book->setCategory(info.value("category"));
        }
        if(info.contains("number")){
            book->setNumber(info.value("number").toInt());
        }
        this->SaveBookIntroduction(isbn,introduction);//modify introduction
        this->SaveAllBooks();
    }
}

//bool Compare(const Book &book1, const Book &book2){
//    return (book1.total_borrow_number >= book2.total_borrow_number);
//}
