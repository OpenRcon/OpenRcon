QT += core \
    network

QT -= gui

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += GameType.h \
    GameEntry.h \
    GameManager.h \
    ServerEntry.h

SOURCES += GameType.cpp \
    GameEntry.cpp \
    GameManager.cpp \
    ServerEntry.cpp

include(game/game.pri)
