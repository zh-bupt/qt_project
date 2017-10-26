#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "questionframe.h"
#include "questiondetailframe.h"
#include "searchframe.h"
#include "accountframe.h"
#include "userquestionframe.h"

namespace Ui {
class MainWindow;
}

class QuestionFrame;
class QuestionDetailFrame;
class AccountFrame;
class QuestionDetailFrame;
class SearchFrame;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setView(QWidget *widget = 0);
    void setFocusList();
    void initView();
    void backToPreviousView();
    void removeWidget(QWidget *widget);

private slots:
    void on_list_focus_list_doubleClicked(const QModelIndex &index);
    void on_btn_account_clicked();
    void updateFocusList();
    void on_btn_search_clicked();

private:
    Ui::MainWindow *ui;
    QuestionFrame *questionFrame = nullptr;
    QuestionDetailFrame *QuestionDetailFrame = nullptr;
    SearchFrame *searchFrame = nullptr;
    AccountFrame *accountFrame = nullptr;
};

#endif // MAINWINDOW_H
