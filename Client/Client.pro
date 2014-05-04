include(locale/Locale.pri)
include(game/Game.pri)

include(frostbite/Frostbite.pri)
include(bfbc2/BFBC2.pri)
include(frostbite2/Frostbite2.pri)
include(bf3/BF3.pri)
include(bf4/BF4.pri)

include(minecraft/Minecraft.pri)

QT += core \     
    network \
    gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = OpenRcon
TEMPLATE = app

INCLUDEPATH += game \
    frostbite \
    bfbc2 \
    frostbite2 \
    bf3 \
    bf4 \
    minecraft

DEPENDPATH += game \
    frostbite \
    bfbc2 \
    frostbite2 \
    bf3 \
    bf4 \
    minecraft

HEADERS += OpenRcon.h \
    Constants.h \
    GameEntry.h \
    ServerEntry.h \
    LanguageEntry.h \
    GameManager.h \
    ServerManager.h \
    LanguageManager.h \
    ServerListDialog.h \
    ServerEditDialog.h \
    AboutDialog.h \
    DragDropListWidget.h \
    DragDropTreeWidget.h \
    ConnectionManager.h \
    OptionsDialog.h

SOURCES += Main.cpp \
    OpenRcon.cpp \
    GameManager.cpp \
    ServerManager.cpp \
    LanguageManager.cpp \
    ServerListDialog.cpp \
    ServerEditDialog.cpp \
    AboutDialog.cpp \
    DragDropListWidget.cpp \
    DragDropTreeWidget.cpp \
    ConnectionManager.cpp \
    OptionsDialog.cpp

FORMS += OpenRcon.ui \
    ServerListDialog.ui \
    ServerEditDialog.ui \
    AboutDialog.ui \
    OptionsDialog.ui

RESOURCES += OpenRcon.qrc

win32:RC_FILE = openrcon.rc

macx {
    TARGET = OpenRcon
    ICON = openrcon.icns
    QMAKE_INFO_PLIST = Info.plist
}
