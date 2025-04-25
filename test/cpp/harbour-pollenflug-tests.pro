QT += testlib network
QT -= gui

CONFIG += c++11 qt

SOURCES += testmain.cpp \
    pollenbackendtests.cpp

HEADERS += pollenbackendtests.h

INCLUDEPATH += ../../
include(../../harbour-pollenflug.pri)

TARGET = PollenBackendTest

DISTFILES += \
    testdata/ch_oak.html \
    testdata/fr.json

DEFINES += UNIT_TEST
