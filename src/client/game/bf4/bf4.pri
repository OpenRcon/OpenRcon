INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/BF4Widget.h \
    $$PWD/BF4MainWidget.h \
    $$PWD/PlayerListWidget.h \
    $$PWD/MapListWidget.h \
    $$PWD/SpectatorSlotsWidget.h \
    $$PWD/BF4OptionsWidget.h \


SOURCES += $$PWD/BF4Widget.cpp \
    $$PWD/BF4MainWidget.cpp \
    $$PWD/PlayerListWidget.cpp \
    $$PWD/MapListWidget.cpp \
    $$PWD/SpectatorSlotsWidget.cpp \
    $$PWD/BF4OptionsWidget.cpp \

FORMS += $$PWD/BF4MainWidget.ui \
    $$PWD/MapListWidget.ui \
    $$PWD/SpectatorSlotsWidget.ui \
    $$PWD/BF4OptionsWidget.ui

RESOURCES += $$PWD/BF4.qrc
