INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += frostbite/FrostbiteConnection.h \
    frostbite/FrostbiteRconPacket.h \
    frostbite/FrostbiteRconWord.h \
    frostbite/FrostbiteCommandHandler.h \
    frostbite/FrostbiteGame.h \
    frostbite/FrostbiteUtils.h \
    frostbite/TeamEntry.h \
    frostbite/LevelEntry.h \
    frostbite/GameModeEntry.h \
    frostbite/LevelDictionary.h \
    frostbite/PlayerSubset.h \
    frostbite/MapListEntry.h \
    frostbite/BanListEntry.h \
    frostbite/ServerInfo.h \
    frostbite/OnlineState.h \
    frostbite/TeamScores.h \
    frostbite/Time.h \
    frostbite/Squad.h \
    frostbite/BanListWidget.h \
    frostbite/ConsoleWidget.h \
    frostbite/ConsoleLineEdit.h

SOURCES += frostbite/FrostbiteConnection.cpp \
    frostbite/FrostbiteRconPacket.cpp \
    frostbite/FrostbiteRconWord.cpp \
    frostbite/FrostbiteCommandHandler.cpp \
    frostbite/FrostbiteGame.cpp \
    frostbite/FrostbiteUtils.cpp \
    frostbite/BanListWidget.cpp \
    frostbite/ConsoleWidget.cpp \
    frostbite/ConsoleLineEdit.cpp

FORMS += frostbite/BanListWidget.ui \
    frostbite/ConsoleWidget.ui

RESOURCES += frostbite/Frostbite.qrc
