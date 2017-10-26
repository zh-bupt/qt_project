/**
  *时间线程类：
  *在该类中继承自QThread类，在 run() 方法中进行时间的推移
  *功能包括：
  *时间推移
  *获取当前时间、计算两个时间之间的差值
**/
#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QThread>
#include "QDateTime"
#include "QString"

class TimeThread : public QThread
{
    Q_OBJECT
public:
    explicit TimeThread(QObject *parent = 0,int duration=10);
    ~TimeThread();
    static int getDuration(QDateTime t1,QDateTime t2);
    static int getDuration(QString t1,QString t2);
    static QString getCurrentTime();
    void setTime(QDateTime time);
    void setFlag(bool flag);
    void ToggleFlag();
protected:
    void run();
private:
    static QDateTime time;
    bool flag=true;
    int duration;
signals:
    void TestSignal(QString);

public slots:
     void changeFlag();
};

#endif // TIMETHREAD_H
