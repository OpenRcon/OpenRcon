INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/BF4.h \
    $$PWD/BF4CommandHandler.h \
    $$PWD/BF4LevelDictionary.h \
    $$PWD/BF4Widget.h \
    $$PWD/BF4GameModeEntry.h \
    $$PWD/BF4ServerInfo.h \
    $$PWD/PlayerListWidget.h \
    $$PWD/MapListWidget.h \
    $$PWD/SpectatorSlotsWidget.h \
    $$PWD/OptionsWidget.h \
    $$PWD/EventsWidget.h \
    $$PWD/BF4Preset.h

SOURCES += $$PWD/BF4.cpp \
    $$PWD/BF4CommandHandler.cpp \
    $$PWD/BF4LevelDictionary.cpp \
    $$PWD/BF4Widget.cpp \
    $$PWD/PlayerListWidget.cpp \
    $$PWD/EventsWidget.cpp \
    $$PWD/OptionsWidget.cpp \
    $$PWD/MapListWidget.cpp \
    $$PWD/SpectatorSlotsWidget.cpp \
    $$PWD/BF4GameModeEntry.cpp \
    $$PWD/BF4ServerInfo.cpp \
    $$PWD/BF4Preset.cpp

FORMS += $$PWD/BF4Widget.ui \
    $$PWD/EventsWidget.ui \
    $$PWD/OptionsWidget.ui \
    $$PWD/MapListWidget.ui \
    $$PWD/SpectatorSlotsWidget.ui

RESOURCES += $$PWD/BF4.qrc
