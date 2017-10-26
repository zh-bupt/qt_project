#ifndef SEARCHFRAME_H
#define SEARCHFRAME_H

#include <QFrame>
#include <list>
#include "question.h"
#include <QDate>
#include <QString>
#include "mainwindow.h"
#include "QStandardItemModel"

using std::list;

namespace Ui {
class SearchFrame;
}

class MainWindow;

class SearchFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SearchFrame(QWidget *parent = 0);
    ~SearchFrame();
    void search(QString title);
    void search(QDate date);

private slots:
    void on_btn_search_clicked();

    void on_btn_rewrite_clicked();

    void on_btn_return_clicked();

    void on_tb_result_doubleClicked(const QModelIndex &index);

    void on_serach_type_currentIndexChanged(int index);

signals:
    void updateFocusList();

private:
    Ui::SearchFrame *ui;
    list<Question> search_result;
    MainWindow *mainWindow;
    QStandardItemModel *model = nullptr;

    void showResult();
    void initViews();
    QString transDate(QDate date);
};

#endif // SEARCHFRAME_H
