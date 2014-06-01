INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += frostbite2/PlayerInfo.h \
    frostbite2/Frostbite2ServerInfo.h \
    frostbite2/Frostbite2CommandHandler.h \
    frostbite2/ChatWidget.h \
    frostbite2/BanListWidget.h \
    frostbite2/ReservedSlotsWidget.h

SOURCES += frostbite2/Frostbite2CommandHandler.cpp \
    frostbite2/ChatWidget.cpp \
    frostbite2/BanListWidget.cpp \
    frostbite2/ReservedSlotsWidget.cpp

FORMS += frostbite2/ChatWidget.ui \
    frostbite2/BanListWidget.ui \
    frostbite2/ReservedSlotsWidget.ui
