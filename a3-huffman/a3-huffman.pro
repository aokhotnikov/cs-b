QT += core
QT -= gui

CONFIG += c++11

TARGET = a3-huffman
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tree.cpp \
    zip.cpp \
    unzip.cpp

HEADERS += \
    tree.h \
    zip.h \
    unzip.h \
    myqueue.h \
    mylist.h \
    myunordered_map.h
