INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/Connection.h \
    $$PWD/CommandHandler.h

SOURCES += $$PWD/Connection.cpp \
    $$PWD/CommandHandler.cpp

include(frostbite/frostbite.pri)
include(frostbite2/frostbite2.pri)
include(bf4/bf4.pri)
