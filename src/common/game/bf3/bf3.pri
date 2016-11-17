INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += BF3Client.h \
    BF3CommandHandler.h \
    BF3LevelDictionary.h \
    BF3WeaponDictionary.h

SOURCES += BF3Client.cpp \
    BF3CommandHandler.cpp \
    BF3LevelDictionary.cpp \
    BF3WeaponDictionary.cpp

include(types/types.pri)
