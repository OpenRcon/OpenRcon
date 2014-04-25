HEADERS += \
           minecraft/MinecraftRconPacket.h \
           minecraft/MinecraftWidget.h \
    minecraft/MinecraftConnection.h \
    minecraft/MinecraftCommandHandler.h \
    minecraft/Minecraft.h

SOURCES += minecraft/Minecraft.cpp \
           minecraft/MinecraftConnection.cpp \
           minecraft/MinecraftRconPacket.cpp \
           minecraft/MinecraftCommandHandler.cpp \
           minecraft/MinecraftWidget.cpp

FORMS += minecraft/Minecraft.ui

RESOURCES += minecraft/Minecraft.qrc
