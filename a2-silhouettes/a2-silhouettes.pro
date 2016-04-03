QT += core
QT += gui

CONFIG += c++11

TARGET = a2-silhouettes
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    silhouettes.cpp

HEADERS += \
    silhouettes.h \
    myvector.h \
    myqueue.h \
    mylist.h
