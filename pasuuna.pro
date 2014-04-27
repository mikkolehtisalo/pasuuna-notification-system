#-------------------------------------------------
#
# Project created by QtCreator 2013-01-12T17:03:50
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += gui
QT       += widgets

TARGET = pasuuna
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    checker.cpp \
    message.cpp \
    settings.cpp

HEADERS += \
    checker.h \
    message.h \
    settings.h

FORMS += \
    message.ui

OTHER_FILES += \
    pasuuna.supp \
    pasuuna.ini

RESOURCES += \
    resources.qrc
