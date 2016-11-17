INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += Connection.h \
    CommandHandler.h \
    Client.h

SOURCES += Connection.cpp \
    CommandHandler.cpp \
    Client.cpp

include(frostbite/frostbite.pri)
include(bfbc2/bfbc2.pri)
include(frostbite2/frostbite2.pri)
include(bf3/bf3.pri)
include(bf4/bf4.pri)
