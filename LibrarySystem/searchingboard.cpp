#include "searchingboard.h"
#include "ui_searchingboard.h"
#include "qdebug.h"
#include "QStandardItemModel"
#include "bookdetails.h"
#include "QMessageBox"
#include "timethread.h"
#include "global.h"

SearchingBoard::SearchingBoard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SearchingBoard)
{
    ui->setupUi(this);
    initViews();
}

SearchingBoard::~SearchingBoard()
{
    delete ui;
}

void SearchingBoard::initViews(){
    ui->comboBox->addItem("ISBN");
    ui->comboBox->addItem("书名");
    ui->comboBox->addItem("作者");
    ui->comboBox->addItem("出版社");
    ui->comboBox->addItem("类别");
//    ui->comboBox->addItem("TOP 10");

    ui->category_box->addItem("文学历史");
    ui->category_box->addItem("政法经济");
    ui->category_box->addItem("军事");
    ui->category_box->addItem("艺术");
    ui->category_box->addItem("数理科学");
    ui->category_box->addItem("自然科学");
    ui->category_box->addItem("工业技术");
    ui->category_box->addItem("杂志");
    ui->category_box->addItem("报纸");
    ui->category_box->addItem("漫画");
    ui->category_box->addItem("其它");

    ui->btn_borrow->hide();
    ui->btn_subscribe->hide();
    ui->category_box->hide();

    ui->tableView->verticalHeader()->hide();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void SearchingBoard::on_btn_search_clicked()
{
    qDebug()<<"Search button pressed";
    switch (ui->comboBox->currentIndex()) {
    case 0:
        this->isbn=ui->tv_search->text();
        SearchByISBN(this->isbn);
        ui->btn_borrow->show();
        ui->btn_subscribe->show();
        break;
    case 1:
    case 2:
    case 3:
        SearchByOthers(ui->tv_search->text(),ui->comboBox->currentIndex());
        ui->btn_borrow->hide();
        ui->btn_subscribe->hide();
        break;
    case 4:{
        QString category=ui->category_box->currentText();
        SearchByOthers(category,ui->comboBox->currentIndex());
        ui->btn_borrow->hide();
        ui->btn_subscribe->hide();
        break;
    }
//    case 5:
//        ShowTop10();
//        break;
    }
}

//void SearchingBoard::ShowTop10(){
//    QList<Book> books=Global::bookmanager->getTop10();
//    if(int len=books.size()!=0){
//        ui->tableView->horizontalHeader()->show();
//        QStandardItemModel *model=new QStandardItemModel();
//        model->setColumnCount(4);
//        model->setRowCount(len);
//        ui->tableView->horizontalHeader()->show();
//        model->setHeaderData(0,Qt::Horizontal,"ISBN");
//        model->setHeaderData(1,Qt::Horizontal,"书名");
//        model->setHeaderData(2,Qt::Horizontal,"作者");
//        model->setHeaderData(3,Qt::Horizontal,"出版社");
//        int i=0;
//        for(QList<Book>::iterator iter=books.begin();iter!=books.end();iter++){
//            qDebug()<<iter->getISBN()+":"+iter->getTitle()+":"+iter->getAuthor()+":"+iter->getPublishingCompany();
//            model->setItem(i,0,new QStandardItem(iter->getISBN()));
//            model->setItem(i,1,new QStandardItem(iter->getTitle()));
//            model->setItem(i,2,new QStandardItem(iter->getAuthor()));
//            model->setItem(i,3,new QStandardItem(iter->getPublishingCompany()));
//            ui->tableView->setRowHeight(i,40);
//            i++;
//        }
//        ui->tableView->setModel(model);
//        ui->tableView->setColumnWidth(0,120);
//        ui->tableView->setColumnWidth(1,120);
//        ui->tableView->setColumnWidth(2,120);
//        ui->tableView->setColumnWidth(3,118);
//    }
//}

void SearchingBoard::on_btn_rewrite_clicked()
{
    ui->tv_search->clear();
}

void SearchingBoard::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(ui->comboBox->currentIndex()!=0){
        QModelIndex index1 = ui->tableView->model()->index(index.row(),0);
        BookDetails *a = new BookDetails(this,index1.data().toString());
        a->show();
    }
}

