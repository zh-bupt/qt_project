#include "usercenterboard.h"
#include "ui_usercenterboard.h"
#include "QStandardItemModel"
#include "returndialog.h"
#include "modifyuserinfodialog.h"
#include "QMessageBox"

UserCenterBoard::UserCenterBoard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UserCenterBoard)
{
    ui->setupUi(this);
    initViews();
}

UserCenterBoard::~UserCenterBoard()
{
    delete ui;
}

void UserCenterBoard::initViews(){
    QStandardItemModel *model=new QStandardItemModel();
    User user=Global::usermanager->getUser(Global::getCurrentUser());
    qDebug()<<user.getUserJson();
    model->setColumnCount(2);
    model->setRowCount(5);
    model->setItem(0,0,new QStandardItem("姓名"));
    model->setItem(0,1,new QStandardItem(user.getName()));
    model->setItem(1,0,new QStandardItem("学号"));
    model->setItem(1,1,new QStandardItem(user.getId()));
    model->setItem(2,0,new QStandardItem("学院"));
    model->setItem(2,1,new QStandardItem(user.getAcademy()));
    model->setItem(3,0,new QStandardItem("类型"));
    model->setItem(3,1,new QStandardItem(user.getType()));
    model->setItem(4,0,new QStandardItem("欠款"));
    model->setItem(4,1,new QStandardItem(QString::number(user.getFine())));
    ui->user_info->setModel(model);
    ui->book_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->book_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->user_info->setColumnWidth(0,100);
    ui->user_info->setColumnWidth(1,378);
    ui->user_info->setAutoFillBackground(true);
    ui->user_info->verticalHeader()->hide();
    ui->user_info->horizontalHeader()->hide();

    model2=new QStandardItemModel();
    std::vector<QMap<QString,QString>> info=Global::usermanager->current_user->getBorrowedBookList();
//    std::vector<Book> book_list=
//            Global::usermanager->getUser(Global::getCurrentUser()).getBorrowedBookList(Global::bookmanager);
    if(int len=info.size()!=0){
        model2->setColumnCount(4);
        model2->setRowCount(len);
        model2->setHeaderData(0,Qt::Horizontal,"ISBN");
        model2->setHeaderData(1,Qt::Horizontal,"书名");
        model2->setHeaderData(2,Qt::Horizontal,"作者");
        model2->setHeaderData(3,Qt::Horizontal,"出版社");
        int i=0;
        for(std::vector<QMap<QString,QString>>::iterator iter=info.begin();iter!=info.end();iter++,i++){
            QMap<QString,QString> map=Global::bookmanager->SearchByISBN(iter->value("ISBN"));
            model2->setItem(i,0,new QStandardItem(map.value("ISBN")));
            model2->setItem(i,1,new QStandardItem(map.value("title")));
            model2->setItem(i,2,new QStandardItem(map.value("author")));
            model2->setItem(i,3,new QStandardItem(map.value("publishing_company")));
        }
        ui->book_list->setModel(model2);
        ui->book_list->verticalHeader()->hide();
        ui->book_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->book_list->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->book_list->setColumnWidth(0,120);
        ui->book_list->setColumnWidth(1,120);
        ui->book_list->setColumnWidth(2,120);
        ui->book_list->setColumnWidth(3,118);
        ui->book_list->setAutoFillBackground(true);
    }
}

void UserCenterBoard::setUserId(QString id){
    this->user_id=id;
}

void UserCenterBoard::on_book_list_doubleClicked(const QModelIndex &index)
{
    QString ISBN=ui->book_list->model()->index(index.row(),0).data().toString();
    ReturnDialog *return_dialog=
            new ReturnDialog(this,ISBN);
    return_dialog->show();
    if(return_dialog->exec()==QDialog::Accepted){
        qDebug()<<"还书成功!";
        model2->removeRow(index.row());
    }
}

void UserCenterBoard::on_btn_edit_info_clicked()
{
    ModifyUserInfoDialog *dialog=new ModifyUserInfoDialog(this,user_id);
    dialog->setWindowTitle("修改用户信息");
    dialog->show();
    if(dialog->exec()==QDialog::Accepted){
        QMessageBox::information(this,tr("提示"),tr("修改成功！"),QMessageBox::Yes);
        this->initViews();
    }
}
