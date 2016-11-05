INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/BF4Widget.h \
    $$PWD/BF4MainWidget.h \
    $$PWD/BF4OptionsWidget.h \
    $$PWD/BF4MapListWidget.h \
    $$PWD/BF4SpectatorSlotsWidget.h \
    $$PWD/PlayerListWidget.h

SOURCES += $$PWD/BF4Widget.cpp \
    $$PWD/BF4MainWidget.cpp \
    $$PWD/BF4OptionsWidget.cpp \
    $$PWD/BF4MapListWidget.cpp \
    $$PWD/BF4SpectatorSlotsWidget.cpp \
    $$PWD/PlayerListWidget.cpp

FORMS += $$PWD/BF4OptionsWidget.ui \
    $$PWD/BF4MapListWidget.ui \
    $$PWD/BF4SpectatorSlotsWidget.ui

RESOURCES += $$PWD/BF4.qrc
