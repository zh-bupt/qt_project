#include "book.h"
#include "QJsonArray"
#include "QJsonValue"
#include "QDebug"
#include "timethread.h"

Book::Book(){

}

/**
 * @brief Book::Book
 * Book类的构造方法，通过传过来的一个 QMap 对象创建一个 Book 对象
 * @param data
 */
Book::Book(QMap<QString, QString> data){
    if(data.contains("ISBN"))
        this->ISBN=data.value("ISBN");
    if(data.contains("title"))
        this->title=data.value("title");
    if(data.contains("author"))
        this->author=data.value("author");
    if(data.contains("number"))
        this->number=data.value("number").toInt();
    if(data.contains("publishing_company"))
        this->publishing_company=data.value("publishing_company");
    if(data.contains("category"))
        this->category=data.value("category");
    if(data.contains("date"))
        this->date=data.value("date");
}

/**
 * @brief Book::Book
 * Book类的构造方法，通过传过来的一个 JsonObject 对象创建一个 Book 对象
 * @param obj
 */
Book::Book(QJsonObject obj){
    if(obj.contains("title")){
        QJsonValue value=obj.value("title");
        this->title=value.toString();
    }
    if(obj.contains("ISBN")){
        QJsonValue value=obj.value("ISBN");
        qDebug()<<value.toString();
        this->ISBN=value.toString();
    }
    if(obj.contains("author")){
        QJsonValue value=obj.value("author");
        this->author=value.toString();
    }
    if(obj.contains("publishing_company")){
        QJsonValue value=obj.value("publishing_company");
        this->publishing_company=value.toString();
    }
    if(obj.contains("number")){
        QJsonValue value=obj.value("number");
        this->number=value.toInt();
    }
    if(obj.contains("date")){
        QJsonValue value=obj.value("date");
        this->date=value.toString();
    }
    if(obj.contains("total_borrow_number")){
        QJsonValue value=obj.value("total_borrow_number");
        this->total_borrow_number=value.toInt();
    }
    if(obj.contains("borrow_list")){
        QJsonValue value=obj.value("borrow_list");
        QJsonArray array=value.toArray();
        for(int i=0;i<array.size();i++){
            this->borrow_list.push_back(array.at(i).toString());
        }
//        this->borrow_number=borrow_list.size();
    }
    if(obj.contains("order_list")){
        QJsonValue value=obj.value("order_list");
        QJsonArray array=value.toArray();
        for(int i=0;i<array.size();i++){
            QJsonObject temp=array.at(i).toObject();
            QMap<QString,QString> map;
            map.insert("user_id",temp.value("user_id").toString());
            map.insert("date",temp.value("date").toString());
            this->order_list.push_back(map);
        }
//        this->order_number=order_list.size();
    }
    if(obj.contains("category"))
        this->category=obj.value("category").toString();
    if(obj.contains("order_number"))
        this->order_number=obj.value("order_number").toInt();
    if(obj.contains("borrow_number"))
        this->borrow_number=obj.value("borrow_number").toInt();
}

/**
 * @brief Book::getBookJson
 *  得到一个 Book 对象的 JsonObject 对象
 * @return
 */
QJsonObject Book::getBookJson(){
    QJsonObject obj;
    //存入流水号、作者、书名、出版社、数量、简介、类别等信息
    obj.insert("title",this->title);
    obj.insert("ISBN",this->ISBN);
    obj.insert("author",this->author);
    obj.insert("publishing_company",this->publishing_company);
    obj.insert("number",this->number);
    obj.insert("date",this->date);
    obj.insert("category",this->category);
    obj.insert("order_number",this->order_number);
    obj.insert("borrow_number",this->borrow_number);
    obj.insert("total_borrow_number",this->total_borrow_number);
    //存入订阅列表
    QJsonArray array;
    std::vector<QMap<QString,QString>>::iterator iter=order_list.begin();
    while(iter!=order_list.end()){
        QJsonObject obj;
        obj.insert("user_id",iter->value("user_id"));
        obj.insert("date",iter->value("date"));
        array.append(obj);
        iter++;
    }
    obj.insert("order_list",array);

    //存入借阅读者列表
    QJsonArray array2;
    std::vector<QString>::iterator iter2=borrow_list.begin();
    while(iter2!=borrow_list.end()){
        array2.append(*iter2);
        iter2++;
    }
    obj.insert("borrow_list",array2);
    return obj;
}
/**
 * @brief Book::isAvailable
 * @return
 */
