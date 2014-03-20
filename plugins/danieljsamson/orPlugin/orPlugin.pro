#-------------------------------------------------
#
# Project created by QtCreator 2011-03-11T23:42:05
#
#-------------------------------------------------

QT       += network script scripttools

TARGET = orPlugin
TEMPLATE = lib

DEFINES += ORPLUGIN_LIBRARY

SOURCES += orplugin.cpp \
    orpluginwidget.cpp

HEADERS += orplugin.h\
        orPlugin_global.h \
    orpluginwidget.h \
    orplugininterface.h

FORMS += \
    orpluginwidget.ui
