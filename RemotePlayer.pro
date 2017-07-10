#-------------------------------------------------
#
# Project created by QtCreator 2017-05-27T02:44:13
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemotePlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    socketserver.cpp \
    display.cpp

HEADERS  += mainwindow.h \
    socketserver.h \
    display.h

FORMS    +=
CONFIG += C++11
LIBS += -lwiringPi
