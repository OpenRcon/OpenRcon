INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += bf4/BF4.h \
    bf4/BF4CommandHandler.h \
    bf4/BF4Widget.h \
    bf4/BF4LevelDictionary.h \
    bf4/BF4GameModeEntry.h \
    bf4/BF4ServerInfo.h \
    bf4/SpectatorSlotsWidget.h \
    bf4/MapListWidget.h \
    bf4/PlayerListWidget.h

SOURCES += bf4/BF4.cpp \
    bf4/BF4CommandHandler.cpp \
    bf4/BF4Widget.cpp \
    bf4/BF4LevelDictionary.cpp \
    bf4/SpectatorSlotsWidget.cpp \
    bf4/MapListWidget.cpp \
    bf4/PlayerListWidget.cpp

FORMS += bf4/BF4Widget.ui \
    bf4/SpectatorSlotsWidget.ui \
    bf4/MapListWidget.ui

RESOURCES += bf4/BF4.qrc
