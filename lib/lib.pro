QT += core \
    network

TARGET = openrcon
TEMPLATE = lib

DEFINES += OPENRCON_LIBRARY

HEADERS += OpenRcon.h \
        OpenRcon_global.h \
        Connection.h

SOURCES += OpenRcon.cpp \
    Connection.cpp
