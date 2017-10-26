#include "modifybookinfodialog.h"
#include "ui_modifybookinfodialog.h"
#include "global.h"
#include "QDebug"
#include "QMessageBox"

ModifyBookInfoDialog::ModifyBookInfoDialog(QWidget *parent, QString isbn) :
    QDialog(parent),
    ui(new Ui::ModifyBookInfoDialog)
{
    ui->setupUi(this);
    this->ISBN=isbn;
    initViews();
}

ModifyBookInfoDialog::~ModifyBookInfoDialog()
{
    delete ui;
}

void ModifyBookInfoDialog::initViews(){
    QMap<QString,QString> book=Global::bookmanager->SearchByISBN(ISBN);
    ui->title->setText(book.value("title"));
    ui->author->setText(book.value("author"));
    ui->ISBN->setText(book.value("ISBN"));
    ui->ISBN->setEnabled(false);
    ui->number->setValue(book.value("number").toInt());
    ui->publishing_company->setText(book.value("publishing_company"));
    QTextCursor c=ui->introduction->textCursor();
    c.movePosition(QTextCursor::End);
    c.insertText(book.value("introduction"));
    c.insertBlock();

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
    int index=ui->category_box->findText(book.value("category"));
    ui->category_box->setCurrentIndex(index);
}

bool ModifyBookInfoDialog::checkInfo(){
    if(ui->title->text()==""){
        QMessageBox::warning(this,tr("警告"),tr("书名不能为空"),QMessageBox::Yes);
        return false;
    }else if(ui->author->text()==""){
        QMessageBox::warning(this,tr("警告"),tr("作者不能为空"),QMessageBox::Yes);
        return false;
    }else if(ui->publishing_company->text()==""){
        QMessageBox::warning(this,tr("警告"),tr("出版社不能为空"),QMessageBox::Yes);
        return false;
    }else if(ui->number->value()==0){
        QMessageBox::warning(this,tr("警告"),tr("数目不能为0"),QMessageBox::Yes);
        return false;
    }else{
        return true;
    }
}

void ModifyBookInfoDialog::on_btn_confirm_clicked()
{
    if(checkInfo()){
        QMap<QString,QString> book_info;
        book_info.insert("title",ui->title->text());
        book_info.insert("author",ui->author->text());
        book_info.insert("publishing_company",ui->publishing_company->text());
        book_info.insert("number",QString::number(ui->number->value()));
        book_info.insert("category",ui->category_box->currentText());
        QString introduction=ui->introduction->document()->toPlainText();
        Global::bookmanager->ModifyBookInfo(book_info,ISBN,introduction);
        this->accept();
    }
}

void ModifyBookInfoDialog::on_btn_cancel_clicked()
{
    this->close();
}
