INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/MinecraftClient.h \
    $$PWD/MinecraftConnection.h \
    $$PWD/MinecraftRconPacketType.h \
    $$PWD/MinecraftRconPacket.h \
    $$PWD/MinecraftCommandHandler.h \
    $$PWD/MinecraftCommandType.h

SOURCES += $$PWD/MinecraftClient.cpp \
    $$PWD/MinecraftConnection.cpp \
    $$PWD/MinecraftRconPacket.cpp \
    $$PWD/MinecraftCommandHandler.cpp
