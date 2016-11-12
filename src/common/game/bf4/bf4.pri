INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/BF4Client.h \
    $$PWD/BF4CommandHandler.h \
    $$PWD/BF4LevelDictionary.h \
    $$PWD/BF4WeaponDictionary.h

SOURCES += $$PWD/BF4Client.cpp \
    $$PWD/BF4CommandHandler.cpp \
    $$PWD/BF4LevelDictionary.cpp \
    $$PWD/BF4WeaponDictionary.cpp

include(types/types.pri)
