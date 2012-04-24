#-------------------------------------------------
#
# Project created by QtCreator 2012-04-23T20:33:35
#
#-------------------------------------------------

QT       += core gui webkit network

TARGET = MobileOnDesktop
TEMPLATE = app

OBJECTS_DIR = objects
MOC_DIR = objects
UI_DIR = objects
RCC_DIR = objects

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/aboutdialog.cpp \
    src/webwidget.cpp \
    src/webpage.cpp \
    src/urlinputdialog.cpp \
    src/preferencesdialog.cpp

HEADERS  += src/mainwindow.h \
    src/aboutdialog.h \
    src/webwidget.h \
    src/webpage.h \
    src/urlinputdialog.h \
    src/preferencesdialog.h

FORMS    += ui/mainwindow.ui \
    ui/aboutdialog.ui \
    ui/preferencesdialog.ui

RESOURCES += \
    qrc/mobileondesktop.qrc

TRANSLATIONS = ts/mobileondesktop_fr.ts













