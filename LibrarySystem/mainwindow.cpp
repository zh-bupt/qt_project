#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStringList"
#include "QString"
#include "QStandardItem"
#include "QDebug"
#include "QLabel"
#include "logindialog.h"
#include "QMessageBox"
#include "timethread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timethread=new TimeThread(this,1);
    timethread->start();
    connect(timethread,SIGNAL(TestSignal(QString)),this,SLOT(DisplayTime(QString)));
    ui->setupUi(this);
    this->setFixedSize(720,480);
    this->setWindowTitle("图书管理系统");
    initViews();
}

MainWindow::~MainWindow()
{
    timethread->terminate();
    Global::bookmanager->SaveAllBooks();
    Global::usermanager->SaveUser();
    delete ui;
}

void MainWindow::initViews(){
    ui->side_bar->resize(220,300);
    ui->side_bar->insertItem(0,"个人中心");
    ui->side_bar->insertItem(1,"书刊检索");
    ui->side_bar->insertItem(2,"管理员");
    ui->side_bar->insertItem(3,"通知中心");
    ui->container->resize(500,480);
    this->user_center_board=new UserCenterBoard(this);
    this->search_board=new SearchingBoard(this);
    this->superuser_board=new SuperUserBoard(this);
    QLabel *lable=new QLabel(this);
    lable->setText("对不起，你不是管理员!!");
    lable->setGeometry(470,240,50,50);
    this->message_board=new MessageBoard(this);
    ui->container->addWidget(user_center_board);
    ui->container->addWidget(search_board);
    if(Global::user_id=="2015211203"){
        ui->container->addWidget(superuser_board);
        lable->close();
    }else{
        ui->container->addWidget(lable);
        superuser_board->close();
    }
    ui->container->addWidget(message_board);
}

//注销后重新登录时用来清除原来的 UI 信息
void MainWindow::removeAllWidget(){
    ui->side_bar->clear();
    ui->container->removeWidget(user_center_board);
    this->user_center_board=NULL;
    ui->container->removeWidget(search_board);
    this->search_board=NULL;
    ui->container->removeWidget(superuser_board);
    this->superuser_board=NULL;
    ui->container->removeWidget(message_board);
    this->message_board=NULL;
}

void MainWindow::startTimeThread(){
    this->timethread->start();
}

void MainWindow::setUserId(QString user_id){
    this->user_id=user_id;
    this->user_center_board->setUserId(user_id);
    qDebug()<<user_id;
}

void MainWindow::on_logout_clicked()
{
    this->hide();
    LoginDialog dlg;
    if(dlg.exec()==QDialog::Accepted){
        this->show();
        Global::setCurrentUser(dlg.getUserId());
        this->setUserId(dlg.getUserId());
        this->removeAllWidget();
        this->initViews();
    }

//    User user=Global::usermanager->getUser("2015211203");
//    qDebug()<<user.getName()+user.getId();
}

void MainWindow::DisplayTime(QString date){
    ui->time->setText(date);
}

void MainWindow::stopTime(){
    if(timer==NULL){
         timer=new QTimer();
         QObject::connect(timer,SIGNAL(timeout()),timethread,SLOT(changeFlag()));
         timer->setInterval(5000);
         timer->start();
    }
    if(timer!=NULL){
        timethread->setFlag(false);
        timer->stop();
        timer->start();
    }else
        QMessageBox::warning(this,tr("警告!"),tr("Something got wrong!!"),QMessageBox::Yes);
}

void MainWindow::on_side_bar_currentRowChanged(int currentRow)
{
    this->RefreshUI(currentRow);
}

void MainWindow::RefreshUI(int index){
    switch(index){
    case 0:
        qDebug() << "refresh usercenterboard UI";
        this->user_center_board->initViews();
        break;
    case 3:
        qDebug() << "refresh messageboard UI";
        this->message_board->initViews();
        break;
    }
}

void MainWindow::on_skip_clicked()
{
    QString date = ui->e_date->text();
    if(date!=""){
        QDateTime time = QDateTime::fromString(date,"yyyyMMdd");
        timethread->setTime(time);
        ui->time->setText(time.toString("yyyy-MM-dd"));
    }
}
