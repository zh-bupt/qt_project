/********************************************************************************
** Form generated from reading UI file 'listdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTDIALOG_H
#define UI_LISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_ListDialog
{
public:
    QTableView *list;
    QPushButton *btn_confirm;

    void setupUi(QDialog *ListDialog)
    {
        if (ListDialog->objectName().isEmpty())
            ListDialog->setObjectName(QStringLiteral("ListDialog"));
        ListDialog->resize(400, 300);
        list = new QTableView(ListDialog);
        list->setObjectName(QStringLiteral("list"));
        list->setGeometry(QRect(10, 20, 380, 240));
        btn_confirm = new QPushButton(ListDialog);
        btn_confirm->setObjectName(QStringLiteral("btn_confirm"));
        btn_confirm->setGeometry(QRect(140, 260, 113, 32));

        retranslateUi(ListDialog);

        QMetaObject::connectSlotsByName(ListDialog);
    } // setupUi

    void retranslateUi(QDialog *ListDialog)
    {
        ListDialog->setWindowTitle(QApplication::translate("ListDialog", "Dialog", Q_NULLPTR));
        btn_confirm->setText(QApplication::translate("ListDialog", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ListDialog: public Ui_ListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTDIALOG_H
