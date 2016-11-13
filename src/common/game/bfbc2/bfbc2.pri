INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/BFBC2Client.h \
    $$PWD/BFBC2CommandHandler.h \
    $$PWD/BFBC2LevelDictionary.h

SOURCES += $$PWD/BFBC2Client.cpp \
    $$PWD/BFBC2CommandHandler.cpp \
    $$PWD/BFBC2LevelDictionary.cpp

include(types/types.pri)
