INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += Frostbite2Client.h \
    Frostbite2CommandHandler.h

SOURCES += Frostbite2Client.cpp \
    Frostbite2CommandHandler.cpp

include(types/types.pri)
