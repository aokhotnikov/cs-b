QT += core
QT -= gui

CONFIG += c++11

TARGET = a5-collections
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    mystack.h \
    myvector.h \
    mylist.h \
    myqueue.h \
    myqueue2.h \
    myunordered_map.h
