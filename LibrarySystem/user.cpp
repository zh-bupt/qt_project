#include "user.h"
#include <QMap>
#include "QDebug"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonValue"
#include "QJsonParseError"
#include "QJsonArray"
#include "timethread.h"
#include "QMessageBox"
#include "global.h"

User::User(){
    isNull=true;
}

User::User(QString info)
{
    qDebug()<<"user created!!";
    QTextStream input(&info);
    input>>this->id>>this->password;
    isNull=false;
}

User::User(QJsonObject object){
    if(object.contains("name")){
        QJsonValue value=object.value("name");
        this->name=value.toString();
    }
    if(object.contains("id")){
        QJsonValue value=object.value("id");
        this->id=value.toString();
    }
    if(object.contains("password")){
        QJsonValue value=object.value("password");
        this->password=value.toString();
    }
    //读入用户类型{UNDERGRADUATE,MASTER,DOCTER,TEACHER,PROFESSOR,VISITOR}
    if(object.contains("type")){
        QJsonValue value=object.value("type");
        this->user_type=(TYPE)value.toInt();
        setAuthority();
    }
    //读入用户学院{JIKE,XINTONG,RENWEN,SHUMEI,JINGGUAN,WANGGONG,XINAN,NONE}
    if(object.contains("academy")){
        QJsonValue value=object.value("academy");
        this->academy=(ACADEMY)value.toInt();
    }
    //读入借阅书籍编号
    if(object.contains("books")){
        QJsonArray array=object.value("books").toArray();
        for(int i=0;i<array.size();i++){
            QMap<QString,QString> map;
            QJsonObject obj=array.at(i).toObject();
            if(obj.contains("ISBN"))
                map.insert("ISBN",obj.value("ISBN").toString());
            if(obj.contains("date"))
                map.insert("date",obj.value("date").toString());
            if(obj.contains("renew_times"))
                map.insert("renew_times",obj.value("renew_times").toString());
            borrowed_books.push_back(map);
        }
    }
    //读入预借书籍编号
    if(object.contains("ordered_books")){
        QJsonArray array=object.value("ordered_books").toArray();
        for(int i=0;i<array.size();i++){
            QMap<QString,QString> map;
            QJsonObject obj=array.at(i).toObject();
            if(obj.contains("isbn"))
                map.insert("isbn",obj.value("isbn").toString());
            if(obj.contains("date"))
                map.insert("date",obj.value("date").toString());
            this->ordered_books.push_back(map);
        }
    }
    //读入违约次数
    if(object.contains("fine_number"))
        this->fine_number=object.value("fine_number").toInt();

    isNull=false;
}

QJsonObject User::getUserJson(){
    QJsonObject obj;
    obj.insert("name",this->name);//存入用户名
    obj.insert("id",this->id);//存入ID
    obj.insert("password",this->password);//存入密码
    obj.insert("fine_number",this->fine_number);//存入罚款数

    //存入所借书籍的编号
    if(this->borrowed_books.size()!=0){
        QJsonArray array;
        std::vector<QMap<QString,QString>>::iterator iter=borrowed_books.begin();
        while(iter!=borrowed_books.end()){
            QJsonObject obj;
            obj.insert("ISBN",iter->value("ISBN"));
            obj.insert("date",iter->value("date"));
            obj.insert("renew_times",iter->value("renew_times"));
            array.append(obj);
            iter++;
        }
        obj.insert("books",array);
    }

    //存入所预借书籍的编号
    if(this->ordered_books.size()!=0){
        QJsonArray array;
        std::vector<QMap<QString,QString>>::iterator iter=ordered_books.begin();
        while(iter!=ordered_books.end()){
            QJsonObject obj;
            obj.insert("isbn",iter->value("isbn"));
            obj.insert("date",iter->value("date"));
            array.append(obj);
            iter++;
        }
        obj.insert("ordered_books",array);
    }

    //存入用户类型{UNDERGRADUATE,MASTER,DOCTER,TEACHER,PROFESSOR}
    obj.insert("type",this->user_type);

    //存入用户学院{JIKE,XINTONG,RENWEN,SHUMEI,JINGGUAN,WANGGONG,XINAN}
    obj.insert("academy",this->academy);
    return obj;
}
//读者权限设置
void User::setAuthority(){
    switch (this->user_type) {
    case UNDERGRADUATE:
        this->borrow_number=5;
        this->borrow_days=30;
        break;
    case MASTER:
        this->borrow_number=5;
        this->borrow_days=45;
        break;
    case DOCTER:
        this->borrow_number=10;
        this->borrow_days=60;
        break;
    case TEACHER:
        this->borrow_number=10;
        this->borrow_days=60;
        break;
    case PROFESSOR:
        this->borrow_number=15;
        this->borrow_days=90;
        break;
    }
}

