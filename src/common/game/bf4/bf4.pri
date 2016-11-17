INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += BF4Client.h \
    BF4CommandHandler.h \
    BF4LevelDictionary.h \
    BF4WeaponDictionary.h

SOURCES += BF4Client.cpp \
    BF4CommandHandler.cpp \
    BF4LevelDictionary.cpp \
    BF4WeaponDictionary.cpp

include(types/types.pri)
