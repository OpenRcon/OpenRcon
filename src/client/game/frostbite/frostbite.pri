INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/FrostbiteWidget.h \
    $$PWD/FrostbiteEventsWidget.h \
    $$PWD/BanListWidget.h \
    $$PWD/FrostbiteConsoleWidget.h \
    $$PWD/FrostbiteChatWidget.h

SOURCES += $$PWD/FrostbiteWidget.cpp \
    $$PWD/FrostbiteEventsWidget.cpp \
    $$PWD/BanListWidget.cpp \
    $$PWD/FrostbiteConsoleWidget.cpp \
    $$PWD/FrostbiteChatWidget.cpp

FORMS += $$PWD/FrostbiteEventsWidget.ui \
    $$PWD/BanListWidget.ui \
    $$PWD/FrostbiteConsoleWidget.ui \
    $$PWD/FrostbiteChatWidget.ui

RESOURCES += $$PWD/Frostbite.qrc