int User::getNumberOfBook(){
    return this->borrowed_books.size();
}

int User::getBorrowNumber(){
    return this->borrow_number;
}

QString User::getName(){
    return this->name;
}

void User::setName(QString name){
    this->name=name;
}

QString User::getId(){
    return this->id;
}

QString User::getPassword(){
    return this->password;
}

void User::setPassword(QString password){
    this->password=password;
}

std::vector<QMap<QString,QString>> User::getBorrowedBookList(){
    std::vector<QMap<QString,QString>> list;
    std::vector<QMap<QString,QString>>::iterator iter=borrowed_books.begin();
    while(iter!=borrowed_books.end()){
        QString isbn=iter->value("ISBN");
        QMap<QString,QString> data=Global::bookmanager->SearchByISBN(isbn);
        if(data.size()!=0){
            QMap<QString,QString> map;
            map.insert("ISBN",isbn);
            map.insert("Deadline",getDeadline(isbn,0));
            map.insert("Title",data.value("title"));
            list.push_back(map);
        }else
            qDebug()<<"can't find book"+iter->value("ISBN");
        iter++;
    }
    return list;
}

std::vector<QMap<QString,QString>> User::getOrderedBookList(){
    std::vector<QMap<QString,QString>> list;
    std::vector<QMap<QString,QString>>::iterator iter=ordered_books.begin();
    while(iter!=ordered_books.end()){
        QString isbn=iter->value("isbn");
        QMap<QString,QString> data=Global::bookmanager->SearchByISBN(isbn);
        if(data.size()!=0){
            QMap<QString,QString> map;
            map.insert("ISBN",isbn);
            map.insert("Deadline",getDeadline(isbn,1));
            map.insert("Title",data.value("title"));
            list.push_back(map);
        }else
            qDebug()<<"can't find book"+iter->value("ISBN");
        iter++;
    }
    return list;
}

int User::BorrowBook(QString isbn,QString date){
    if(this->borrow_number > (int)this->borrowed_books.size()){
        QMap<QString,QString> map;
        map.insert("ISBN",isbn);
        map.insert("date",date);
        map.insert("renew_times","0");
        borrowed_books.push_back(map);
        Global::usermanager->SaveUser();
        return BORROW_SECCEEDED;
    }
    return BORROW_FAILED;
}

int User::ReturnBook(QString isbn, QString date){
    qDebug()<<"return book:"+isbn;
    std::vector<QMap<QString,QString>>::iterator iter=borrowed_books.begin();
    while(iter!=borrowed_books.end()){
        if(iter->value("ISBN")==isbn){
            qDebug()<<TimeThread::getDuration(iter->value("date"),date);
            int over_days = TimeThread::getDuration(iter->value("date"),date) - (this->borrow_days+iter->value("renew_times").toInt()*15);
            if(over_days > 0){//逾期还书，罚款！！！
                qDebug()<<"超期还书，扣积分！！！！";
                this->fine_number+=calculateFine(over_days);
                borrowed_books.erase(iter);
                return this->OVERDUE;
            }else{
                borrowed_books.erase(iter);
                return this->RETURN_SECCEEDED;
            }
        }
        iter++;
    }
    return this->BOOK_UNSEARCHED;
}

