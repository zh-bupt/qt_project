/********************************************************************************
** Form generated from reading UI file 'borrowdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BORROWDIALOG_H
#define UI_BORROWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_BorrowDialog
{
public:
    QDialogButtonBox *button;
    QTableView *table_info;

    void setupUi(QDialog *BorrowDialog)
    {
        if (BorrowDialog->objectName().isEmpty())
            BorrowDialog->setObjectName(QStringLiteral("BorrowDialog"));
        BorrowDialog->resize(400, 300);
        button = new QDialogButtonBox(BorrowDialog);
        button->setObjectName(QStringLiteral("button"));
        button->setGeometry(QRect(30, 240, 341, 32));
        button->setOrientation(Qt::Horizontal);
        button->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        table_info = new QTableView(BorrowDialog);
        table_info->setObjectName(QStringLiteral("table_info"));
        table_info->setGeometry(QRect(10, 10, 371, 221));

        retranslateUi(BorrowDialog);
        QObject::connect(button, SIGNAL(accepted()), BorrowDialog, SLOT(accept()));
        QObject::connect(button, SIGNAL(rejected()), BorrowDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BorrowDialog);
    } // setupUi

    void retranslateUi(QDialog *BorrowDialog)
    {
        BorrowDialog->setWindowTitle(QApplication::translate("BorrowDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BorrowDialog: public Ui_BorrowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BORROWDIALOG_H
