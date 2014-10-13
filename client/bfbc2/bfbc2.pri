INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/BFBC2.h \
    $$PWD/BFBC2CommandHandler.h \
    $$PWD/BFBC2LevelDictionary.h \
    $$PWD/BFBC2LevelEntry.h \
    $$PWD/BFBC2Mod.h \
    $$PWD/BFBC2ServerInfo.h \
    $$PWD/BFBC2Widget.h

SOURCES += $$PWD/BFBC2.cpp \
    $$PWD/BFBC2CommandHandler.cpp \
    $$PWD/BFBC2LevelDictionary.cpp \
    $$PWD/BFBC2Widget.cpp \
    $$PWD/BFBC2LevelEntry.cpp \
    $$PWD/BFBC2ServerInfo.cpp

FORMS += $$PWD/BFBC2Widget.ui

RESOURCES += $$PWD/BFBC2.qrc
