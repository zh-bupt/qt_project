/********************************************************************************
** Form generated from reading UI file 'returndialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RETURNDIALOG_H
#define UI_RETURNDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_ReturnDialog
{
public:
    QTableView *book_info;
    QPushButton *btn_return;
    QPushButton *btn_renew;

    void setupUi(QDialog *ReturnDialog)
    {
        if (ReturnDialog->objectName().isEmpty())
            ReturnDialog->setObjectName(QStringLiteral("ReturnDialog"));
        ReturnDialog->resize(400, 300);
        book_info = new QTableView(ReturnDialog);
        book_info->setObjectName(QStringLiteral("book_info"));
        book_info->setGeometry(QRect(10, 10, 380, 250));
        btn_return = new QPushButton(ReturnDialog);
        btn_return->setObjectName(QStringLiteral("btn_return"));
        btn_return->setGeometry(QRect(60, 260, 113, 32));
        btn_renew = new QPushButton(ReturnDialog);
        btn_renew->setObjectName(QStringLiteral("btn_renew"));
        btn_renew->setGeometry(QRect(210, 260, 113, 32));

        retranslateUi(ReturnDialog);

        QMetaObject::connectSlotsByName(ReturnDialog);
    } // setupUi

    void retranslateUi(QDialog *ReturnDialog)
    {
        ReturnDialog->setWindowTitle(QApplication::translate("ReturnDialog", "Dialog", Q_NULLPTR));
        btn_return->setText(QApplication::translate("ReturnDialog", " \345\275\222\350\277\230", Q_NULLPTR));
        btn_renew->setText(QApplication::translate("ReturnDialog", "\347\273\255\345\200\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReturnDialog: public Ui_ReturnDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RETURNDIALOG_H
