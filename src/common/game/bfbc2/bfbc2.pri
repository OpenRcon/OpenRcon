INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += BFBC2Client.h \
    BFBC2CommandHandler.h \
    BFBC2LevelDictionary.h

SOURCES += BFBC2Client.cpp \
    BFBC2CommandHandler.cpp \
    BFBC2LevelDictionary.cpp

include(types/types.pri)
