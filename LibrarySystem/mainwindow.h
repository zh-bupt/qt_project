#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bookmanager.h>
#include "QStandardItemModel"
#include "QListWidgetItem"
#include "QString"
#include "usermanager.h"
#include "searchingboard.h"
#include "superuserboard.h"
#include "usercenterboard.h"
#include "messageboard.h"
#include "borrowboard.h"
#include "timethread.h"
#include "QTimer"
#include "QTableView"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUserId(QString user_id);
    void initViews();
    void startTimeThread();
    void RefreshUI(int index);
private slots:
    void on_logout_clicked();

    void DisplayTime(QString date);
    void stopTime();

    void on_side_bar_currentRowChanged(int currentRow);

    void on_skip_clicked();

private:
    void removeAllWidget();
    QStandardItemModel *model=NULL;
    Ui::MainWindow *ui;
    UserCenterBoard *user_center_board=NULL;
    SearchingBoard *search_board=NULL;
    SuperUserBoard *superuser_board=NULL;
    BorrowBoard *borrow_board=NULL;
    MessageBoard *message_board=NULL;
    TimeThread *timethread=NULL;
    QTimer *timer=NULL;
    QString user_id;
};

#endif // MAINWINDOW_H
