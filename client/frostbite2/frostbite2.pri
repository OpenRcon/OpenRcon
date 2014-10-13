INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/PlayerInfo.h \
    $$PWD/Frostbite2ServerInfo.h \
    $$PWD/Frostbite2CommandHandler.h \
    $$PWD/ReservedSlotsWidget.h

SOURCES += $$PWD/Frostbite2CommandHandler.cpp \
    $$PWD/ReservedSlotsWidget.cpp \
    $$PWD/Frostbite2ServerInfo.cpp

FORMS += $$PWD/ReservedSlotsWidget.ui
