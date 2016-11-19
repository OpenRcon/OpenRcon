INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/Connection.h \
    $$PWD/CommandHandler.h \
    $$PWD/Client.h \
    $$PWD/Packet.h \
    $$PWD/PacketWord.h

SOURCES += $$PWD/Connection.cpp \
    $$PWD/CommandHandler.cpp \
    $$PWD/Client.cpp \
    $$PWD/Packet.cpp \
    $$PWD/PacketWord.cpp

include(frostbite/frostbite.pri)
include(bfbc2/bfbc2.pri)
include(frostbite2/frostbite2.pri)
include(bf3/bf3.pri)
include(bf4/bf4.pri)
