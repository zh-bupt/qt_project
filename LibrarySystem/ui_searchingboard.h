/********************************************************************************
** Form generated from reading UI file 'searchingboard.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHINGBOARD_H
#define UI_SEARCHINGBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_SearchingBoard
{
public:
    QTableView *tableView;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *tv_search;
    QComboBox *comboBox;
    QPushButton *btn_search;
    QPushButton *btn_rewrite;
    QPushButton *btn_borrow;
    QPushButton *btn_subscribe;
    QComboBox *category_box;

    void setupUi(QFrame *SearchingBoard)
    {
        if (SearchingBoard->objectName().isEmpty())
            SearchingBoard->setObjectName(QStringLiteral("SearchingBoard"));
        SearchingBoard->resize(500, 480);
        SearchingBoard->setFrameShape(QFrame::StyledPanel);
        SearchingBoard->setFrameShadow(QFrame::Raised);
        tableView = new QTableView(SearchingBoard);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 120, 480, 281));
        tableView->setAutoFillBackground(true);
        label = new QLabel(SearchingBoard);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 30, 71, 16));
        label_2 = new QLabel(SearchingBoard);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 60, 71, 16));
        tv_search = new QLineEdit(SearchingBoard);
        tv_search->setObjectName(QStringLiteral("tv_search"));
        tv_search->setGeometry(QRect(200, 60, 113, 21));
        comboBox = new QComboBox(SearchingBoard);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(200, 30, 113, 26));
        btn_search = new QPushButton(SearchingBoard);
        btn_search->setObjectName(QStringLiteral("btn_search"));
        btn_search->setGeometry(QRect(130, 90, 81, 32));
        btn_rewrite = new QPushButton(SearchingBoard);
        btn_rewrite->setObjectName(QStringLiteral("btn_rewrite"));
        btn_rewrite->setGeometry(QRect(240, 90, 81, 32));
        btn_borrow = new QPushButton(SearchingBoard);
        btn_borrow->setObjectName(QStringLiteral("btn_borrow"));
        btn_borrow->setGeometry(QRect(130, 410, 100, 32));
        btn_subscribe = new QPushButton(SearchingBoard);
        btn_subscribe->setObjectName(QStringLiteral("btn_subscribe"));
        btn_subscribe->setGeometry(QRect(270, 410, 100, 32));
        category_box = new QComboBox(SearchingBoard);
        category_box->setObjectName(QStringLiteral("category_box"));
        category_box->setGeometry(QRect(200, 59, 114, 26));

        retranslateUi(SearchingBoard);

        QMetaObject::connectSlotsByName(SearchingBoard);
    } // setupUi

    void retranslateUi(QFrame *SearchingBoard)
    {
        SearchingBoard->setWindowTitle(QApplication::translate("SearchingBoard", "Frame", Q_NULLPTR));
        label->setText(QApplication::translate("SearchingBoard", "\346\243\200\347\264\242\350\257\215\347\261\273\345\236\213", Q_NULLPTR));
        label_2->setText(QApplication::translate("SearchingBoard", "\346\243\200   \347\264\242   \350\257\215", Q_NULLPTR));
        btn_search->setText(QApplication::translate("SearchingBoard", "\346\220\234\347\264\242", Q_NULLPTR));
        btn_rewrite->setText(QApplication::translate("SearchingBoard", "\351\207\215\345\206\231", Q_NULLPTR));
        btn_borrow->setText(QApplication::translate("SearchingBoard", "\345\200\237\351\230\205", Q_NULLPTR));
        btn_subscribe->setText(QApplication::translate("SearchingBoard", "\351\242\204\347\272\246", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SearchingBoard: public Ui_SearchingBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHINGBOARD_H
