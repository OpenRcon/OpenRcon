include(locale/Locale.pri)

include(frostbite/Frostbite.pri)
include(bfbase/BFBase.pri)
include(bfbc2/BFBC2.pri)
include(bf3/BF3.pri)
include(bf4/BF4.pri)

include(minecraft/Minecraft.pri)

QT += core \
      gui \
      network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenRcon
TEMPLATE = app

INCLUDEPATH += frostbite \
    bfbase \
    bfbc2 \
    bf3 \
    bf4 \
    minecraft

DEPENDPATH += frostbite \
    bfbase \
    bfbc2 \
    bf3 \
    bf4 \
    minecraft

HEADERS += OpenRcon.h \
    Constants.h \
    Directory.h \
    Connection.h \
    ConnectionTabWidget.h \
    GameEntry.h \
    ServerEntry.h \
    LanguageEntry.h \
    GameManager.h \
    ServerManager.h \
    LanguageManager.h \
    ServerListDialog.h \
    ServerEditDialog.h \
    SettingsDialog.h \
    AboutDialog.h \
    Game.h \
    DragDropListWidget.h \
    DragDropTreeWidget.h

SOURCES += Main.cpp \
    OpenRcon.cpp \
    Directory.cpp \
    Connection.cpp \
    GameManager.cpp \
    ServerManager.cpp \
    LanguageManager.cpp \
    ServerListDialog.cpp \
    ServerEditDialog.cpp \
    SettingsDialog.cpp \
    AboutDialog.cpp \
    Game.cpp \
    DragDropListWidget.cpp \
    DragDropTreeWidget.cpp

FORMS += OpenRcon.ui \
    ServerListDialog.ui \
    ServerEditDialog.ui \
    SettingsDialog.ui \
    AboutDialog.ui

RESOURCES += OpenRcon.qrc

win32:RC_FILE = openrcon.rc

macx {
    TARGET = OpenRcon
    ICON = openrcon.icns
    QMAKE_INFO_PLIST = Info.plist
}
