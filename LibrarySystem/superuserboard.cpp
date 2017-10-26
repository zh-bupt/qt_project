#include "superuserboard.h"
#include "ui_superuserboard.h"
#include "QMessageBox"
#include "QMap"
#include "global.h"
#include "timethread.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include "listdialog.h"
#include "modifybookinfodialog.h"
#include "modifyuserinfodialog.h"

SuperUserBoard::SuperUserBoard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SuperUserBoard)
{
    ui->setupUi(this);
    ui->user_info->horizontalHeader()->hide();
    ui->book_info->verticalHeader()->hide();
    ui->book_info->horizontalHeader()->hide();

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
}

SuperUserBoard::~SuperUserBoard()
{
    delete ui;
}

void SuperUserBoard::on_btn_confirm_clicked()
{
    QString title=ui->t_title->text();
    QString author=ui->t_author->text();
    QString publishing_company=ui->t_publishing_company->text();
    QString introduction=ui->t_introduction->document()->toPlainText();
    QString isbn=ui->t_isbn->text();
    int number=ui->number->value();
    if(title==""){
        QMessageBox::warning(this,tr("警告"),tr("书名不能为空"),QMessageBox::Yes);
        ui->t_title->setFocus();
    }else if(author==""){
        QMessageBox::warning(this,tr("警告"),tr("作者不能为空"),QMessageBox::Yes);
        ui->t_author->setFocus();
    }else if(isbn==""){
        QMessageBox::warning(this,tr("警告"),tr("ISBN不能为空"),QMessageBox::Yes);
        ui->t_isbn->setFocus();
    }else if(publishing_company==""){
        QMessageBox::warning(this,tr("警告"),tr("出版社不能为空"),QMessageBox::Yes);
        ui->t_publishing_company->setFocus();
    }else if(number==0){
        QMessageBox::warning(this,tr("警告"),tr("数量不能为零"),QMessageBox::Yes);
        ui->number->setFocus();
    }else{
        QMap<QString,QString> book_info;
        book_info.insert("title",title);
        book_info.insert("author",author);
        book_info.insert("publishing_company",publishing_company);
        book_info.insert("number",QString::number(number));
        book_info.insert("ISBN",TimeThread::getCurrentTime()+isbn);
        book_info.insert("date",TimeThread::getCurrentTime());
        book_info.insert("category",ui->category_box->currentText());
        Book book(book_info);
        Global::bookmanager->BuyBooks(book,introduction);
        QMessageBox::information(this,tr("提示"),tr("图书添加成功"),QMessageBox::Yes);
    }
}

void SuperUserBoard::on_btn_clear_clicked()
{
    ui->t_title->clear();
    ui->t_author->clear();
    ui->t_isbn->clear();
    ui->t_introduction->clear();
    ui->number->clear();
    ui->t_publishing_company->clear();
    ui->t_title->setFocus();
}

void SuperUserBoard::on_btn_search_user_clicked()
{
    user_id=ui->t_id->text();
    User user=Global::usermanager->getUser(user_id);
    if(!user.isNull){
        qDebug()<<user.getId();
        QStandardItemModel *model=new QStandardItemModel();
        qDebug()<<user.getUserJson();
        model->setColumnCount(1);
        model->setRowCount(5);
        model->setHeaderData(0,Qt::Vertical,"姓名");
        model->setHeaderData(1,Qt::Vertical,"学号");
        model->setHeaderData(2,Qt::Vertical,"学院");
        model->setHeaderData(3,Qt::Vertical,"类型");
        model->setHeaderData(4,Qt::Vertical,"欠款");
        model->setItem(0,0,new QStandardItem(user.getName()));
        model->setItem(1,0,new QStandardItem(user.getId()));
        model->setItem(2,0,new QStandardItem(user.getAcademy()));
        model->setItem(3,0,new QStandardItem(user.getType()));
        model->setItem(4,0,new QStandardItem(QString::number(user.getFine())));
        ui->user_info->setModel(model);
        ui->user_info->setColumnWidth(0,418);
        ui->user_info->setColumnWidth(1,348);
        ui->user_info->setAutoFillBackground(true);
    }else{
        QStandardItemModel *model=new QStandardItemModel();
        model->setColumnCount(1);
        model->setRowCount(1);
        model->setItem(0,0,new QStandardItem("未查询到该用户!"));
        ui->user_info->setModel(model);
        ui->user_info->setColumnWidth(0,448);
    }
}

void SuperUserBoard::on_btn_search_book_clicked()
{
    isbn=ui->t_isbn_2->text();
    Book book;
    if(Global::bookmanager->SearchByISBN(isbn,book)){
        qDebug()<<book.getISBN()<<';'<<book.getTitle();
        QStandardItemModel *model=new QStandardItemModel();
        model->setColumnCount(2);
        model->setRowCount(6);
        model->setItem(0,0,new QStandardItem("书名"));
        model->setItem(0,1,new QStandardItem(book.getTitle()));
        model->setItem(1,0,new QStandardItem("作者"));
        model->setItem(1,1,new QStandardItem(book.getAuthor()));
        model->setItem(2,0,new QStandardItem("简介"));
        model->setItem(2,1,new QStandardItem(Global::bookmanager->getIntroduction(isbn)));
        model->setItem(3,0,new QStandardItem("出版社"));
        model->setItem(3,1,new QStandardItem(book.getPublishingCompany()));
        model->setItem(4,0,new QStandardItem("数量"));
        model->setItem(4,1,new QStandardItem(QString::number(book.getNumber())));
        model->setItem(5,0,new QStandardItem("借阅人数"));
        model->setItem(5,1,new QStandardItem(QString::number(book.getBorrowNumber())));
        ui->book_info->setModel(model);
        ui->book_info->resizeRowsToContents();
        ui->book_info->autoFillBackground();
        ui->book_info->setColumnWidth(0, 120);
        ui->book_info->setColumnWidth(1, 328);
    }else{
        QStandardItemModel *model=new QStandardItemModel();
        model->setColumnCount(1);
        model->setRowCount(1);
        model->setItem(0,0,new QStandardItem("未查询到该图书!"));
        ui->book_info->setModel(model);
        ui->book_info->setColumnWidth(0,448);
    }
}

void SuperUserBoard::on_book_borrow_info_clicked()
{
    ListDialog *list_dialog=new ListDialog(this,this->USER_LIST,isbn);
    list_dialog->setWindowTitle(tr("借阅列表"));
    list_dialog->show();
}

void SuperUserBoard::on_user_borrow_info_clicked()
{
    ListDialog *list_dialog=new ListDialog(this,this->BOOK_LIST,user_id);
    list_dialog->setWindowTitle(tr("借阅列表"));
    list_dialog->show();
}

void SuperUserBoard::on_modify_book_info_clicked()
{
    ModifyBookInfoDialog *dialog=new ModifyBookInfoDialog(this,isbn);
    dialog->setWindowTitle("修改书籍信息");
    dialog->show();
    if(dialog->exec()==QDialog::Accepted){
        QMessageBox::information(this,tr("提示"),tr("修改成功！"),QMessageBox::Yes);
    }
}

void SuperUserBoard::on_modify_user_info_clicked()
{
    ModifyUserInfoDialog *dialog=new ModifyUserInfoDialog(this,user_id);
    dialog->setWindowTitle("修改用户信息");
    dialog->show();
    if(dialog->exec()==QDialog::Accepted){
        QMessageBox::information(this,tr("提示"),tr("修改成功！"),QMessageBox::Yes);
    }
}
