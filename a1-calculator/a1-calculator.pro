QT += core
QT -= gui

CONFIG += c++11

TARGET = a1-calculator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    calculator.cpp \
    validation.cpp

HEADERS += \
    calculator.h \
    validation.h \
    mystack.h \
    myunordered_map.h
