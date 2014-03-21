include(Locale/Locale.pri)

include(BFBC2/BFBC2.pri)
include(BF3/bf3.pri)
include(Minecraft/Minecraft.pri)

QT += core \
      gui \
      network \
      webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenRcon
TEMPLATE = app

INCLUDEPATH += bfbc2 \
               bf3 \
               minecraft



DEPENDPATH += bfbc2 \
              bf3 \
              minecraft

HEADERS += OpenRcon.h \
    About.h \
    Connection.h \
    ConnectionManager.h \
    ConnectionTabWidget.h \
    Constants.h \
    Directory.h \
    ServerListDialog.h \
    ServerEditDialog.h \
    ServerEntry.h \
    ServerTableModel.h \
    SettingsDialog.h \
    DragDropListWidget.h \
    DragDropTreeWidget.h \
    SettingsManager.h \
    Game.h \
    GameEntry.h

SOURCES += OpenRcon.cpp \
    About.cpp \
    Connection.cpp \
    ConnectionManager.cpp \
    Directory.cpp \
    Main.cpp \
    ServerListDialog.cpp \
    ServerEditDialog.cpp \
    ServerTableModel.cpp \
    SettingsDialog.cpp \
    DragDropListWidget.cpp \
    DragDropTreeWidget.cpp \
    SettingsManager.cpp \
    Game.cpp \
    GameEntry.cpp

FORMS += About.ui \
    OpenRcon.ui \
    ServerListDialog.ui \
    ServerEditDialog.ui \
    SettingsDialog.ui

RESOURCES += openrcon.qrc \
             data/graphics/graphics.qrc

win32:RC_FILE = openrcon.rc

macx {
    TARGET = OpenRcon
    ICON = openrcon.icns
    QMAKE_INFO_PLIST = Info.plist
}
