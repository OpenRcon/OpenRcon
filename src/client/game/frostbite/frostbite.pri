INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/FrostbiteWidget.h \
    $$PWD/FrostbiteEventsWidget.h \
    $$PWD/ChatWidget.h \
    $$PWD/BanListWidget.h \
    $$PWD/ConsoleWidget.h

SOURCES += $$PWD/FrostbiteWidget.cpp \
    $$PWD/FrostbiteEventsWidget.cpp \
    $$PWD/ChatWidget.cpp \
    $$PWD/BanListWidget.cpp \
    $$PWD/ConsoleWidget.cpp

FORMS += $$PWD/FrostbiteEventsWidget.ui \
    $$PWD/ChatWidget.ui \
    $$PWD/BanListWidget.ui \
    $$PWD/ConsoleWidget.ui

RESOURCES += $$PWD/Frostbite.qrc
