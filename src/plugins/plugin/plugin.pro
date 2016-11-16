QT += widgets

CONFIG += plugin

TEMPLATE = lib
TARGET = plugin

HEADERS += $$PWD/PluginInterface.h \
    $$PWD/Plugin.h

SOURCES += $$PWD/Plugin.cpp
