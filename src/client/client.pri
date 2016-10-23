INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/OpenRcon.h \
    $$PWD/Constants.h \
    $$PWD/ServerEntry.h \
    $$PWD/ServerManager.h \
    $$PWD/LanguageEntry.h \
    $$PWD/LanguageManager.h \
    $$PWD/SessionManager.h

SOURCES += $$PWD/Main.cpp \
    $$PWD/OpenRcon.cpp \
    $$PWD/ServerEntry.cpp \
    $$PWD/ServerManager.cpp \
    $$PWD/LanguageManager.cpp \
    $$PWD/SessionManager.cpp \
    $$PWD/LanguageEntry.cpp

RESOURCES += $$PWD/OpenRcon.qrc

RC_ICONS = $$PWD/images/icons/openrcon.ico

include(translations/translations.pri)
include(gui/gui.pri)
include(game/game.pri)
