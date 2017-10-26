#include "messageboard.h"
#include "ui_messageboard.h"
#include "global.h"
#include "returndialog.h"
#include "bookdetails.h"

MessageBoard::MessageBoard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MessageBoard)
{
    ui->setupUi(this);
    initViews();
}

void MessageBoard::initViews(){
    ui->order_table->verticalHeader()->hide();
    ui->order_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->order_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->borrow_table->verticalHeader()->hide();
    ui->borrow_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->borrow_table->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->displayBorrowBooks();
    this->displayOrderBooks();
}

void MessageBoard::displayOrderBooks(){
    order_model=NULL;
    order_model=new QStandardItemModel();
    order_model->setColumnCount(3);
    order_model->setHeaderData(0,Qt::Horizontal,"ISBN");
    order_model->setHeaderData(1,Qt::Horizontal,"书名");
    order_model->setHeaderData(2,Qt::Horizontal,"到期日期");
    std::vector<QMap<QString,QString>> order_list=Global::usermanager->current_user->getOrderedBookList();
    qDebug()<<"预约书单size:"+QString::number(order_list.size());
    int size=order_list.size();
    order_model->setRowCount(size);
    if(size!=0){
        int i=0;
        for(std::vector<QMap<QString,QString>>::iterator iter=order_list.begin();iter!=order_list.end();iter++,i++){
            order_model->setItem(i,0,new QStandardItem(iter->value("ISBN")));
            order_model->setItem(i,1,new QStandardItem(iter->value("Title")));
            order_model->setItem(i,2,new QStandardItem(iter->value("Deadline")));
        }
    }
    ui->order_table->setModel(order_model);
    ui->order_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->order_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->order_table->setColumnWidth(0,120);
    ui->order_table->setColumnWidth(1,238);
    ui->order_table->setColumnWidth(2,120);
    ui->order_table->setAutoFillBackground(true);
}

void MessageBoard::displayBorrowBooks(){
    borrow_model=NULL;
    borrow_model=new QStandardItemModel();
    borrow_model->setColumnCount(3);
    borrow_model->setHeaderData(0,Qt::Horizontal,"ISBN");
    borrow_model->setHeaderData(1,Qt::Horizontal,"书名");
    borrow_model->setHeaderData(2,Qt::Horizontal,"应还日期");
    std::vector<QMap<QString,QString>> borrow_list=Global::usermanager->current_user->getBorrowedBookList();
    qDebug()<<"借书单size:"+QString::number(borrow_list.size());
    int size=borrow_list.size();
    borrow_model->setRowCount(size);
    if(size!=0){
        int i=0;
        for(std::vector<QMap<QString,QString>>::iterator iter=borrow_list.begin();iter!=borrow_list.end();iter++,i++){
            borrow_model->setItem(i,0,new QStandardItem(iter->value("ISBN")));
            borrow_model->setItem(i,1,new QStandardItem(iter->value("Title")));
            borrow_model->setItem(i,2,new QStandardItem(iter->value("Deadline")));
        }
    }
    ui->borrow_table->setModel(borrow_model);
    ui->borrow_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->borrow_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->borrow_table->setColumnWidth(0,120);
    ui->borrow_table->setColumnWidth(1,238);
    ui->borrow_table->setColumnWidth(2,120);
    ui->borrow_table->setAutoFillBackground(true);}

MessageBoard::~MessageBoard()
{
    delete ui;
}

void MessageBoard::on_order_table_doubleClicked(const QModelIndex &index)
{
    QString ISBN=ui->order_table->model()->index(index.row(),0).data().toString();
    qDebug()<< ISBN;
    BookDetails *details=
            new BookDetails(this,ISBN);
    details->show();
    if(details->exec()==QDialog::Accepted){
        order_model->removeRow(index.row());
        this->initViews();
    }
}

void MessageBoard::on_borrow_table_doubleClicked(const QModelIndex &index)
{
    QString ISBN=ui->borrow_table->model()->index(index.row(),0).data().toString();
    ReturnDialog *return_dialog=
            new ReturnDialog(this,ISBN);
    return_dialog->show();
    if(return_dialog->exec()==QDialog::Accepted){
        qDebug()<<"还书成功!";
        borrow_model->removeRow(index.row());
    }
}
