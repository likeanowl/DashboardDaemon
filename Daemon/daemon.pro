#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T16:21:04
#
#-------------------------------------------------

TRIKCONTROL_BINDIR = ../../../trikRuntime/bin/arm-release
TRIKCONTROL_DIR = ../../../trikRuntime/trikControl

QT       += core gui
QT       += network
QT       += printsupport

TARGET = daemon
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++1y

TEMPLATE = app

INCLUDEPATH = \
        $$TRIKCONTROL_DIR/include/trikControl \
        telemetry/ \

INCLUDEPATH += ../../../trikRuntime/trikControl/include/trikControl

LIBS += -L$$TRIKCONTROL_BINDIR -ltrikControl -ltrikKernel -lqslog -ltrikHal

!macx {
        QMAKE_LFLAGS += -Wl,-O1,-rpath,.
}

SOURCES += main.cpp \
    tcpcommunicator.cpp \
    #fakeobserver.cpp \
    #fakedaemon.cpp \
    udpcommunicator.cpp \
    daemon.cpp \
    observer.cpp \
    gyroobserver.cpp \
    accelobserver.cpp \
    batteryobserver.cpp \
    powermotorobserver.cpp \
    encoderobserver.cpp
HEADERS += \
    tcpcommunicator.h \
    telemetry_const.h \
    #fakeobserver.h \
    #fakedaemon.h \
    udpcommunicator.h \
    icommunicator.h \
    daemon.h \
    observer.h \
    gyroobserver.h \
    accelobserver.h \
    batteryobserver.h \
    powermotorobserver.h \
    encoderobserver.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
