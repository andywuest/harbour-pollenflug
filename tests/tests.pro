QT += testlib network
QT -= gui

CONFIG += c++11 qt

SOURCES += testmain.cpp \
    frenchpollenbackendtests.cpp

HEADERS += \
    frenchpollenbackendtests.h

INCLUDEPATH += ../
include(../harbour-pollenflug.pri)

TARGET = FrenchBackendTest

DISTFILES += \
    testdata/fr.json

DEFINES += UNIT_TEST
