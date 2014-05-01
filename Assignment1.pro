#-------------------------------------------------
#
# Project created by QtCreator 2014-03-23T23:22:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assignment1
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp\
        config.cpp \
    ball.cpp \
    itemfactory.cpp \
    brick.cpp \
    brickdecorator.cpp \
    invinciblebrick.cpp \
    slidingbrick.cpp \
    teleportingbrick.cpp

HEADERS  += dialog.h\
            config.h \
    ball.h \
    itemfactory.h \
    brick.h \
    brickdecorator.h \
    invinciblebrick.h \
    slidingbrick.h \
    teleportingbrick.h

FORMS    += dialog.ui

OTHER_FILES += config.config
