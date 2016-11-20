INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/GameType.h \
    $$PWD/GameEntry.h \
    $$PWD/GameManager.h \
    $$PWD/ServerEntry.h

SOURCES += $$PWD/GameType.cpp \
    $$PWD/GameEntry.cpp \
    $$PWD/GameManager.cpp \
    $$PWD/ServerEntry.cpp

include(game/game.pri)
