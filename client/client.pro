QT += core \     
    network \
    gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = openrcon
TEMPLATE = app

HEADERS += OpenRcon.h \
    Constants.h \
    GameEntry.h \
    GameManager.h \
    ServerEntry.h \
    ServerManager.h \
    LanguageEntry.h \
    LanguageManager.h \
    ServerListDialog.h \
    ServerEditDialog.h \
    OptionsDialog.h \
    AboutDialog.h \
    GameType.h \
    SessionManager.h

SOURCES += Main.cpp \
    OpenRcon.cpp \
    GameManager.cpp \
    ServerManager.cpp \
    LanguageManager.cpp \
    ServerListDialog.cpp \
    ServerEditDialog.cpp \
    OptionsDialog.cpp \
    AboutDialog.cpp \
    SessionManager.cpp

FORMS += OpenRcon.ui \
    ServerListDialog.ui \
    ServerEditDialog.ui \
    OptionsDialog.ui \
    AboutDialog.ui

RESOURCES += OpenRcon.qrc

win32:RC_FILE = openrcon.rc

macx {
    TARGET = OpenRcon
    ICON = openrcon.icns
    QMAKE_INFO_PLIST = Info.plist
}

include(locale/locale.pri)
include(game/game.pri)

include(frostbite/frostbite.pri)
include(bfbc2/bfbc2.pri)
include(frostbite2/frostbite2.pri)
include(bf3/bf3.pri)
include(bf4/bf4.pri)
include(minecraft/minecraft.pri)