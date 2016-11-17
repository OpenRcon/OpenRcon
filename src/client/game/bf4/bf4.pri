INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += BF4Widget.h \
    BF4MainWidget.h \
    BF4PlayerListWidget.h \
    BF4OptionsWidget.h \
    BF4MapListWidget.h \
    BF4SpectatorSlotsWidget.h

SOURCES += BF4Widget.cpp \
    BF4MainWidget.cpp \
    BF4PlayerListWidget.cpp \
    BF4OptionsWidget.cpp \
    BF4MapListWidget.cpp \
    BF4SpectatorSlotsWidget.cpp

FORMS += BF4OptionsWidget.ui \
    BF4MapListWidget.ui \
    BF4SpectatorSlotsWidget.ui

RESOURCES += BF4.qrc
