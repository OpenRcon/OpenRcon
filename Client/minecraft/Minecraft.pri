INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += minecraft/Minecraft.h \
    minecraft/MinecraftConnection.h \
    minecraft/MinecraftRconPacket.h \
    minecraft/MinecraftWidget.h \
    minecraft/MinecraftRconPacketType.h

SOURCES += minecraft/Minecraft.cpp \
    minecraft/MinecraftConnection.cpp \
    minecraft/MinecraftRconPacket.cpp \
    minecraft/MinecraftWidget.cpp

FORMS += \
    minecraft/MinecraftWidget.ui

RESOURCES += minecraft/Minecraft.qrc
