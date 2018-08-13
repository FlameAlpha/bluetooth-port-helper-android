#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06 13:11:05
#
#-------------------------------------------------

QT       += core gui
QT      += bluetooth
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PortHelper
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    speeddispaly.cpp

HEADERS  += widget.h \
    speeddispaly.h \
    main.h

FORMS    += widget.ui \
    speeddispaly.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    AndroidManifest.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/
