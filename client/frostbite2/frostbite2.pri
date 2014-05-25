INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += frostbite2/PlayerInfo.h \
    frostbite2/Frostbite2ServerInfo.h \
    frostbite2/Frostbite2CommandHandler.h \
    frostbite2/ReservedSlotsWidget.h \
    frostbite2/ChatWidget.h

SOURCES += frostbite2/Frostbite2CommandHandler.cpp \
    frostbite2/ReservedSlotsWidget.cpp \
    frostbite2/ChatWidget.cpp

FORMS += frostbite2/ReservedSlotsWidget.ui \
    frostbite2/ChatWidget.ui
