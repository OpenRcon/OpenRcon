INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/Frostbite2Client.h \
    $$PWD/Frostbite2CommandHandler.h

SOURCES += $$PWD/Frostbite2Client.cpp \
    $$PWD/Frostbite2CommandHandler.cpp

include(types/types.pri)
