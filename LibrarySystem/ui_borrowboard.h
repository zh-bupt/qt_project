/********************************************************************************
** Form generated from reading UI file 'borrowboard.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BORROWBOARD_H
#define UI_BORROWBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_BorrowBoard
{
public:
    QLineEdit *t_isbn;
    QPushButton *btn_borrow;
    QPushButton *btn_clear;

    void setupUi(QFrame *BorrowBoard)
    {
        if (BorrowBoard->objectName().isEmpty())
            BorrowBoard->setObjectName(QStringLiteral("BorrowBoard"));
        BorrowBoard->resize(400, 300);
        BorrowBoard->setFrameShape(QFrame::StyledPanel);
        BorrowBoard->setFrameShadow(QFrame::Raised);
        t_isbn = new QLineEdit(BorrowBoard);
        t_isbn->setObjectName(QStringLiteral("t_isbn"));
        t_isbn->setGeometry(QRect(130, 70, 113, 21));
        btn_borrow = new QPushButton(BorrowBoard);
        btn_borrow->setObjectName(QStringLiteral("btn_borrow"));
        btn_borrow->setGeometry(QRect(130, 100, 51, 32));
        btn_clear = new QPushButton(BorrowBoard);
        btn_clear->setObjectName(QStringLiteral("btn_clear"));
        btn_clear->setGeometry(QRect(190, 100, 51, 32));

        retranslateUi(BorrowBoard);

        QMetaObject::connectSlotsByName(BorrowBoard);
    } // setupUi

    void retranslateUi(QFrame *BorrowBoard)
    {
        BorrowBoard->setWindowTitle(QApplication::translate("BorrowBoard", "Frame", Q_NULLPTR));
        t_isbn->setPlaceholderText(QApplication::translate("BorrowBoard", "ISBN", Q_NULLPTR));
        btn_borrow->setText(QApplication::translate("BorrowBoard", "\345\200\237\351\230\205", Q_NULLPTR));
        btn_clear->setText(QApplication::translate("BorrowBoard", "\346\270\205\347\251\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BorrowBoard: public Ui_BorrowBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BORROWBOARD_H
