INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/GameType.h \
    $$PWD/GameEntry.h \
    $$PWD/GameManager.h

SOURCES += $$PWD/GameType.cpp \
    $$PWD/GameEntry.cpp \
    $$PWD/GameManager.cpp

include(game/game.pri)
