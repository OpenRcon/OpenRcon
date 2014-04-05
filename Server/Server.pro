QT += core \
      network \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenRcon_Server
TEMPLATE = app

HEADERS += Server.h \
    Server.h

SOURCES += Server.cpp \
    Server.cpp