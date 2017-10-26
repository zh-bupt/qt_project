/********************************************************************************
** Form generated from reading UI file 'messageboard.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEBOARD_H
#define UI_MESSAGEBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_MessageBoard
{
public:
    QTableView *borrow_table;
    QTableView *order_table;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QFrame *MessageBoard)
    {
        if (MessageBoard->objectName().isEmpty())
            MessageBoard->setObjectName(QStringLiteral("MessageBoard"));
        MessageBoard->resize(500, 450);
        MessageBoard->setFrameShape(QFrame::StyledPanel);
        MessageBoard->setFrameShadow(QFrame::Raised);
        borrow_table = new QTableView(MessageBoard);
        borrow_table->setObjectName(QStringLiteral("borrow_table"));
        borrow_table->setGeometry(QRect(10, 30, 480, 180));
        order_table = new QTableView(MessageBoard);
        order_table->setObjectName(QStringLiteral("order_table"));
        order_table->setGeometry(QRect(10, 240, 480, 180));
        label = new QLabel(MessageBoard);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 10, 60, 16));
        label_2 = new QLabel(MessageBoard);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 220, 60, 16));

        retranslateUi(MessageBoard);

        QMetaObject::connectSlotsByName(MessageBoard);
    } // setupUi

    void retranslateUi(QFrame *MessageBoard)
    {
        MessageBoard->setWindowTitle(QApplication::translate("MessageBoard", "Frame", Q_NULLPTR));
        label->setText(QApplication::translate("MessageBoard", "\345\202\254\350\277\230\351\200\232\347\237\245", Q_NULLPTR));
        label_2->setText(QApplication::translate("MessageBoard", "\351\242\204\345\200\237\351\200\232\347\237\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MessageBoard: public Ui_MessageBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEBOARD_H
