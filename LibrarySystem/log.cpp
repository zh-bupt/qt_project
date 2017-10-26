#include "log.h"
#include "QIODevice"
#include "QDebug"
#include "QFile"
#include "timethread.h"

Log::Log(QString file_path)
{
    qDebug()<<"log file path"+file_path;
    this->file_path=file_path;
    file=new QFile(file_path);
    this->i("Library System launched at "+TimeThread::getCurrentTime()+"\n");
}

Log::~Log(){
    file->close();
    file=NULL;
}

void Log::e(QString error){
    //file=new QFile(this->file_path);
    if(file->open(QIODevice::WriteOnly|QIODevice::Append)){
        QTextStream in(file);
        in<<"error "+TimeThread::getCurrentTime()+"\n"+error+"\n";
        file->close();
    }else{
        qDebug()<<"log文件打开失败!!";
    }
}

void Log::i(QString info){
    //file=new QFile(this->file_path);
    if(file->open(QIODevice::WriteOnly|QIODevice::Append)){
        QTextStream in(file);
        in<<"info "+TimeThread::getCurrentTime()+"\n"+info+"\n";
        file->close();
    }else{
        qDebug()<<"log文件打开失败!!";
    }
}
