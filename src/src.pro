include(bf3/bf3.pri)
include(bfbc2/bfbc2.pri)

include(locale/locale.pri)

QT += core \
    gui \
    network \
    webkit

TARGET = openrcon
TEMPLATE = app

INCLUDEPATH += bf3 \
    bfbc2
DEPENDPATH += bf3 \
    bfbc2

HEADERS += OpenRcon.h \
    About.h \
    Connection.h \
    ConnectionManager.h \
    ConnectionTabWidget.h \
    Constants.h \
    Directory.h \
    PluginManager.h \
    ServerListDialog.h \
    ServerEditDialog.h \
    ServerEntry.h \
    ServerTableModel.h \
    SettingsDialog.h \
    DragDropListWidget.h \
    DragDropTreeWidget.h \
    PluginInterface.h \
    Plugin.h \
    PluginLoader.h \
    PluginDialog.h \
    SettingsManager.h

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
    Plugin.cpp \
    PluginLoader.cpp \
    PluginManager.cpp \
    PluginDialog.cpp \
    SettingsManager.cpp

FORMS += About.ui \
    OpenRcon.ui \
    PluginDialog.ui \
    ServerListDialog.ui \
    ServerEditDialog.ui \
    SettingsDialog.ui

RESOURCES += openrcon.qrc \
    data/data.qrc \
    data/graphics/graphics.qrc \
    locale/locale.qrc

win32:RC_FILE = openrcon.rc

macx { 
    TARGET = OpenRcon
    ICON = openrcon.icns
    QMAKE_INFO_PLIST = Info.plist
}
