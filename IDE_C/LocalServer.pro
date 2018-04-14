#-------------------------------------------------
#
# Project created by QtCreator 2018-04-11T18:53:57
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LocalServer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    localserver.cpp

HEADERS  += widget.h \
    localserver.h

FORMS    += widget.ui
