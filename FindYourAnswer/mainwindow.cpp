#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "QDebug"
#include "list"
#include <QSqlQuery>
#include <QVariant>
#include <QStringListModel>
#include <QStringList>
#include "questionframe.h"
#include "user.h"
#include <QSqlQueryModel>
#include "accountframe.h"
#include "searchframe.h"
#include "userquestionframe.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Hello " << Global::currentUser->getName();
    initView();
    setFocusList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setView(QWidget *widget)
{
    connect(widget,SIGNAL(updateFocusList()),this,SLOT(updateFocusList()));
//    ui->container->removeWidget(ui->container->currentWidget());
    ui->container->addWidget(widget);
    ui->container->setCurrentWidget(widget);
}

void MainWindow::backToPreviousView()
{
    int index = ui->container->currentIndex();
    int total = ui->container->count();
    ui->container->setCurrentIndex((index - 1 + total) % total);
}

void MainWindow::removeWidget(QWidget *widget)
{
    ui->container->removeWidget(widget);
}

void MainWindow::initView()
{
    this->ui->lb_id->setText(QString("用户ID:%1").arg(Global::currentUser->getId()));
    this->ui->lb_user_name->setText(QString("用户名:%1").arg(Global::currentUser->getName()));
    ui->container->removeWidget(ui->container->currentWidget());
    QuestionFrame *questionFrame = new QuestionFrame(this);
    connect(questionFrame,SIGNAL(updateFocusList()),this,SLOT(updateFocusList()));
    ui->container->addWidget(questionFrame);
}

void MainWindow::updateFocusList()
{
    qDebug() << "update focus list";
    std::list<User> focusList;
    QSqlQuery query;
    QString queryString = "select * from focus_list where focusing = :id";
    query.prepare(queryString);
    query.bindValue(":id", Global::currentUser->getId());
    if (query.exec()){
        while(query.next()){
            int focusedId = query.value("focused").toInt();
            QSqlQuery queryUser;
            QString queryString2 = "select * from user where id = :id";
            queryUser.prepare(queryString2);
            queryUser.bindValue(":id", focusedId);
            if (queryUser.exec()) {
                while (queryUser.next()){
                    QString focusedName = queryUser.value("name").toString();
                    User u = User(focusedId, focusedName);
                    focusList.push_back(u);
                }
            }
        }
    }

    QStringListModel *model = new QStringListModel(this);
    QStringList* list = new QStringList();
    foreach (User u, focusList) {
        list->append(u.getName());
    }
    model->setStringList(*list);
    if (list){
        delete list;
        list = nullptr;
    }
    ui->list_focus_list->setModel(model);
}

void MainWindow::setFocusList()
{
    std::list<User> focusList = Global::currentUser->getFocusList();
    QStringListModel *model = new QStringListModel(this);
    QStringList* list = new QStringList();
    foreach (User u, focusList) {
        list->append(u.getName());
    }
    model->setStringList(*list);
    if (list){
        delete list;
        list = nullptr;
    }
    ui->list_focus_list->setModel(model);
}

void MainWindow::on_list_focus_list_doubleClicked(const QModelIndex &index)
{
    QString userName = index.data().toString();
    UserQuestionFrame *frame = new UserQuestionFrame(this, userName);
    this->setView(frame);
    qDebug() << "跳到用户" << userName << "的问题界面";
}


void MainWindow::on_btn_account_clicked()
{
    AccountFrame * account = new AccountFrame(this);
    this->setView(account);
}

void MainWindow::on_btn_search_clicked()
{
    SearchFrame *searchFrame = new SearchFrame(this);
    this->setView(searchFrame);
}
