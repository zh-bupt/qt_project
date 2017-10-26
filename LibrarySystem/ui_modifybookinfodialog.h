/********************************************************************************
** Form generated from reading UI file 'modifybookinfodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYBOOKINFODIALOG_H
#define UI_MODIFYBOOKINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ModifyBookInfoDialog
{
public:
    QLineEdit *title;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *ISBN;
    QLabel *label_12;
    QLabel *label_13;
    QPlainTextEdit *introduction;
    QLabel *label_14;
    QLineEdit *publishing_company;
    QSpinBox *number;
    QComboBox *category_box;
    QPushButton *btn_confirm;
    QLabel *label_15;
    QPushButton *btn_cancel;
    QLineEdit *author;
    QLabel *label_16;

    void setupUi(QDialog *ModifyBookInfoDialog)
    {
        if (ModifyBookInfoDialog->objectName().isEmpty())
            ModifyBookInfoDialog->setObjectName(QStringLiteral("ModifyBookInfoDialog"));
        ModifyBookInfoDialog->resize(362, 310);
        title = new QLineEdit(ModifyBookInfoDialog);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(85, 30, 241, 21));
        label_10 = new QLabel(ModifyBookInfoDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(30, 125, 60, 16));
        label_11 = new QLabel(ModifyBookInfoDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(30, 200, 60, 16));
        ISBN = new QLineEdit(ModifyBookInfoDialog);
        ISBN->setObjectName(QStringLiteral("ISBN"));
        ISBN->setGeometry(QRect(85, 90, 241, 21));
        ISBN->setMaxLength(12);
        label_12 = new QLabel(ModifyBookInfoDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(160, 125, 60, 16));
        label_13 = new QLabel(ModifyBookInfoDialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(30, 30, 60, 16));
        introduction = new QPlainTextEdit(ModifyBookInfoDialog);
        introduction->setObjectName(QStringLiteral("introduction"));
        introduction->setGeometry(QRect(85, 200, 241, 61));
        label_14 = new QLabel(ModifyBookInfoDialog);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(30, 60, 60, 16));
        publishing_company = new QLineEdit(ModifyBookInfoDialog);
        publishing_company->setObjectName(QStringLiteral("publishing_company"));
        publishing_company->setGeometry(QRect(85, 160, 241, 21));
        number = new QSpinBox(ModifyBookInfoDialog);
        number->setObjectName(QStringLiteral("number"));
        number->setGeometry(QRect(85, 120, 71, 24));
        category_box = new QComboBox(ModifyBookInfoDialog);
        category_box->setObjectName(QStringLiteral("category_box"));
        category_box->setGeometry(QRect(210, 120, 111, 26));
        btn_confirm = new QPushButton(ModifyBookInfoDialog);
        btn_confirm->setObjectName(QStringLiteral("btn_confirm"));
        btn_confirm->setGeometry(QRect(90, 270, 81, 32));
        label_15 = new QLabel(ModifyBookInfoDialog);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(30, 160, 60, 16));
        btn_cancel = new QPushButton(ModifyBookInfoDialog);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));
        btn_cancel->setGeometry(QRect(220, 270, 81, 32));
        author = new QLineEdit(ModifyBookInfoDialog);
        author->setObjectName(QStringLiteral("author"));
        author->setGeometry(QRect(85, 60, 241, 21));
        label_16 = new QLabel(ModifyBookInfoDialog);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(30, 90, 51, 16));

        retranslateUi(ModifyBookInfoDialog);

        QMetaObject::connectSlotsByName(ModifyBookInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *ModifyBookInfoDialog)
    {
        ModifyBookInfoDialog->setWindowTitle(QApplication::translate("ModifyBookInfoDialog", "Dialog", Q_NULLPTR));
        label_10->setText(QApplication::translate("ModifyBookInfoDialog", "\346\225\260    \351\207\217", Q_NULLPTR));
        label_11->setText(QApplication::translate("ModifyBookInfoDialog", "\347\256\200    \344\273\213", Q_NULLPTR));
        label_12->setText(QApplication::translate("ModifyBookInfoDialog", "\347\247\215    \347\261\273", Q_NULLPTR));
        label_13->setText(QApplication::translate("ModifyBookInfoDialog", "\344\271\246    \345\220\215", Q_NULLPTR));
        label_14->setText(QApplication::translate("ModifyBookInfoDialog", "\344\275\234    \350\200\205", Q_NULLPTR));
        btn_confirm->setText(QApplication::translate("ModifyBookInfoDialog", "\347\241\256\350\256\244", Q_NULLPTR));
        label_15->setText(QApplication::translate("ModifyBookInfoDialog", "\345\207\272\347\211\210\347\244\276", Q_NULLPTR));
        btn_cancel->setText(QApplication::translate("ModifyBookInfoDialog", "\346\270\205\347\251\272", Q_NULLPTR));
        label_16->setText(QApplication::translate("ModifyBookInfoDialog", "I S B N", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ModifyBookInfoDialog: public Ui_ModifyBookInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYBOOKINFODIALOG_H
