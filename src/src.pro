QT += core \
    network \
    gui \
    widgets

CONFIG += c++17

TARGET = openrcon
TEMPLATE = app

include(client/client.pri)
include(common/common.pri)
