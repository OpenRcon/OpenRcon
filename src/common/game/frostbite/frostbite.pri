INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/FrostbiteClient.h \
    $$PWD/FrostbiteCommandHandler.h \
    $$PWD/FrostbiteConnection.h \
    $$PWD/FrostbiteRconPacket.h \
    $$PWD/FrostbiteRconPacketOrigin.h \
    $$PWD/FrostbiteRconPacketType.h \
    $$PWD/FrostbiteRconWord.h \
    $$PWD/FrostbiteUtils.h \
    $$PWD/LevelDictionary.h \
    $$PWD/WeaponDictionary.h

SOURCES += $$PWD/FrostbiteClient.cpp \
    $$PWD/FrostbiteCommandHandler.cpp \
    $$PWD/FrostbiteConnection.cpp \
    $$PWD/FrostbiteRconPacket.cpp \
    $$PWD/FrostbiteRconWord.cpp \
    $$PWD/FrostbiteUtils.cpp

include(types/types.pri)
