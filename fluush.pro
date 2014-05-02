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
    screenshotrestriction.cpp \
    fluushnetwork.cpp

HEADERS  += fluushoption.h \
    screenshotrestriction.h \
    fluushnetwork.h

FORMS    += fluushoption.ui

TRANSLATIONS = fluush_fr.ts

RESOURCES += \
    ressources.qrc
