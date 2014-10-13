INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += bfbc2/BFBC2.h \
    bfbc2/BFBC2CommandHandler.h \
    bfbc2/BFBC2LevelDictionary.h \
    bfbc2/BFBC2LevelEntry.h \
    bfbc2/BFBC2Mod.h \
    bfbc2/BFBC2ServerInfo.h \
    bfbc2/BFBC2Widget.h

SOURCES += bfbc2/BFBC2.cpp \
    bfbc2/BFBC2CommandHandler.cpp \
    bfbc2/BFBC2LevelDictionary.cpp \
    bfbc2/BFBC2Widget.cpp \
    $$PWD/BFBC2LevelEntry.cpp \
    $$PWD/BFBC2ServerInfo.cpp

FORMS += bfbc2/BFBC2Widget.ui

RESOURCES += bfbc2/BFBC2.qrc
