#-------------------------------------------------
#
# Project created by QtCreator 2017-09-12T21:09:16
#
#-------------------------------------------------
QT += sql
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FindYourAnswer
TEMPLATE = app

QMAKE_MAC_SDK = macosx10.12

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    baseinfo.cpp \
    question.cpp \
    comment.cpp \
    user.cpp \
    logindialog.cpp \
    global.cpp \
    questionframe.cpp \
    questiondetailframe.cpp \
    commentdialog.cpp \
    focusdialog.cpp \
    questiondialog.cpp \
    signupdialog.cpp \
    accountframe.cpp \
    searchframe.cpp \
    userquestionframe.cpp \
    cancelfocusdialog.cpp \
    log.cpp \
    fileexception.cpp

HEADERS += \
        mainwindow.h \
    baseinfo.h \
    question.h \
    comment.h \
    user.h \
    logindialog.h \
    global.h \
    questionframe.h \
    questiondetailframe.h \
    commentdialog.h \
    focusdialog.h \
    questiondialog.h \
    signupdialog.h \
    accountframe.h \
    searchframe.h \
    userquestionframe.h \
    cancelfocusdialog.h \
    log.h \
    fileexception.h

FORMS += \
        mainwindow.ui \
    logindialog.ui \
    questionframe.ui \
    questiondetailframe.ui \
    commentdialog.ui \
    focusdialog.ui \
    questiondialog.ui \
    signupdialog.ui \
    accountframe.ui \
    searchframe.ui \
    userquestionframe.ui \
    cancelfocusdialog.ui
