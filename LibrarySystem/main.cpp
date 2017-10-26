#include "mainwindow.h"
#include "myapplication.h"
#include "logindialog.h"
#include "QObject"
#include "global.h"
#include "usermanager.h"
#include "bookmanager.h"

int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);
    Global global;
    LoginDialog dlg;
    if(dlg.exec()==QDialog::Accepted){
        Global::setCurrentUser(dlg.getUserId());
        MainWindow w;
        QObject::connect(&a,SIGNAL(hasInput()),&w,SLOT(stopTime()));
        w.setUserId(dlg.getUserId());
        w.show();
        return a.exec();
    }else{
        return a.exec();
    }
}
