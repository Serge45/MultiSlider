#-------------------------------------------------
#
# Project created by QtCreator 2014-11-11T15:20:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultiSlider
TEMPLATE = app


SOURCES += main.cpp\
        multislider.cpp \
    overlay.cpp \
    colorslider.cpp

HEADERS  += multislider.h \
    overlay.h \
    colorslider.h

FORMS    += multislider.ui
