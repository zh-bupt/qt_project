#include "questionframe.h"
#include "ui_questionframe.h"
#include <QStandardItem>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include "questiondetailframe.h"
#include "focusdialog.h"
#include "questiondialog.h"

QuestionFrame::QuestionFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QuestionFrame)
{
    ui->setupUi(this);
    mainWindow = (MainWindow*) parentWidget();
    initViews();
//    setQuestions();
}

QuestionFrame::~QuestionFrame()
{
    if (queryModel){
        delete queryModel;
        queryModel = nullptr;
    }
    delete ui;
}

void QuestionFrame::initViews()
{
    queryModel = new QSqlQueryModel(this);
    model = new QStandardItemModel(this);
    setModel();
    currentPage = 1;
    totalRecordCount = getTotalCount();
    totalPage = getPageCount();
    updateStatus();
    recordQuery(0);
}



void QuestionFrame::on_tb_question_doubleClicked(const QModelIndex &index)
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
        int id = ui->tb_question->model()->index(index.row(), 3).data().toInt();
        QuestionDetailFrame *frame = new QuestionDetailFrame(mainWindow, id);
        mainWindow->setView(frame);
    }
}

void QuestionFrame::on_btn_question_clicked()
{
    QuestionDialog *dialog = new QuestionDialog(this);
    dialog->show();
    if (dialog->exec() == QDialog::Accepted) {
        QuestionFrame *frame = new QuestionFrame(mainWindow);
        mainWindow->setView(frame);
    }
}

int QuestionFrame::getTotalCount()
{
    queryModel->setQuery("select * from question");
    return queryModel->rowCount();
}

int QuestionFrame::getPageCount()
{
    return
            (totalRecordCount % pageRecordCount == 0) ? (totalRecordCount / pageRecordCount) : (totalRecordCount / pageRecordCount + 1);
}

void QuestionFrame::updateStatus()
{
    ui->tb_question->update();
    QString currentPageStr = QString("当前第%1页").arg(QString::number(currentPage));
    ui->lb_page->setText(currentPageStr);
    if (currentPage == 1) {
        ui->btn_page_pre->setEnabled(false);
        ui->btn_page_next->setEnabled(true);
    } else if (currentPage == totalPage)
    {
        ui->btn_page_pre->setEnabled(true);
        ui->btn_page_next->setEnabled(false);
    } else {
        ui->btn_page_pre->setEnabled(true);
        ui->btn_page_next->setEnabled(true);
    }
}

void QuestionFrame::setModel()
{
    model->clear();
    model->setColumnCount(4);
    model->setHeaderData(0, Qt::Horizontal, "提问者");
    model->setHeaderData(1, Qt::Horizontal, "标题");
    model->setHeaderData(2, Qt::Horizontal, "创建时间");
}

void QuestionFrame::recordQuery(int limitIndex)
{
    QString queryString = QString("select * from question order by created_time desc limit %1,%2")
            .arg(QString::number(limitIndex))
            .arg(QString::number(pageRecordCount));
    if (query.exec(queryString)) {
        setModel();
        int i = 0;
        while (query.next()) {
            QSqlQuery queryCreator;
            if (queryCreator.exec(QString("select * from user where id = %1").arg(query.value("creator_id").toInt()))){
                while(queryCreator.next()){
                    model->setItem(i, 0, new QStandardItem(queryCreator.value("name").toString()));
                }
            }
            model->setItem(i, 1, new QStandardItem(query.value("title").toString()));
            model->setItem(i, 2, new QStandardItem(query.value("created_time").toString()));
            model->setItem(i, 3, new QStandardItem(query.value("id").toString()));
            i++;
        }
        ui->tb_question->setModel(model);
        ui->tb_question->resizeRowsToContents();
        ui->tb_question->setColumnWidth(3,0);
        ui->tb_question->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tb_question->setColumnWidth(0, 98);
        ui->tb_question->setColumnWidth(1, 180);
        ui->tb_question->setColumnWidth(2, 120);
        for (int j = 0; j<= 4; j++) {
            ui->tb_question->setRowHeight(j,40);
        }
    }
}

void QuestionFrame::on_btn_page_pre_clicked()
{
    int limitIndex = (currentPage - 2) * pageRecordCount;
    recordQuery(limitIndex);
    currentPage -= 1;
    updateStatus();
}

void QuestionFrame::on_btn_page_next_clicked()
{
    int limitIndex = currentPage * pageRecordCount;
    recordQuery(limitIndex);
    currentPage += 1;
    updateStatus();
}
