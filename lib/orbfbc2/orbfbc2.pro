QT += core \
    network

QT -= gui

TARGET = orbfbc2
TEMPLATE = lib

DEFINES += ORBFBC2_LIBRARY

SOURCES += ORBFBC2.cpp \
    ORBFBC2Commands.cpp \
    ORBFBC2Connection.cpp \
    ORBFBC2RconPacket.cpp \
    ORBFBC2RconWord.cpp

HEADERS += ORBFBC2.h \
    ORBFBC2_global.h \
    ORBFBC2Commands.h \
    ORBFBC2Connection.h \
    ORBFBC2RconPacket.h \
    ORBFBC2RconWord.h
