#-------------------------------------------------
#
# Project created by QtCreator 2015-07-03T12:27:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webview webkitwidgets testlib

TARGET = AdvancedELearning
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    numberbaseconverter.cpp \
    numberbasechart.cpp \
    basegenerator.cpp \
    qbase.cpp

HEADERS  += mainwindow.h \
    numberbaseconverter.h \
    numberbasechart.h \
    basegenerator.h \
    qbase.h

FORMS    += mainwindow.ui \
    numberbaseconverter.ui \
    numberbasechart.ui

RESOURCES += \
    appresource.qrc