void SearchingBoard::SearchByOthers(QString key,int flag){
    std::vector<Book> books;
    switch (flag) {
    case 1:
        books=Global::bookmanager->SearchByTitle(key);
        break;
    case 2:
        books=Global::bookmanager->SearchByAuthor(key);
        break;
    case 3:
        books=Global::bookmanager->SearchByPublishingCompany(key);
        break;
    case 4:
        books=Global::bookmanager->SearchByCategory(key);
        break;
    }
    qDebug()<<books.size();
    if(int len=books.size()!=0){
        ui->tableView->horizontalHeader()->show();
        QStandardItemModel *model=new QStandardItemModel();
        model->setColumnCount(4);
        model->setRowCount(len);
        ui->tableView->horizontalHeader()->show();
        model->setHeaderData(0,Qt::Horizontal,"ISBN");
        model->setHeaderData(1,Qt::Horizontal,"书名");
        model->setHeaderData(2,Qt::Horizontal,"作者");
        model->setHeaderData(3,Qt::Horizontal,"出版社");
        int i=0;
        for(std::vector<Book>::iterator iter=books.begin();iter!=books.end();iter++){
            qDebug()<<iter->getISBN()+":"+iter->getTitle()+":"+iter->getAuthor()+":"+iter->getPublishingCompany();
            model->setItem(i,0,new QStandardItem(iter->getISBN()));
            model->setItem(i,1,new QStandardItem(iter->getTitle()));
            model->setItem(i,2,new QStandardItem(iter->getAuthor()));
            model->setItem(i,3,new QStandardItem(iter->getPublishingCompany()));
            ui->tableView->setRowHeight(i,40);
            i++;
        }
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0,120);
        ui->tableView->setColumnWidth(1,120);
        ui->tableView->setColumnWidth(2,120);
        ui->tableView->setColumnWidth(3,118);
    }else{
        ui->tableView->horizontalHeader()->hide();
        QStandardItemModel *model=new QStandardItemModel();
        model->setColumnCount(1);
        model->setRowCount(1);
        model->setItem(0,0,new QStandardItem("未查询到任何图书!"));
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0,478);
    }
}

void SearchingBoard::SearchByISBN(QString isbn){
    ui->tableView->horizontalHeader()->hide();
    QMap<QString,QString> book=Global::bookmanager->SearchByISBN(isbn);
    qDebug()<<book.value("title")+book.value("author");
    if(book.size()){
        QStandardItemModel *model=new QStandardItemModel();
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
        model->setItem(4,0,new QStandardItem("数量"));
        model->setItem(4,1,new QStandardItem(book.value("number")));
        ui->tableView->setModel(model);
        ui->tableView->resizeRowsToContents();
        ui->tableView->setColumnWidth(0,120);
        ui->tableView->setColumnWidth(1,358);
    }else{
        QStandardItemModel *model=new QStandardItemModel();
        model->setColumnCount(1);
        model->setRowCount(1);
        model->setItem(0,0,new QStandardItem("未查询到任何图书!"));
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0,478);
    }
}


void SearchingBoard::on_btn_borrow_clicked()
{
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
    }
}

void SearchingBoard::on_btn_subscribe_clicked()
{
    QString date=TimeThread::getCurrentTime();
    Global::bookmanager->OrderBook(Global::getCurrentUser(),isbn,date);
    Global::usermanager->OrderBook(isbn,date);
    QMessageBox::information(this,tr("提示"),tr("预借成功!!"),QMessageBox::Yes);
}


void SearchingBoard::on_comboBox_currentIndexChanged(int index)
{
    if(index==4){
        ui->category_box->show();
        ui->tv_search->hide();
    }else{
        ui->tv_search->show();
        ui->category_box->hide();
    }
}
