#-------------------------------------------------
#
# Project created by QtCreator 2016-08-22T15:28:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Biblioteka
TEMPLATE = app
RC_ICONS = notebook.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    pozycja.cpp \
    plytacd.cpp \
    kasetawideo.cpp \
    kasetadvhs.cpp \
    kasetaaudio.cpp

HEADERS  += mainwindow.h \
    pozycja.h \
    plytacd.h \
    kasetawideo.h \
    kasetadvhs.h \
    kasetaaudio.h

FORMS    += mainwindow.ui
