INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/DragDropTreeWidget.h \
    $$PWD/HistoryLineEdit.h \
    $$PWD/GameWidget.h

SOURCES += $$PWD/DragDropTreeWidget.cpp \
    $$PWD/HistoryLineEdit.cpp \
    $$PWD/GameWidget.cpp

include(frostbite/frostbite.pri)
include(frostbite2/frostbite2.pri)
include(bf3/bf3.pri)
include(bf4/bf4.pri)
