QT += core \
    gui \
    widgets

CONFIG += c++14

TARGET = openrcon
TEMPLATE = app

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += OpenRcon.h \
    Constants.h \
    ServerManager.h \
    LanguageEntry.h \
    LanguageManager.h \
    SessionManager.h

SOURCES += Main.cpp \
    OpenRcon.cpp \
    ServerManager.cpp \
    LanguageManager.cpp \
    SessionManager.cpp \
    LanguageEntry.cpp

RESOURCES += OpenRcon.qrc

RC_ICONS = images/icons/openrcon.ico

include(../common/common.pro)
include(translations/translations.pri)
include(gui/gui.pri)
include(game/game.pri)
include(plugins/plugins.pri)
