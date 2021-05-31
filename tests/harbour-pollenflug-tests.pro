QT += testlib network
QT -= gui

CONFIG += c++11 qt

SOURCES += testmain.cpp \
    frenchpollenbackendtests.cpp \
    abstractpollen.cpp \
    genericpollen.cpp

HEADERS += \
    frenchpollenbackendtests.h \
    abstractpollen.h \
    genericpollen.h

INCLUDEPATH += ../
include(../harbour-pollenflug.pri)

TARGET = FrenchBackendTest

DISTFILES += \
    testdata/fr.json

DEFINES += UNIT_TEST
