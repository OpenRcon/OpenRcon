INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/FrostbiteWidget.h \
    $$PWD/FrostbiteEventsWidget.h \
    $$PWD/FrostbiteChatWidget.h \
    $$PWD/FrostbiteBanListWidget.h \
    $$PWD/FrostbiteConsoleWidget.h

SOURCES += $$PWD/FrostbiteWidget.cpp \
    $$PWD/FrostbiteEventsWidget.cpp \
    $$PWD/FrostbiteChatWidget.cpp \
    $$PWD/FrostbiteBanListWidget.cpp \
    $$PWD/FrostbiteConsoleWidget.cpp

FORMS += $$PWD/FrostbiteEventsWidget.ui \
    $$PWD/FrostbiteChatWidget.ui \
    $$PWD/FrostbiteBanListWidget.ui \
    $$PWD/FrostbiteConsoleWidget.ui

RESOURCES += $$PWD/Frostbite.qrc
