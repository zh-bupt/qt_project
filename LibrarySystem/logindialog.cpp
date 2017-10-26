#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_login_clicked()
{
    QString s=Global::usermanager->getUser(ui->user_name->text()).getPassword();
    if(s==""){
        QMessageBox::warning(this,tr("警告!"),tr("用户名不存在"),QMessageBox::Yes);
        ui->user_name->clear();
        ui->password->clear();
        ui->user_name->setFocus();
    }
    else if(ui->password->text()==s){
        this->user_id=ui->user_name->text();
        Global::usermanager->setCurrentUser(ui->user_name->text());
        accept();
    }else{
        QMessageBox::warning(this,tr("警告!"),tr("用户名和密码不匹配!"),QMessageBox::Yes);
        ui->password->clear();
        ui->password->setFocus();
    }
}

QString LoginDialog::getUserId(){
    return this->user_id;
}

