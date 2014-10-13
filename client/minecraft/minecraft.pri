INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/Minecraft.h \
    $$PWD/MinecraftConnection.h \
    $$PWD/MinecraftRconPacketType.h \
    $$PWD/MinecraftRconPacket.h \
    $$PWD/MinecraftWidget.h

SOURCES += $$PWD/Minecraft.cpp \
    $$PWD/MinecraftConnection.cpp \
    $$PWD/MinecraftRconPacket.cpp \
    $$PWD/MinecraftWidget.cpp

FORMS += $$PWD/MinecraftWidget.ui

RESOURCES += $$PWD/Minecraft.qrc
