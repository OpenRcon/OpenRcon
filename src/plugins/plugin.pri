include(../client/plugins/plugins.pri)

QT -= gui

CONFIG += plugin

TEMPLATE = lib

CONFIG(debug, debug|release) {
  CONFIG += console
  DESTDIR       = ../../client/debug/plugins
}

CONFIG(release, debug|release) {
  DESTDIR       = ../../client/release/plugins
}

include(../common/common.pro)
