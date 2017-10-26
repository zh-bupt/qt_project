/**
  *继承自QApplication类的MyApplication类
  *该类主要负责一个功能即对全局的输入(包括鼠标和键盘)
  *进行监测，然后通过信号与槽机制通知时间线程是否向前
  *推移时间
**/
#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QApplication>

class MyApplication : public QApplication
{
    Q_OBJECT
public:
    explicit MyApplication(int &argc,char **argv);
protected:
    bool notify(QObject *obj, QEvent *event);

signals:
    void hasInput();

public slots:
};

#endif // MYAPPLICATION_H
