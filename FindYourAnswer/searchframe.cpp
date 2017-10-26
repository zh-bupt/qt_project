#include "searchframe.h"
#include "ui_searchframe.h"
#include "questionframe.h"
#include <QStandardItem>
#include "focusdialog.h"
#include <QDebug>
#include "questiondetailframe.h"
#include <QSqlQuery>
#include <QVariant>
#include <QMessageBox>

SearchFrame::SearchFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SearchFrame)
{
    ui->setupUi(this);
    this->mainWindow = (MainWindow*)parentWidget();
    initViews();
}

SearchFrame::~SearchFrame()
{
    delete ui;
}

void SearchFrame::initViews()
{
    ui->serach_type->addItem("标题");
    ui->serach_type->addItem("时间");
    ui->tb_result->verticalHeader()->hide();
    this->model = new QStandardItemModel();
}

void SearchFrame::on_btn_search_clicked()
{
    QString title;
    QDate date;
    switch (ui->serach_type->currentIndex()) {
    case 0:
        title = this->ui->tv_title->text();
        if (title == "") {
            QMessageBox::information(this, "提示", "搜索词为空", QMessageBox::Yes);
        } else {
            search(title);
        }
        break;
    case 1:
        date = ui->date->date();
        search(date);
        break;
    }
    showResult();
}

void SearchFrame::on_btn_rewrite_clicked()
{
    this->ui->tv_title->clear();
}

void SearchFrame::showResult()
{
    int i = 0;
    model->setColumnCount(4);
    model->setHeaderData(0, Qt::Horizontal, "提问者");
    model->setHeaderData(1, Qt::Horizontal, "标题");
    model->setHeaderData(2, Qt::Horizontal, "时间");
    foreach (Question q, search_result) {
        model->setItem(i, 0, new QStandardItem(q.getCreator()));
        model->setItem(i, 1, new QStandardItem(q.getTitle()));
        model->setItem(i, 2, new QStandardItem(q.getCreatedTime()));
        model->setItem(i++, 3, new QStandardItem(QString::number(q.getId())));
    }

    ui->tb_result->setModel(model);
    ui->tb_result->resizeRowsToContents();
    ui->tb_result->setColumnWidth(3,0);
    ui->tb_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tb_result->setColumnWidth(0, 98);
    ui->tb_result->setColumnWidth(1, 180);
    ui->tb_result->setColumnWidth(2, 120);
}

void SearchFrame::on_btn_return_clicked()
{
    QuestionFrame *questionFrame = new QuestionFrame(mainWindow);
    mainWindow->setView(questionFrame);
}

void SearchFrame::on_tb_result_doubleClicked(const QModelIndex &index)
{
    if (index.column() == 0) {
        QString userName = index.data().toString();
        FocusDialog *dlg = new FocusDialog(this,userName);
        dlg->show();
        if (dlg->exec() == QDialog::Accepted){
            emit updateFocusList();
            qDebug() << "关注成功";
        }
    }

    if (index.column() == 1) {
        int id = ui->tb_result->model()->index(index.row(), 3).data().toInt();
        QuestionDetailFrame *frame = new QuestionDetailFrame(mainWindow, id);
        mainWindow->setView(frame);
    }
}

void SearchFrame::on_serach_type_currentIndexChanged(int index)
{
    if (index == 0){
        ui->date->hide();
        ui->tv_title->show();
    } else {
        ui->tv_title->hide();
        ui->date->show();
    }
}

void SearchFrame::search(QDate date)
{
    QString stringDate = transDate(date);
    qDebug() << stringDate;
    QSqlQuery query;
    QString queryString = QString("select * from question where created_time like '%1%'").arg(stringDate);
    if (query.exec(queryString)) {
        while (query.next()) {
            QString title = query.value("title").toString();
            QString content = query.value("context").toString();
            int id = query.value("id").toInt();
            QString createdTime = query.value("created_time").toString();
            int creator_id = query.value("creator_id").toInt();
            QString creator;
            QSqlQuery queryCreator;
            if (queryCreator.exec(QString("select * from user where id = %1").arg(creator_id))){
                while(queryCreator.next()){
                    creator = queryCreator.value("name").toString();
                }
            } else {
                QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
            }
            qDebug() << title << content << creator;
            Question q = Question(id, title, content,createdTime,creator);
            this->search_result.push_back(q);
        }
    } else {
        QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
    }
}

void SearchFrame::search(QString title)
{
    qDebug() << title;
    QSqlQuery query;
    QString queryString = QString("select * from question where title like '%%1%'").arg(title);
    qDebug() << queryString;
    if (query.exec(queryString)) {
        while (query.next()) {
            QString title = query.value("title").toString();
            QString content = query.value("context").toString();
            int id = query.value("id").toInt();
            QString createdTime = query.value("created_time").toString();
            int creator_id = query.value("creator_id").toInt();
            QString creator;
            QSqlQuery queryCreator;
            if (queryCreator.exec(QString("select * from user where id = %1").arg(creator_id))){
                while(queryCreator.next()){
                    creator = queryCreator.value("name").toString();
                }
            } else {
                QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
            }

            Question q = Question(id, title, content,createdTime,creator);
            this->search_result.push_back(q);
        }
    } else {
        QMessageBox::warning(this, "警告", "数据库错误", QMessageBox::Yes);
    }
}

QString SearchFrame::transDate(QDate date)
{
    QString year = QString::number(date.year());
    QString month = date.month() < 10 ? ("0" + QString::number(date.month())) : (QString::number(date.month()));
    QString day = date.day() < 10 ? ("0" + QString::number(date.day())) : (QString::number(date.day()));
    return year + "-" + month + "-" + day;
}
