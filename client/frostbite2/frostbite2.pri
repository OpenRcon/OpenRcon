INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += frostbite2/PlayerInfo.h \
    frostbite2/Frostbite2ServerInfo.h \
    frostbite2/Frostbite2CommandHandler.h \
    frostbite2/ReservedSlotsWidget.h

SOURCES += frostbite2/Frostbite2CommandHandler.cpp \
    frostbite2/ReservedSlotsWidget.cpp

FORMS += frostbite2/ReservedSlotsWidget.ui
