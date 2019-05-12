QT += testlib core gui network widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app
DESTDIR = ../bin
TARGET = Test

SOURCES +=  tst_test.cpp \
            ../AistFlightRoute/src/flightplan.cpp \
            ../AistFlightRoute/src/mission.cpp \
            ../AistFlightRoute/src/item.cpp \
            ../AistFlightRoute/src/geofence.cpp \
            ../AistFlightRoute/src/rallypoint.cpp

HEADERS +=  ../AistFlightRoute/src/serializable.h \
            ../AistFlightRoute/src/flightplan.h \
            ../AistFlightRoute/src/mission.h \
            ../AistFlightRoute/src/item.h \
            ../AistFlightRoute/src/geofence.h \
            ../AistFlightRoute/src/rallypoint.h



LIBS += -L$$OUT_PWD/../bin -lqmapcontrol

INCLUDEPATH += $$PWD/../MapControl
DEPENDPATH += $$PWD/../MapControl
