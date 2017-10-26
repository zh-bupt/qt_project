#include "borrowboard.h"
#include "ui_borrowboard.h"
#include "QMessageBox"
#include "timethread.h"
#include "global.h"

BorrowBoard::BorrowBoard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BorrowBoard)
{
    ui->setupUi(this);
}

BorrowBoard::~BorrowBoard()
{
    delete ui;
}

void BorrowBoard::on_btn_borrow_clicked()
{
    if(ui->t_isbn->text().isEmpty())
        QMessageBox::warning(this,tr("警告"),tr("ISBN不能为空!!"),QMessageBox::Yes);
    else{
        QString isbn=ui->t_isbn->text();
        if(!Global::bookmanager->isBookAvailable(isbn)){
            QMessageBox::warning(this,tr("警告"),tr("图书已无库存!!"),QMessageBox::Yes);
            Global::log->i(Global::getCurrentUser()+" 借阅书籍 "+isbn+"失败，因为该书籍已无库存\n");
        }else if(!Global::usermanager->canStillBorrowBook()){
            QMessageBox::warning(this,tr("警告"),tr("对不起，您所借图书已达到上限!!"),QMessageBox::Yes);
            Global::log->i(Global::getCurrentUser()+" 借阅书籍 "+isbn+" 失败，因为该用户所借书籍达到上限\n");
        }else{
            Global::bookmanager->BorrowBook(Global::getCurrentUser(),isbn);
            Global::usermanager->BorrowBook(isbn,TimeThread::getCurrentTime());
            Global::log->i(Global::getCurrentUser()+" 借阅书籍 "+isbn+" 成功\n");
            QMessageBox::information(this,tr("提示"),tr("借书成功!!"),QMessageBox::Yes);
        }
    }
}

void BorrowBoard::on_btn_clear_clicked()
{
    ui->t_isbn->clear();
}
