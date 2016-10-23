INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/Connection.h \
    $$PWD/CommandHandler.h \
    $$PWD/Client.h

SOURCES += $$PWD/Connection.cpp \
    $$PWD/CommandHandler.cpp \
    $$PWD/Client.cpp

include(frostbite/frostbite.pri)
include(frostbite2/frostbite2.pri)
include(bf3/bf3.pri)
include(bf4/bf4.pri)
