QT += core \
    gui \
    network

TARGET = ExamplePlugin
TEMPLATE = lib

DEFINES += EXAMPLEPLUGIN_LIBRARY

HEADERS += ExamplePlugin.h \
    ExamplePlugin_global.h \
    ExamplePluginWidget.h \
    ExamplePluginInterface.h

SOURCES += ExamplePlugin.cpp \
    ExamplePluginWidget.cpp

FORMS += ExamplePluginWidget.ui
