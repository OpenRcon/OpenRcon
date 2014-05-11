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
    ConnectionManager.h \
    LanguageEntry.h \
    LanguageManager.h \
    ServerListDialog.h \
    ServerEditDialog.h \
    OptionsDialog.h \
    AboutDialog.h

SOURCES += Main.cpp \
    OpenRcon.cpp \
    GameManager.cpp \
    ServerManager.cpp \
    ConnectionManager.cpp \
    LanguageManager.cpp \
    ServerListDialog.cpp \
    ServerEditDialog.cpp \
    OptionsDialog.cpp \
    AboutDialog.cpp

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

include(locale/Locale.pri)
include(game/Game.pri)
include(frostbite/Frostbite.pri)
include(bfbc2/BFBC2.pri)
include(frostbite2/Frostbite2.pri)
include(bf3/BF3.pri)
include(bf4/BF4.pri)
include(minecraft/Minecraft.pri)
