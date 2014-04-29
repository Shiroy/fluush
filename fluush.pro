#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T11:07:30
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fluush
TEMPLATE = app


SOURCES += main.cpp\
        fluushoption.cpp \
    screenshotrestriction.cpp

HEADERS  += fluushoption.h \
    screenshotrestriction.h

FORMS    += fluushoption.ui

RESOURCES += \
    ressources.qrc
