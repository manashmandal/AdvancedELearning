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
    qbase.cpp \
    qbaseoperations.cpp \
    qboolalgebra.cpp \
    aboutme.cpp

HEADERS  += mainwindow.h \
    numberbaseconverter.h \
    numberbasechart.h \
    qbase.h \
    qbaseoperations.h \
    qboolalgebra.h \
    aboutme.h

FORMS    += mainwindow.ui \
    numberbaseconverter.ui \
    numberbasechart.ui \
    qbaseoperations.ui \
    aboutme.ui

RESOURCES += \
    appresource.qrc
