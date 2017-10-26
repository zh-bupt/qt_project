/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QListWidget *side_bar;
    QStackedWidget *container;
    QPushButton *logout;
    QLabel *time;
    QLineEdit *e_date;
    QPushButton *skip;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(719, 488);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        side_bar = new QListWidget(centralWidget);
        side_bar->setObjectName(QStringLiteral("side_bar"));
        side_bar->setGeometry(QRect(0, 0, 200, 291));
        container = new QStackedWidget(centralWidget);
        container->setObjectName(QStringLiteral("container"));
        container->setGeometry(QRect(220, 0, 500, 480));
        container->setAutoFillBackground(true);
        logout = new QPushButton(centralWidget);
        logout->setObjectName(QStringLiteral("logout"));
        logout->setGeometry(QRect(35, 400, 121, 23));
        time = new QLabel(centralWidget);
        time->setObjectName(QStringLiteral("time"));
        time->setGeometry(QRect(80, 330, 111, 16));
        e_date = new QLineEdit(centralWidget);
        e_date->setObjectName(QStringLiteral("e_date"));
        e_date->setGeometry(QRect(10, 365, 111, 21));
        skip = new QPushButton(centralWidget);
        skip->setObjectName(QStringLiteral("skip"));
        skip->setGeometry(QRect(130, 360, 61, 32));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 330, 60, 16));
        MainWindow->setCentralWidget(centralWidget);
        container->raise();
        side_bar->raise();
        logout->raise();
        time->raise();
        e_date->raise();
        skip->raise();
        label->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 719, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(side_bar, SIGNAL(currentRowChanged(int)), container, SLOT(setCurrentIndex(int)));

        container->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        logout->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", Q_NULLPTR));
        time->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        skip->setText(QApplication::translate("MainWindow", "\350\267\263\350\275\254", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\346\227\245\346\234\237:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
