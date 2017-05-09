#-------------------------------------------------
#
# Project created by QtCreator 2013-10-03T22:30:49
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = video_converter
TEMPLATE = app


SOURCES += main.cpp\
    droppanel.cpp \
    mainwindow.cpp \
    settings.cpp

HEADERS  += \
    droppanel.h \
    mainwindow.h \
    settings.h

FORMS    += \
    mainwindow.ui \
    settings.ui

RESOURCES += \
    resources.qrc

DISTFILES +=

DESTDIR = $$PWD

