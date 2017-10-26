#include "timethread.h"
#include "QDebug"
#include "QDir"

QDateTime TimeThread::time=QDateTime::currentDateTime();

TimeThread::TimeThread(QObject *parent, int duration) : QThread(parent)
{
//    time=QDateTime::currentDateTime();
    QDir *dir=new QDir();
    QFile *time_file=new QFile(dir->absoluteFilePath("time.txt"));
    if(time_file->open(QIODevice::ReadOnly)){
        QByteArray line=time_file->readLine();
        QString time(line);
        time=time.mid(0,8);
        TimeThread::time=QDateTime::fromString(time,"yyyyMMdd");
        qDebug()<<"当前时间是:"+time;
    }else{
        qDebug()<<"时间文件打开失败！";
    }
    time_file->close();
    this->duration=duration;
}

TimeThread::~TimeThread(){
    QDir *dir=new QDir();
    QFile *time_file=new QFile(dir->absoluteFilePath("time.txt"));
    if(time_file->open(QIODevice::WriteOnly)){
        QTextStream stream(time_file);
        stream<<TimeThread::getCurrentTime();
    }else{
        qDebug()<<"时间文件打开失败！";
    }
    time_file->close();
}

void TimeThread::run(){
    while(true){
        emit TestSignal(time.toString("yyyy-MM-dd"));
        //qDebug()<<time.toString("yyyy-MM-dd");
        QThread::sleep(duration);
        this->time=this->time.addDays(1*(int)flag);
    }
}

int TimeThread::getDuration(QDateTime t1, QDateTime t2){
    return t1.msecsTo(t2)/(1000*60*60*24);
}

int TimeThread::getDuration(QString t1,QString t2){
    QDateTime date1=QDateTime::fromString(t1,"yyyyMMdd");
    QDateTime date2=QDateTime::fromString(t2,"yyyyMMdd");
    return date1.msecsTo(date2)/(1000*60*60*24);
}

void TimeThread::setFlag(bool flag){
    this->flag=flag;
}

void TimeThread::ToggleFlag(){
    this->flag=!flag;
}

void TimeThread::changeFlag(){
    flag=true;
}

QString TimeThread::getCurrentTime(){
    return time.toString("yyyyMMdd");
}

void TimeThread::setTime(QDateTime time){
    this->time=time;
}
