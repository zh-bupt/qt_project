#ifndef QUESTIONFRAME_H
#define QUESTIONFRAME_H

#include <QFrame>
#include <QStandardItemModel>
#include "mainwindow.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QVariant>

namespace Ui {
class QuestionFrame;
}

class MainWindow;


class QuestionFrame : public QFrame
{
    Q_OBJECT

public:
    explicit QuestionFrame(QWidget *parent = 0);
    ~QuestionFrame();

private slots:
    void on_tb_question_doubleClicked(const QModelIndex &index);

    void on_btn_question_clicked();

    void on_btn_page_pre_clicked();

    void on_btn_page_next_clicked();

signals:
    void updateFocusList();

private:
    Ui::QuestionFrame *ui;
    MainWindow *mainWindow;
    QStandardItemModel * model = nullptr;
    QSqlQueryModel *queryModel = nullptr;
    int totalRecordCount;
    int pageRecordCount = 5;
    int limitIndex;
    int currentPage;
    int totalPage;
    QSqlQuery query;

    void initViews();
    int getTotalCount();
    int getPageCount();
    void updateStatus();
    void setModel();
    void recordQuery(int limitIndex);
};

#endif // QUESTIONFRAME_H
