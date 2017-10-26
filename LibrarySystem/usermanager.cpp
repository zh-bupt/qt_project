#include "usermanager.h"
#include "user.h"
#include "QTextStream"
#include "QDebug"
#include "QMessageBox"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QIODevice"
#include "QFile"
#include "global.h"

unsigned UserManager::userNumber=0;

UserManager::UserManager(QString file_path)
{
    this->file_path=file_path;
}

UserManager::~UserManager(){
    this->SaveUser();
    qDebug()<<"UserManager destoryed";
}

User UserManager::getUser(QString userId){
    file=new QFile(file_path);
    QJsonObject object;
    if(Global::ReadJson(file,object)){
        file=NULL;
        if(object.contains(userId)){
            return User(object[userId].toObject());
        }
    }
    return User();
}

bool UserManager::getCurrentUser(User &user){
    if(current_user!=NULL){
        user=*current_user;
        return true;
    }
    return false;
}

void UserManager::setCurrentUser(QString id){
    file=new QFile(file_path);
    QJsonObject object;
    if(Global::ReadJson(file,object)){
        if(object.contains(id)){
            current_user=new User(object[id].toObject());
        }
    }
    file=NULL;
}

bool UserManager::SaveUser(){
    file=new QFile(file_path);
    QJsonObject object;
    if(Global::ReadJson(file,object)){
        object.remove(current_user->getId());
        object.insert(current_user->getId(),current_user->getUserJson());
        file=new QFile(file_path);
        if(Global::WriteJson(file,object)) {
            file=NULL;
            return true;
        }
    }
    file=NULL;
    return false;
}

//返回用户能否继续借书
bool UserManager::canStillBorrowBook(){
    if(current_user->getBorrowNumber()>current_user->getNumberOfBook()) return true;
    return false;
}

int UserManager::BorrowBook(QString isbn,QString date){
    if(current_user->BorrowBook(isbn,date)==User::BORROW_SECCEEDED) {
        return User::BORROW_SECCEEDED;//借书成功
        this->SaveUser();
    }
    return User::BORROW_FAILED;//借书失败
}

int UserManager::ReturnBook(QString isbn,QString date){
    int result=current_user->ReturnBook(isbn,date);
    this->SaveUser();
    return result;
}

int UserManager::RenewBook(QString isbn){
    int result=current_user->RenewBook(isbn);
    this->SaveUser();
    return result;
}

void UserManager::OrderBook(QString isbn, QString date){
    current_user->OrderBook(isbn,date);
    this->SaveUser();
}

//todo:
int UserManager::HandleOrder(QString isbn){
    int result=current_user->HandleOrder(isbn);
    this->SaveUser();
    return result;
}

//todo:用来更改用户信息
void UserManager::ModifyUserInfo(QMap<QString, QString> info, QString id){
    if(id!=current_user->getId()){
        file=new QFile(file_path);
        QJsonObject object;
        if(Global::ReadJson(file,object)){
            file=NULL;
            if(object.contains(id)){
                QJsonObject user=object.value(id).toObject();
                qDebug() << user;
                if(info.contains("name")){
                    user.remove("name");
                    user.insert("name",info.value("name"));
                }
                if(info.contains("password")){
                    user.remove("password");
                    user.insert("password",info.value("password"));
                }
                if(info.contains("fine_number")){
                    user.remove("fine_number");
                    user.insert("fine_number",info.value("fine_number").toInt());
                }
                if(info.contains("academy")){
                    user.remove("academy");
                    user.insert("academy",info.value("academy").toInt());
                }
                if(info.contains("type")){
                    user.remove("type");
                    user.insert("type",info.value("type").toInt());
                }
                object.remove(id);
                object.insert(id,user);
                qDebug() << user;
                file=new QFile(file_path);
                Global::WriteJson(file,object);
            }
        }
        file=NULL;
    }else{
        current_user->setName(info.value("name"));
        current_user->setFine(info.value("fine_number").toInt());
        current_user->setAcademy((ACADEMY)info.value("academy").toInt());
        current_user->setType((TYPE)info.value("type").toInt());
        current_user->setPassword(info.value("password"));
        this->SaveUser();
    }
}



