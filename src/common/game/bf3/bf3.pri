INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/BF3Client.h \
    $$PWD/BF3CommandHandler.h \
    $$PWD/BF3LevelDictionary.h \
    $$PWD/BF3WeaponDictionary.h

SOURCES += $$PWD/BF3Client.cpp \
    $$PWD/BF3CommandHandler.cpp \
    $$PWD/BF3LevelDictionary.cpp \
    $$PWD/BF3WeaponDictionary.cpp

include(types/types.pri)
