QT += core \
    gui \
    network

TARGET = orPlugin
TEMPLATE = lib
CONFIG += plugin

DEFINES += ORPLUGIN_LIBRARY

SOURCES += orplugin.cpp \
    orpluginwidget.cpp

HEADERS += orplugin.h \
    orPlugin_global.h \
    orpluginwidget.h \
    orplugininterface.h

FORMS += orpluginwidget.ui
