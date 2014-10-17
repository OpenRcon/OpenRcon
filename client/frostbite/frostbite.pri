INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/FrostbiteConnection.h \
    $$PWD/FrostbiteRconPacket.h \
    $$PWD/FrostbiteRconWord.h \
    $$PWD/FrostbiteCommandHandler.h \
    $$PWD/FrostbiteGame.h \
    $$PWD/FrostbiteUtils.h \
    $$PWD/TeamEntry.h \
    $$PWD/LevelEntry.h \
    $$PWD/GameModeEntry.h \
    $$PWD/LevelDictionary.h \
    $$PWD/PlayerSubset.h \
    $$PWD/MapListEntry.h \
    $$PWD/BanListEntry.h \
    $$PWD/ServerInfo.h \
    $$PWD/OnlineState.h \
    $$PWD/TeamScores.h \
    $$PWD/Time.h \
    $$PWD/Squad.h \
    $$PWD/ChatWidget.h \
    $$PWD/BanListWidget.h \
    $$PWD/ConsoleWidget.h \
    $$PWD/WeaponEntry.h \
    $$PWD/WeaponDictionary.h

SOURCES += $$PWD/FrostbiteConnection.cpp \
    $$PWD/FrostbiteRconPacket.cpp \
    $$PWD/FrostbiteRconWord.cpp \
    $$PWD/FrostbiteCommandHandler.cpp \
    $$PWD/FrostbiteGame.cpp \
    $$PWD/FrostbiteUtils.cpp \
    $$PWD/ChatWidget.cpp \
    $$PWD/BanListWidget.cpp \
    $$PWD/ConsoleWidget.cpp \
    $$PWD/MapListEntry.cpp \
    $$PWD/GameModeEntry.cpp \
    $$PWD/LevelEntry.cpp \
    $$PWD/ServerInfo.cpp \
    $$PWD/TeamEntry.cpp \
    $$PWD/PlayerSubset.cpp \
    $$PWD/WeaponEntry.cpp

FORMS += $$PWD/ChatWidget.ui \
    $$PWD/BanListWidget.ui \
    $$PWD/ConsoleWidget.ui

RESOURCES += $$PWD/Frostbite.qrc
