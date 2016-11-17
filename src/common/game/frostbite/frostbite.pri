INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += FrostbiteClient.h \
    FrostbiteCommandHandler.h \
    FrostbiteConnection.h \
    FrostbiteRconPacket.h \
    FrostbiteRconPacketOrigin.h \
    FrostbiteRconPacketType.h \
    FrostbiteRconWord.h \
    FrostbiteUtils.h \
    LevelDictionary.h \
    WeaponDictionary.h

SOURCES += FrostbiteClient.cpp \
    FrostbiteCommandHandler.cpp \
    FrostbiteConnection.cpp \
    FrostbiteRconPacket.cpp \
    FrostbiteRconWord.cpp \
    FrostbiteUtils.cpp

include(types/types.pri)
