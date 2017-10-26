#include "myapplication.h"
#include "QDebug"
#include "QKeyEvent"
#include "QMouseEvent"

MyApplication::MyApplication(int &argc, char **argv) : QApplication(argc,argv){
}

//监测鼠标移动、键盘输入、鼠标点击事件，当发生这些事件时停止时间推进
bool MyApplication::notify(QObject *obj, QEvent *event){
    const QMetaObject* objMeta = obj->metaObject();
    QString clName = objMeta->className();

    if(event->type() == QEvent::KeyPress||event->type()==QEvent::MouseButtonPress
            ||event->type()==QEvent::MouseMove){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        //qDebug()<<keyEvent->key();
        emit hasInput();
    }
    return QApplication::notify(obj,event);
}

