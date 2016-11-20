INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += OpenRcon.h \
    Constants.h \
    ServerManager.h \
    LanguageEntry.h \
    LanguageManager.h \
    SessionManager.h

SOURCES += Main.cpp \
    OpenRcon.cpp \
    ServerManager.cpp \
    LanguageManager.cpp \
    SessionManager.cpp \
    LanguageEntry.cpp

RESOURCES += OpenRcon.qrc

RC_ICONS = $$PWD/images/icons/openrcon.ico

include(translations/translations.pri)
include(gui/gui.pri)
include(game/game.pri)
