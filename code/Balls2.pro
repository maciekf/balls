#-------------------------------------------------
#
# Project created by QtCreator 2012-05-30T20:34:53
#
#-------------------------------------------------

QT       += core gui

TARGET = Balls2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ball.cpp \
    controller.cpp \
    factory.cpp \
    cameleonball.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    ball.h \
    controller.h \
    factory.h \
    cameleonball.h \
    settings.h

FORMS    += mainwindow.ui \
    settings.ui

RESOURCES += \
    Pics.qrc
