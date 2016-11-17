INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += FrostbiteWidget.h \
    FrostbiteMainWidget.h \
    FrostbiteEventsWidget.h \
    FrostbiteChatWidget.h \
    FrostbiteBanListWidget.h \
    FrostbiteConsoleWidget.h

SOURCES += FrostbiteWidget.cpp \
    FrostbiteMainWidget.cpp \
    FrostbiteEventsWidget.cpp \
    FrostbiteChatWidget.cpp \
    FrostbiteBanListWidget.cpp \
    FrostbiteConsoleWidget.cpp

FORMS += FrostbiteMainWidget.ui \
    FrostbiteEventsWidget.ui \
    FrostbiteChatWidget.ui \
    FrostbiteBanListWidget.ui \
    FrostbiteConsoleWidget.ui

RESOURCES += Frostbite.qrc
