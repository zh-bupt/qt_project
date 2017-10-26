#include "listdialog.h"
#include "ui_listdialog.h"
#include "superuserboard.h"
#include "global.h"
#include "usermanager.h"
#include "QMap"
#include "QString"
#include "QStandardItemModel"
#include "QStandardItem"

ListDialog::ListDialog(QWidget *parent, int flag, QString tag) :
    QDialog(parent),
    ui(new Ui::ListDialog)
{
    ui->setupUi(this);
    this->flag=flag;
    this->tag=tag;
    initViews();
}

void ListDialog::initViews(){
    switch(flag){
    case SuperUserBoard::BOOK_LIST:
        disPlayBookList();
        break;
    case SuperUserBoard::USER_LIST:
        disPlayUserList();
        break;
    }
}

void ListDialog::disPlayBookList(){
    std::vector<QMap<QString,QString>> book_list=Global::usermanager->getUser(tag).getBorrowedBookList();
    int list_len=book_list.size();
    ui->list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->list->verticalHeader()->hide();
    QStandardItemModel* model=new QStandardItemModel();
    model->setRowCount(list_len);
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,"ISBN");
    model->setHeaderData(1,Qt::Horizontal,"书名");
    model->setHeaderData(2,Qt::Horizontal,"应还日期");
    int i=0;
    std::vector<QMap<QString,QString>>::iterator iter=book_list.begin();
    for (;iter!=book_list.end();iter++,i++){
        model->setItem(i,0,new QStandardItem(iter->value("ISBN")));
        model->setItem(i,1,new QStandardItem(iter->value("Title")));
        model->setItem(i,2,new QStandardItem(iter->value("Deadline")));
    }
    ui->list->setModel(model);
    ui->list->setColumnWidth(0,120);
    ui->list->setColumnWidth(1,158);
    ui->list->setColumnWidth(2,100);
    qDebug() << "the size of book list is " << book_list.size();
}

void ListDialog::disPlayUserList(){
    std::vector<Book>::iterator book_iter;
    Global::bookmanager->SearchBook(tag,book_iter);
    QList<QString> user_list=Global::bookmanager->getBorrowList(tag);
    int list_len=user_list.size();
    ui->list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->list->verticalHeader()->hide();
    QStandardItemModel* model=new QStandardItemModel();
    model->setRowCount(list_len);
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal,"学号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    int i=0;
    QList<QString>::iterator iter=user_list.begin();
    for (;iter!=user_list.end();iter++,i++){
        model->setItem(i,0,new QStandardItem(*iter));
        model->setItem(i,1,new QStandardItem(Global::usermanager->getUser(*iter).getName()));
    }
    ui->list->setModel(model);
    ui->list->setColumnWidth(0,170);
    ui->list->setColumnWidth(1,208);
    qDebug() << "the size of user list is " << user_list.size();
}


ListDialog::~ListDialog()
{
    delete ui;
}

void ListDialog::on_btn_confirm_clicked()
{

    this->close();
}
