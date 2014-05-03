#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T11:07:30
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fluush
TEMPLATE = app

QMAKE_CXXFLAGS = -std=c++11

SOURCES += main.cpp\
        fluushoption.cpp \
    screenshotrestriction.cpp \
    fluushnetwork.cpp \
    fluushnetworkrequest.cpp \
    fluushrequestupload.cpp \
    thumbwidget.cpp \
    fluushrequesthistory.cpp \
    fluushrequestthumbnail.cpp

HEADERS  += fluushoption.h \
    screenshotrestriction.h \
    fluushnetwork.h \
    fluushnetworkrequest.h \
    fluushrequestupload.h \
    thumbwidget.h \
    fluushrequesthistory.h \
    fluushrequestthumbnail.h

FORMS    += fluushoption.ui \
    thumbwidget.ui

TRANSLATIONS = fluush_fr.ts

RESOURCES += \
    ressources.qrc