int User::RenewBook(QString isbn){
    std::vector<QMap<QString,QString>>::iterator iter=borrowed_books.begin();
    while(iter!=borrowed_books.end()){
        if(iter->value("ISBN")==isbn){
           if(iter->value("renew_times").toInt()<2){
               (*iter)["renew_times"]=QString::number(iter->value("renew_times").toInt()+1);
               return this->RENEW_SECCEEDED;
           }else{
               return this->RENEW_EXCEEDED;
           }
        }
        iter++;
    }
    return this->BOOK_UNSEARCHED;
}

//todo:
int User::HandleOrder(QString isbn){
    QDateTime ct=QDateTime::fromString(TimeThread::getCurrentTime(),"yyyyMMdd");
    std::vector<QMap<QString,QString>>::iterator iter=ordered_books.begin();
    while(iter!=ordered_books.end()){
        if(iter->value("isbn")==isbn){
            QDateTime ot=QDateTime::fromString(iter->value("date"),"yyyyMMdd");
            int duration=TimeThread::getDuration(ot,ct);
            qDebug() <<"User.cpp duration = "+QString::number(duration);
            if(duration < ORDER_DAYS){
                this->BorrowBook(isbn,ct.toString("yyyyMMdd"));
                this->ordered_books.erase(iter);
                return OK;
            }else{
                this->ordered_books.erase(iter);
                return OVERDUE;
            }
        }
        iter++;
    }
    return BOOK_UNSEARCHED;
}

void User::OrderBook(QString isbn,QString date){
    QMap<QString,QString> map;
    map.insert("isbn",isbn);
    map.insert("date",date);
    ordered_books.push_back(map);
}

QString User::getAcademy(){
    switch(academy){
    case JIKE:
        return "计算机学院";
    case XINTONG:
        return "信息与通信工程学院";
    case RENWEN:
        return "人文学院";
    case SHUMEI:
        return "数字媒体与艺术设计学院";
    case JINGGUAN:
        return "经济管理学院";
    case WANGGONG:
        return "网络工程学院";
    case XINAN:
        return "信息安全学院";
    }
    return "";
}

void User::setAcademy(ACADEMY academy){
    this->academy=academy;
}

QString User::getType(){
    switch(user_type){
    case UNDERGRADUATE:
        return "本科生";
        break;
    case MASTER:
        return "研究生";
        break;
    case DOCTER:
        return "博士";
        break;
    case TEACHER:
        return "老师";
        break;
    case PROFESSOR:
        return "教授";
        break;
    }
    return "";
}

void User::setType(TYPE type){
    this->user_type=type;
}

int User::getFine(){
    return this->fine_number;
}

void User::setFine(int fine){
    this->fine_number=fine;
}

int User::calculateFine(int days){
    if(days <= 100)
        return days;
    else
        return 100;
}


QString User::getDeadline(QString isbn,int type){
    if(type==0){//借书的应还日期
        std::vector<QMap<QString,QString>>::iterator iter=borrowed_books.begin();
        while(iter!=borrowed_books.end()){
            if(isbn==iter->value("ISBN")){
                QDateTime date_time=QDateTime::fromString(iter->value("date"),"yyyyMMdd");
                date_time=date_time.addDays(this->borrow_days+iter->value("renew_times").toInt()*15);
                return date_time.toString("yyyyMMdd");
            }
            iter++;
        }
    }

    if(type==1){
        std::vector<QMap<QString,QString>>::iterator iter=ordered_books.begin();
        while(iter!=ordered_books.end()){
            if(isbn==iter->value("isbn")){
                QDateTime date_time=QDateTime::fromString(iter->value("date"),"yyyyMMdd");
                date_time=date_time.addDays(ORDER_DAYS);
                return date_time.toString("yyyyMMdd");
            }
            iter++;
        }
    }

    return "";
}
