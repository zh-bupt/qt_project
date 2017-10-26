/********************************************************************************
** Form generated from reading UI file 'superuserboard.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUPERUSERBOARD_H
#define UI_SUPERUSERBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SuperUserBoard
{
public:
    QTabWidget *tab;
    QWidget *buy_book;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *t_title;
    QLineEdit *t_author;
    QLineEdit *t_publishing_company;
    QLabel *label_5;
    QPlainTextEdit *t_introduction;
    QPushButton *btn_confirm;
    QPushButton *btn_clear;
    QSpinBox *number;
    QLabel *label_6;
    QLineEdit *t_isbn;
    QComboBox *category_box;
    QLabel *label_9;
    QWidget *user;
    QLabel *label_7;
    QLineEdit *t_id;
    QPushButton *btn_search_user;
    QTableView *user_info;
    QPushButton *user_borrow_info;
    QPushButton *modify_user_info;
    QWidget *book;
    QLineEdit *t_isbn_2;
    QLabel *label_8;
    QTableView *book_info;
    QPushButton *btn_search_book;
    QPushButton *book_borrow_info;
    QPushButton *modify_book_info;

    void setupUi(QFrame *SuperUserBoard)
    {
        if (SuperUserBoard->objectName().isEmpty())
            SuperUserBoard->setObjectName(QStringLiteral("SuperUserBoard"));
        SuperUserBoard->resize(500, 480);
        SuperUserBoard->setFrameShape(QFrame::StyledPanel);
        SuperUserBoard->setFrameShadow(QFrame::Raised);
        tab = new QTabWidget(SuperUserBoard);
        tab->setObjectName(QStringLiteral("tab"));
        tab->setGeometry(QRect(0, 0, 500, 480));
        buy_book = new QWidget();
        buy_book->setObjectName(QStringLiteral("buy_book"));
        label = new QLabel(buy_book);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(25, 50, 60, 16));
        label_2 = new QLabel(buy_book);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(25, 80, 60, 16));
        label_3 = new QLabel(buy_book);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(25, 145, 60, 16));
        label_4 = new QLabel(buy_book);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(25, 180, 60, 16));
        t_title = new QLineEdit(buy_book);
        t_title->setObjectName(QStringLiteral("t_title"));
        t_title->setGeometry(QRect(80, 50, 350, 21));
        t_author = new QLineEdit(buy_book);
        t_author->setObjectName(QStringLiteral("t_author"));
        t_author->setGeometry(QRect(80, 80, 350, 21));
        t_publishing_company = new QLineEdit(buy_book);
        t_publishing_company->setObjectName(QStringLiteral("t_publishing_company"));
        t_publishing_company->setGeometry(QRect(80, 180, 350, 21));
        label_5 = new QLabel(buy_book);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(25, 220, 60, 16));
        t_introduction = new QPlainTextEdit(buy_book);
        t_introduction->setObjectName(QStringLiteral("t_introduction"));
        t_introduction->setGeometry(QRect(80, 220, 350, 79));
        btn_confirm = new QPushButton(buy_book);
        btn_confirm->setObjectName(QStringLiteral("btn_confirm"));
        btn_confirm->setGeometry(QRect(90, 320, 81, 32));
        btn_clear = new QPushButton(buy_book);
        btn_clear->setObjectName(QStringLiteral("btn_clear"));
        btn_clear->setGeometry(QRect(300, 320, 81, 32));
        number = new QSpinBox(buy_book);
        number->setObjectName(QStringLiteral("number"));
        number->setGeometry(QRect(80, 140, 131, 24));
        label_6 = new QLabel(buy_book);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(25, 110, 51, 16));
        t_isbn = new QLineEdit(buy_book);
        t_isbn->setObjectName(QStringLiteral("t_isbn"));
        t_isbn->setGeometry(QRect(80, 110, 350, 21));
        t_isbn->setMaxLength(15);
        category_box = new QComboBox(buy_book);
        category_box->setObjectName(QStringLiteral("category_box"));
        category_box->setGeometry(QRect(330, 140, 104, 26));
        label_9 = new QLabel(buy_book);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(280, 145, 60, 16));
        tab->addTab(buy_book, QString());
        user = new QWidget();
        user->setObjectName(QStringLiteral("user"));
        label_7 = new QLabel(user);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(80, 40, 60, 16));
        t_id = new QLineEdit(user);
        t_id->setObjectName(QStringLiteral("t_id"));
        t_id->setGeometry(QRect(130, 37, 181, 21));
        btn_search_user = new QPushButton(user);
        btn_search_user->setObjectName(QStringLiteral("btn_search_user"));
        btn_search_user->setGeometry(QRect(320, 33, 80, 31));
        user_info = new QTableView(user);
        user_info->setObjectName(QStringLiteral("user_info"));
        user_info->setGeometry(QRect(25, 90, 450, 280));
        user_borrow_info = new QPushButton(user);
        user_borrow_info->setObjectName(QStringLiteral("user_borrow_info"));
        user_borrow_info->setGeometry(QRect(90, 390, 113, 32));
        modify_user_info = new QPushButton(user);
        modify_user_info->setObjectName(QStringLiteral("modify_user_info"));
        modify_user_info->setGeometry(QRect(250, 390, 113, 32));
        tab->addTab(user, QString());
        book = new QWidget();
        book->setObjectName(QStringLiteral("book"));
        t_isbn_2 = new QLineEdit(book);
        t_isbn_2->setObjectName(QStringLiteral("t_isbn_2"));
        t_isbn_2->setGeometry(QRect(130, 37, 181, 21));
        label_8 = new QLabel(book);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(90, 40, 60, 16));
        book_info = new QTableView(book);
        book_info->setObjectName(QStringLiteral("book_info"));
        book_info->setGeometry(QRect(25, 90, 450, 280));
        btn_search_book = new QPushButton(book);
        btn_search_book->setObjectName(QStringLiteral("btn_search_book"));
        btn_search_book->setGeometry(QRect(310, 33, 80, 32));
        book_borrow_info = new QPushButton(book);
        book_borrow_info->setObjectName(QStringLiteral("book_borrow_info"));
        book_borrow_info->setGeometry(QRect(90, 390, 113, 32));
        modify_book_info = new QPushButton(book);
        modify_book_info->setObjectName(QStringLiteral("modify_book_info"));
        modify_book_info->setGeometry(QRect(250, 390, 113, 32));
        tab->addTab(book, QString());

        retranslateUi(SuperUserBoard);

        tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SuperUserBoard);
    } // setupUi

    void retranslateUi(QFrame *SuperUserBoard)
    {
        SuperUserBoard->setWindowTitle(QApplication::translate("SuperUserBoard", "Frame", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        tab->setToolTip(QApplication::translate("SuperUserBoard", "<html><head/><body><p>\347\224\250\346\210\267</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        tab->setWhatsThis(QApplication::translate("SuperUserBoard", "<html><head/><body><p>\347\224\250\346\210\267</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        label->setText(QApplication::translate("SuperUserBoard", "\344\271\246    \345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("SuperUserBoard", "\344\275\234    \350\200\205", Q_NULLPTR));
        label_3->setText(QApplication::translate("SuperUserBoard", "\346\225\260    \351\207\217", Q_NULLPTR));
        label_4->setText(QApplication::translate("SuperUserBoard", "\345\207\272\347\211\210\347\244\276", Q_NULLPTR));
        label_5->setText(QApplication::translate("SuperUserBoard", "\347\256\200    \344\273\213", Q_NULLPTR));
        btn_confirm->setText(QApplication::translate("SuperUserBoard", "\347\241\256\350\256\244", Q_NULLPTR));
        btn_clear->setText(QApplication::translate("SuperUserBoard", "\346\270\205\347\251\272", Q_NULLPTR));
        label_6->setText(QApplication::translate("SuperUserBoard", "I S B N", Q_NULLPTR));
        label_9->setText(QApplication::translate("SuperUserBoard", "\347\247\215    \347\261\273", Q_NULLPTR));
        tab->setTabText(tab->indexOf(buy_book), QApplication::translate("SuperUserBoard", "\350\264\255\344\271\246", Q_NULLPTR));
        label_7->setText(QApplication::translate("SuperUserBoard", "\347\224\250\346\210\267ID:", Q_NULLPTR));
        t_id->setPlaceholderText(QApplication::translate("SuperUserBoard", " \350\257\267\350\276\223\345\205\245\344\275\240\350\246\201\346\237\245\350\257\242\347\232\204\347\224\250\346\210\267ID", Q_NULLPTR));
        btn_search_user->setText(QApplication::translate("SuperUserBoard", "\346\237\245\350\257\242", Q_NULLPTR));
        user_borrow_info->setText(QApplication::translate("SuperUserBoard", "\346\237\245\347\234\213\345\200\237\351\230\205\344\277\241\346\201\257", Q_NULLPTR));
        modify_user_info->setText(QApplication::translate("SuperUserBoard", "\344\277\256\346\224\271\350\257\273\350\200\205\344\277\241\346\201\257", Q_NULLPTR));
        tab->setTabText(tab->indexOf(user), QApplication::translate("SuperUserBoard", "\347\224\250\346\210\267", Q_NULLPTR));
        t_isbn_2->setPlaceholderText(QApplication::translate("SuperUserBoard", "\345\233\276\344\271\246ISBN", Q_NULLPTR));
        label_8->setText(QApplication::translate("SuperUserBoard", "ISBN:", Q_NULLPTR));
        btn_search_book->setText(QApplication::translate("SuperUserBoard", "\346\237\245\350\257\242", Q_NULLPTR));
        book_borrow_info->setText(QApplication::translate("SuperUserBoard", "\346\237\245\347\234\213\345\200\237\351\230\205\344\277\241\346\201\257", Q_NULLPTR));
        modify_book_info->setText(QApplication::translate("SuperUserBoard", "\344\277\256\346\224\271\344\271\246\347\261\215\344\277\241\346\201\257", Q_NULLPTR));
        tab->setTabText(tab->indexOf(book), QApplication::translate("SuperUserBoard", "\345\233\276\344\271\246", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SuperUserBoard: public Ui_SuperUserBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPERUSERBOARD_H
