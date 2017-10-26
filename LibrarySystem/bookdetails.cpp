#include "bookdetails.h"
#include "ui_bookdetails.h"
#include "QStandardItemModel"
#include "QMessageBox"
#include "timethread.h"
#include "QHeaderView"

BookDetails::BookDetails(QWidget *parent,QString isbn) :
    QDialog(parent),
    ui(new Ui::BookDetails)
{
    ui->setupUi(this);
    this->isbn=isbn;
    if(parent->objectName()=="MessageBoard"){
        this->skip_from=FROM_MESSAGE_BOARD;
    }else{
        this->skip_from=FROM_SEARCH_BOARD;
    }
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    initViews();
}

BookDetails::~BookDetails()
{
    delete ui;
}


void BookDetails::initViews(){
    if(this->skip_from==FROM_MESSAGE_BOARD){
        this->ui->orderBtn->hide();
        this->ui->borrowBtn->setText("取书");
    }
    QMap<QString,QString> book=Global::bookmanager->SearchByISBN(isbn);
    if(book.size()){
        QStandardItemModel *model=new QStandardItemModel();
        model->setColumnCount(2);
        model->setRowCount(6);
        model->setItem(0,0,new QStandardItem("书名"));
        model->setItem(0,1,new QStandardItem(book.value("title")));
        model->setItem(1,0,new QStandardItem("作者"));
        model->setItem(1,1,new QStandardItem(book.value("author")));
        model->setItem(2,0,new QStandardItem("简介"));
        model->setItem(2,1,new QStandardItem(book.value("introduction")));
        model->setItem(3,0,new QStandardItem("出版社"));
        model->setItem(3,1,new QStandardItem(book.value("publishing_company")));
        model->setItem(4,0,new QStandardItem("数量"));
        model->setItem(4,1,new QStandardItem(book.value("number")));
        model->setItem(5,0,new QStandardItem("总借阅次数"));
        model->setItem(5,1,new QStandardItem(book.value("total_borrow_number")));
        ui->tableView->setModel(model);
        ui->tableView->resizeRowsToContents();
        ui->tableView->autoFillBackground();
        ui->tableView->setColumnWidth(0, 130);
        ui->tableView->setColumnWidth(1, 226);
    }
}

void BookDetails::on_pushButton_clicked()
{
    this->close();
}

void BookDetails::on_borrowBtn_clicked()
{
    if(this->skip_from==FROM_SEARCH_BOARD){
        if(!Global::usermanager->canStillBorrowBook()){
            QMessageBox::warning(this,tr("警告"),tr("对不起，您所借图书已达到上限!!"),QMessageBox::Yes);
            Global::log->i(Global::getCurrentUser()+" 借阅书籍 "+isbn+" 失败，因为该用户所借书籍达到上限\n");
        }else if(!Global::bookmanager->isBookAvailable(isbn)){
            QMessageBox::warning(this,tr("警告"),tr("对不起，该图书已无库存!!"),QMessageBox::Yes);
            Global::log->i(Global::getCurrentUser()+" 借阅书籍 "+isbn+" 失败，因为该图书已无库存\n");
        }else{
            Global::bookmanager->BorrowBook(Global::getCurrentUser(),isbn);
            Global::usermanager->BorrowBook(isbn,TimeThread::getCurrentTime());
            Global::log->i(Global::getCurrentUser()+" 借阅书籍 "+isbn+" 成功\n");
            QMessageBox::information(this,tr("提示"),tr("借书成功!!"),QMessageBox::Yes);
            this->close();
        }
    }else{
        qDebug()<< "Handle order";
        if(!Global::bookmanager->hasBook(isbn)){
            QMessageBox::warning(this,tr("警告"),tr("此书暂时无库存，请耐心等待！"));
        }else if(Global::usermanager->HandleOrder(isbn)==User::OVERDUE){
            QMessageBox::warning(this,tr("警告"),tr("对不起，已超过取书期限，请重新预借"));
            accept();
        }else{
            QMessageBox::information(this,tr("提示"),tr("取书成功！"));
            accept();
        }
        Global::bookmanager->HandleOrder(Global::getCurrentUser(),isbn);
    }
}

void BookDetails::on_orderBtn_clicked()
{
    QString date=TimeThread::getCurrentTime();
    Global::bookmanager->OrderBook(Global::getCurrentUser(),isbn,date);
    Global::usermanager->OrderBook(isbn,date);
    QMessageBox::information(this,tr("提示"),tr("预借成功!!"),QMessageBox::Yes);
}
