/********************************************************************************
** Form generated from reading UI file 'usercenterboard.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERCENTERBOARD_H
#define UI_USERCENTERBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_UserCenterBoard
{
public:
    QTableView *user_info;
    QLabel *label;
    QLabel *label_2;
    QTableView *book_list;
    QPushButton *btn_edit_info;

    void setupUi(QFrame *UserCenterBoard)
    {
        if (UserCenterBoard->objectName().isEmpty())
            UserCenterBoard->setObjectName(QStringLiteral("UserCenterBoard"));
        UserCenterBoard->resize(500, 450);
        UserCenterBoard->setFrameShape(QFrame::StyledPanel);
        UserCenterBoard->setFrameShadow(QFrame::Raised);
        user_info = new QTableView(UserCenterBoard);
        user_info->setObjectName(QStringLiteral("user_info"));
        user_info->setGeometry(QRect(10, 30, 480, 171));
        label = new QLabel(UserCenterBoard);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(223, 10, 54, 12));
        label_2 = new QLabel(UserCenterBoard);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(223, 230, 54, 12));
        book_list = new QTableView(UserCenterBoard);
        book_list->setObjectName(QStringLiteral("book_list"));
        book_list->setGeometry(QRect(10, 249, 480, 171));
        btn_edit_info = new QPushButton(UserCenterBoard);
        btn_edit_info->setObjectName(QStringLiteral("btn_edit_info"));
        btn_edit_info->setGeometry(QRect(370, 200, 113, 32));

        retranslateUi(UserCenterBoard);

        QMetaObject::connectSlotsByName(UserCenterBoard);
    } // setupUi

    void retranslateUi(QFrame *UserCenterBoard)
    {
        UserCenterBoard->setWindowTitle(QApplication::translate("UserCenterBoard", "Frame", Q_NULLPTR));
        label->setText(QApplication::translate("UserCenterBoard", "\344\270\252\344\272\272\344\277\241\346\201\257", Q_NULLPTR));
        label_2->setText(QApplication::translate("UserCenterBoard", "\346\211\200\345\200\237\344\271\246\347\261\215", Q_NULLPTR));
        btn_edit_info->setText(QApplication::translate("UserCenterBoard", "\344\277\256\346\224\271\344\270\252\344\272\272\344\277\241\346\201\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UserCenterBoard: public Ui_UserCenterBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERCENTERBOARD_H
