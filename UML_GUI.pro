#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T10:36:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UML_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    diagramscene.cpp \
    arrow.cpp \
    diagramitem.cpp \
    diagramtextitem.cpp \
    atrybutdialog.cpp \
    operacjadialog.cpp \
    propertiesdialog.cpp

HEADERS  += mainwindow.h \
    diagramscene.h \
    arrow.h \
    diagramitem.h \
    diagramtextitem.h \
    atrybutdialog.h \
    operacjadialog.h \
    propertiesdialog.h

FORMS    += mainwindow.ui \
    atrybutdialog.ui

RESOURCES += \
    mojeres.qrc
