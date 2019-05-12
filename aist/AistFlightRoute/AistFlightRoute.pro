#-------------------------------------------------
#
# Project created by QtCreator 2019-04-03T11:04:47
#
#-------------------------------------------------
QT += core gui network widgets

TEMPLATE = app
DESTDIR = ../bin
TARGET = AistFlightRoute

SOURCES +=  src/main.cpp \
            src/mainwindow.cpp \
            src/flightplan.cpp \ 
            src/dialog.cpp \
            src/item.cpp \
            src/mission.cpp \
            src/geofence.cpp \
            src/rallypoint.cpp

HEADERS +=  src/mainwindow.h \
            src/flightplan.h \
            src/serializable.h \
            src/dialog.h \
            src/item.h \
            src/mission.h \
            src/geofence.h \
            src/rallypoint.h


LIBS += -L$$OUT_PWD/../bin -lqmapcontrol

INCLUDEPATH += $$PWD/../MapControl
DEPENDPATH += $$PWD/../MapControl

FORMS += \
    src/mainwindow.ui \
    src/dialog.ui