bool Book::isAvailable(){
    return this->getNumber() > order_number ? true : false;
}

/**
 * @brief Book::ReturnBook
 *  将 user_id 从 Book 借阅清单上抹去
 * @param user_id
 * @return
 */
bool Book::ReturnBook(QString user_id){
    std::vector<QString>::iterator iter=borrow_list.begin();
    while(iter!=borrow_list.end()){
        if(*iter==user_id){
            borrow_list.erase(iter);
            this->number++;
            this->borrow_number > 0 ? borrow_number-- : borrow_number=0;
            return true;//还书成功
        }
        iter++;
    }
    return false;//还书失败
}

/**
 * @brief Book::BorrowBook
 * 将 user_id 添加到 Book 的借阅清单上去
 * @param user_id
 * @return
 */
bool Book::BorrowBook(QString user_id){
    if(this->number>0){
        this->borrow_list.push_back(user_id);
        this->number--;
        this->borrow_number++;
        this->total_borrow_number++;
        return true;//借书成功
    }
    return false;//借书失败
}

/**
 * @brief Book::OrderBook
 * @param user_id date
 * @return
 */
void Book::OrderBook(QString user_id,QString date){
    QMap<QString,QString> map;
    map.insert("user_id",user_id);
    map.insert("date",date);
    this->order_number++;
    this->order_list.push_back(map);
}

//may be have bug
bool Book::HandleOrder(QString user_id){
    QDateTime ct=QDateTime::fromString(TimeThread::getCurrentTime(),"yyyyMMdd");
    std::vector<QMap<QString,QString>>::iterator iter=order_list.begin();
    while(iter!=order_list.end()){
        if(iter->value("user_id")==user_id){
            QDateTime ot=QDateTime::fromString(iter->value("date"),"yyyyMMdd");
            int duration=TimeThread::getDuration(ot,ct);
            if(duration < User::ORDER_DAYS){
                this->BorrowBook(user_id);
                this->order_list.erase(iter);
                this->order_number--;
                return true;
            }else{
                this->order_list.erase(iter);
                this->order_number--;
                return false;
            }
        }
        iter++;
    }
    return false;
}

/**
 * @brief Book::setNumber
 * 设置书籍的数目
 * @param number
 */
void Book::setNumber(int number){
    this->number=number;
}

/**
 * @brief Book::getTitle
 * 返回书籍标题
 * @return
 */
QString Book::getTitle(){
    return this->title;
}

/**
 * @brief Book::getISBN
 * 返回书籍的 ISBN 号
 * @return
 */
QString Book::getISBN(){
     return this->ISBN;
}

/**
 * @brief Book::getAuthor
 * 返回书籍的作者
 * @return
 */
QString Book::getAuthor(){
    return this->author;
}

/**
 * @brief Book::getPublishingCompany
 * @return
 */
QString Book::getPublishingCompany(){
     return this->publishing_company;
}

/**
 * @brief Book::getNumber
 * @return
 */
int Book::getNumber(){
     return this->number;
}

/**
 * @brief Book::getDate
 * @return
 */
QString Book::getDate(){
    return this->date;
}

/**
 * @brief Book::getCategory
 * @return
 */
QString Book::getCategory(){
    return this->category;
}

int Book::getOrderNumber(){
    return this->order_number;
}

int Book::getBorrowNumber(){
    return this->borrow_number;
}

int Book::getTotalBorrowNumber(){
    return this->total_borrow_number;
}

void Book::setAuthor(QString author){
    this->author=author;
}

void Book::setTitle(QString title){
    this->title=title;
}

void Book::setPublishingCompany(QString company){
    this->publishing_company=company;
}

void Book::setISBN(QString isbn){
    this->ISBN=isbn;
}

void Book::setCategory(QString category){
    this->category=category;
}

//QList<QString> Book::getBorrowList(){
//    QList<QString> list;
//    std::vector<QString>::iterator iter=borrow_list.begin();
//    while(iter!=borrow_list.end()){
//        list.append(*iter);
//        iter++;
//    }
//    return list;
//}

//QList<QMap<QString,QString>> Book::getOrderList(){
//    QList<QMap<QString,QString>> list;
//    std::vector<QMap<QString,QString>>::iterator iter=order_list.begin();
//    while(iter!=order_list.end()){
//        list.append(*iter);
//        iter++;
//    }
//    return list;
//}

