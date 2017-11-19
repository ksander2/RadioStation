#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T09:44:25
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RadioStation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    domain/device.cpp \
    domain/operationmode.cpp \
    domain/statedevice.cpp \
    domain/subscriber.cpp \
    subscriberwidget.cpp \
    byteconverter.cpp \
    gbl.cpp \
    net/udplistener.cpp \
    presenters/mainpresenter.cpp \
    logger.cpp \
    logview.cpp

HEADERS  += mainwindow.h \
    domain/device.h \
    domain/operationmode.h \
    domain/statedevice.h \
    domain/subscriber.h \
    subscriberwidget.h \
    byteconverter.h \
    gbl.h \
    net/udplistener.h \
    presenters/mainpresenter.h \
    logger.h \
    logview.h

FORMS    += mainwindow.ui \
    logview.ui
