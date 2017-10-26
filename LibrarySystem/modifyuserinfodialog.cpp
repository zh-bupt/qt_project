#include "modifyuserinfodialog.h"
#include "ui_modifyuserinfodialog.h"
#include "user.h"
#include "global.h"
#include "QMessageBox"

ModifyUserInfoDialog::ModifyUserInfoDialog(QWidget *parent,QString id) :
    QDialog(parent),
    ui(new Ui::ModifyUserInfoDialog)
{
    ui->setupUi(this);
    this->id=id;
    initViews();
    if(parent->objectName()=="UserCenterBoard"){
        ui->fine->setEnabled(false);
        ui->type->setEnabled(false);
        ui->academy->setEnabled(false);
    }
}

ModifyUserInfoDialog::~ModifyUserInfoDialog()
{
    delete ui;
}

void ModifyUserInfoDialog::initViews(){
    User user=Global::usermanager->getUser(id);
    ui->name->setText(user.getName());
    ui->id->setText(user.getId());
    ui->id->setEnabled(false);
    ui->password->setText(user.getPassword());
    ui->fine->setValue(user.getFine());

    ui->type->addItem("本科生");
    ui->type->addItem("研究生");
    ui->type->addItem("博士生");
    ui->type->addItem("老师");
    ui->type->addItem("教授");
    ui->type->setCurrentIndex(user.user_type);

    ui->academy->addItem("计算机学院");
    ui->academy->addItem("信息与通信工程学院");
    ui->academy->addItem("人文学院");
    ui->academy->addItem("数字媒体与艺术设计学院");
    ui->academy->addItem("经济管理学院");
    ui->academy->addItem("网络工程学院");
    ui->academy->addItem("信息安全学院");
    ui->academy->setCurrentIndex(user.academy);
}

bool ModifyUserInfoDialog::checkInfo(){
    if(ui->name->text()==""){
        QMessageBox::warning(this,tr("警告"),tr("姓名不能为空"),QMessageBox::Yes);
        return false;
    }else if(ui->password->text()==""){
        QMessageBox::warning(this,tr("警告"),tr("密码不能为空"),QMessageBox::Yes);
        return false;
    }else{
        return true;
    }
}

void ModifyUserInfoDialog::on_btn_comfirm_clicked()
{
    if(checkInfo()){
        QMap<QString,QString> user_info;
        user_info.insert("name",ui->name->text());
        user_info.insert("academy",QString::number(ui->academy->currentIndex()));
        user_info.insert("type",QString::number(ui->type->currentIndex()));
        user_info.insert("fine_number",QString::number(ui->fine->value()));
        user_info.insert("password",ui->password->text());
        Global::usermanager->ModifyUserInfo(user_info,id);
        this->accept();
    }
}

void ModifyUserInfoDialog::on_btn_cancel_clicked()
{
    this->close();
}

void ModifyUserInfoDialog::on_show_password_clicked()
{
    if(ui->password->echoMode()==QLineEdit::Password){
        ui->show_password->setText("隐藏");
        ui->password->setEchoMode(QLineEdit::Normal);
    }else{
        ui->show_password->setText("显示");
        ui->password->setEchoMode(QLineEdit::Password);
    }
}
