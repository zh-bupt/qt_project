#include "global.h"
#include "qdebug.h"
#include "QJsonParseError"
#include "QJsonDocument"

QDir* Global::dir=new QDir();
Log* Global::log=
        new Log(Global::dir->absoluteFilePath("log.txt"));
BookManager* Global::bookmanager=
        new BookManager(Global::dir->absoluteFilePath("book.json"),Global::dir->absoluteFilePath("introduction.dat"));
UserManager* Global::usermanager=
        new UserManager(Global::dir->absoluteFilePath("user.json"));
QString Global::user_id="";

Global::Global()
{
}
void Global::setCurrentUser(QString id){
    qDebug()<<"current user"+id;
    user_id=id;
}

QString Global::getCurrentUser(){
    qDebug()<<"current user"+user_id;
    return user_id;
}

bool Global::ReadJson(QFile *file, QJsonObject &object){
    if(file!=NULL){
        if(file->open(QIODevice::ReadOnly)){
            qDebug()<<"file opened!!";
            QByteArray data=file->readAll();
            QJsonParseError error;
            QJsonDocument document(QJsonDocument::fromJson(data,&error));
            if(!document.isNull()&&error.error==QJsonParseError::NoError){
                if(document.isObject()){
                    object=document.object();
                    return true;
                }
            }else{
                qDebug()<<"book read filed!"+error.errorString();
                Global::log->e("file read failed!!\n");
            }
            file->close();
            qDebug()<<"file closed!";
        }else{
            qDebug()<<"file open failed!";
            Global::log->e("file open failed!!\n");
        }
    }
    return false;
}

bool Global::WriteJson(QFile *file,QJsonObject object){
    if(file!=NULL){
        if(file->open(QIODevice::WriteOnly)){
            qDebug()<<"file opened!!";
            QJsonDocument document(object);
            file->write(document.toJson());
            file->close();
            qDebug()<<"book file closed!";
            return true;
        }else{
            qDebug()<<"file open failed!";
            Global::log->e("file open failed!!\n");
        }
    }
    return false;
}



