/********************************************************************************
** Form generated from reading UI file 'modifyuserinfodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYUSERINFODIALOG_H
#define UI_MODIFYUSERINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ModifyUserInfoDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *name;
    QLineEdit *id;
    QLineEdit *password;
    QComboBox *academy;
    QComboBox *type;
    QPushButton *btn_comfirm;
    QPushButton *btn_cancel;
    QSpinBox *fine;
    QPushButton *show_password;

    void setupUi(QDialog *ModifyUserInfoDialog)
    {
        if (ModifyUserInfoDialog->objectName().isEmpty())
            ModifyUserInfoDialog->setObjectName(QStringLiteral("ModifyUserInfoDialog"));
        ModifyUserInfoDialog->resize(391, 255);
        label = new QLabel(ModifyUserInfoDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 35, 60, 16));
        label_2 = new QLabel(ModifyUserInfoDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 65, 60, 16));
        label_3 = new QLabel(ModifyUserInfoDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 95, 60, 16));
        label_4 = new QLabel(ModifyUserInfoDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(215, 95, 60, 16));
        label_5 = new QLabel(ModifyUserInfoDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 125, 60, 16));
        label_6 = new QLabel(ModifyUserInfoDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(50, 155, 60, 16));
        name = new QLineEdit(ModifyUserInfoDialog);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(90, 30, 241, 21));
        id = new QLineEdit(ModifyUserInfoDialog);
        id->setObjectName(QStringLiteral("id"));
        id->setGeometry(QRect(90, 60, 241, 21));
        id->setAutoFillBackground(false);
        id->setInputMethodHints(Qt::ImhDigitsOnly);
        password = new QLineEdit(ModifyUserInfoDialog);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(90, 120, 151, 21));
        password->setEchoMode(QLineEdit::Password);
        academy = new QComboBox(ModifyUserInfoDialog);
        academy->setObjectName(QStringLiteral("academy"));
        academy->setGeometry(QRect(90, 90, 111, 26));
        type = new QComboBox(ModifyUserInfoDialog);
        type->setObjectName(QStringLiteral("type"));
        type->setGeometry(QRect(250, 90, 81, 26));
        btn_comfirm = new QPushButton(ModifyUserInfoDialog);
        btn_comfirm->setObjectName(QStringLiteral("btn_comfirm"));
        btn_comfirm->setGeometry(QRect(70, 190, 113, 32));
        btn_cancel = new QPushButton(ModifyUserInfoDialog);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));
        btn_cancel->setGeometry(QRect(210, 190, 113, 32));
        fine = new QSpinBox(ModifyUserInfoDialog);
        fine->setObjectName(QStringLiteral("fine"));
        fine->setGeometry(QRect(90, 150, 241, 24));
        fine->setMaximum(1000);
        show_password = new QPushButton(ModifyUserInfoDialog);
        show_password->setObjectName(QStringLiteral("show_password"));
        show_password->setGeometry(QRect(250, 115, 81, 32));

        retranslateUi(ModifyUserInfoDialog);

        QMetaObject::connectSlotsByName(ModifyUserInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *ModifyUserInfoDialog)
    {
        ModifyUserInfoDialog->setWindowTitle(QApplication::translate("ModifyUserInfoDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("ModifyUserInfoDialog", "\345\247\223  \345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("ModifyUserInfoDialog", "\345\255\246  \345\217\267", Q_NULLPTR));
        label_3->setText(QApplication::translate("ModifyUserInfoDialog", "\345\255\246  \351\231\242", Q_NULLPTR));
        label_4->setText(QApplication::translate("ModifyUserInfoDialog", "\347\261\273  \345\236\213", Q_NULLPTR));
        label_5->setText(QApplication::translate("ModifyUserInfoDialog", "\345\257\206  \347\240\201", Q_NULLPTR));
        label_6->setText(QApplication::translate("ModifyUserInfoDialog", "\346\254\240  \346\254\276", Q_NULLPTR));
        btn_comfirm->setText(QApplication::translate("ModifyUserInfoDialog", "\344\277\235\345\255\230", Q_NULLPTR));
        btn_cancel->setText(QApplication::translate("ModifyUserInfoDialog", "\345\217\226\346\266\210", Q_NULLPTR));
        show_password->setText(QApplication::translate("ModifyUserInfoDialog", "\346\230\276\347\244\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ModifyUserInfoDialog: public Ui_ModifyUserInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYUSERINFODIALOG_H
