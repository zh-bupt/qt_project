#include "returndialog.h"
#include "ui_returndialog.h"
#include "global.h"
#include "QMap"
#include "QDateTime"
#include "timethread.h"
#include "QMessageBox"

ReturnDialog::ReturnDialog(QWidget *parent, QString isbn) :
    QDialog(parent),
    ui(new Ui::ReturnDialog)
{
    ui->setupUi(this);
    this->ISBN=isbn;
    initViews();
}

void ReturnDialog::initViews(){
    QMap<QString,QString> book=Global::bookmanager->SearchByISBN(this->ISBN);
    ui->book_info->horizontalHeader()->hide();
    ui->book_info->verticalHeader()->hide();
    ui->book_info->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if(book.size()){
        model=new QStandardItemModel();
        model->setColumnCount(2);
        model->setRowCount(5);
        model->setItem(0,0,new QStandardItem("书名"));
        model->setItem(0,1,new QStandardItem(book.value("title")));
        model->setItem(1,0,new QStandardItem("作者"));
        model->setItem(1,1,new QStandardItem(book.value("author")));
        model->setItem(2,0,new QStandardItem("简介"));
        model->setItem(2,1,new QStandardItem(book.value("introduction")));
        model->setItem(3,0,new QStandardItem("出版社"));
        model->setItem(3,1,new QStandardItem(book.value("publishing_company")));
        model->setItem(4,0,new QStandardItem("应还日期"));
        QString time=Global::usermanager->getUser(Global::getCurrentUser()).getDeadline(this->ISBN,0);
        model->setItem(4,1,new QStandardItem(time));
        ui->book_info->setModel(model);
        ui->book_info->resizeRowsToContents();
        ui->book_info->autoFillBackground();
        ui->book_info->setColumnWidth(0, 130);
        ui->book_info->setColumnWidth(1, 226);
    }}

ReturnDialog::~ReturnDialog()
{
    delete ui;
}

void ReturnDialog::on_btn_return_clicked()
{
    QString date=TimeThread::getCurrentTime();
    switch (Global::usermanager->ReturnBook(this->ISBN,date)) {
    case User::RETURN_SECCEEDED:
        QMessageBox::warning(this,tr("提示!"),tr("还书成功!!"),QMessageBox::Yes);
        break;
    case User::USER_UNSEARCHED:
        QMessageBox::warning(this,tr("提示!"),tr("用户不存在,还书失败!!"),QMessageBox::Yes);
        break;
    case User::OVERDUE:
        QMessageBox::warning(this,tr("提示!"),tr("逾期还书!!"),QMessageBox::Yes);
        break;
        break;
    case User::RETURN_FAILED:
        QMessageBox::warning(this,tr("提示!"),tr("还书失败!!"),QMessageBox::Yes);
        break;
    case User::BOOK_UNSEARCHED:
        QMessageBox::warning(this,tr("提示!"),tr("未借阅此书,还书失败!!"),QMessageBox::Yes);
        break;
    }
    Global::bookmanager->ReturnBook(Global::user_id,this->ISBN);
    Global::bookmanager->SaveAllBooks();
    Global::usermanager->SaveUser();
    accept();
}

void ReturnDialog::on_btn_renew_clicked()
{
    switch (Global::usermanager->RenewBook(this->ISBN)) {
    case User::RENEW_SECCEEDED:
        QMessageBox::warning(this,tr("提示!"),tr("续借成功!!"),QMessageBox::Yes);
        model->setItem(4,1,new QStandardItem(Global::usermanager->getUser(Global::getCurrentUser()).getDeadline(this->ISBN,0)));
        break;
    case User::USER_UNSEARCHED:
        QMessageBox::warning(this,tr("提示!"),tr("用户不存在,续借失败!!"),QMessageBox::Yes);
        break;
    case User::BOOK_UNSEARCHED:
        QMessageBox::warning(this,tr("提示!"),tr("未借阅此书,续借失败!!"),QMessageBox::Yes);
        break;
    case User::RENEW_EXCEEDED:
        QMessageBox::warning(this,tr("提示!"),tr("超过续借次数,续借失败!!"),QMessageBox::Yes);
        break;
    }
    Global::usermanager->SaveUser();
}
