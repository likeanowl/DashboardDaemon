#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T16:21:04
#
#-------------------------------------------------

TRIKCONTROL_BINDIR = /trikRuntime/bin/arm-release
TRIKCONTROL_DIR = ../../trikRuntime/trikControl

QT       += core
QT       += network
QT       += gui

TARGET = daemon
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++1y

TEMPLATE = app

INCLUDEPATH = \
        $$TRIKCONTROL_DIR/include \
        telemetry/ \

LIBS += -L$$TRIKCONTROL_BINDIR -ltrikControl -ltrikKernel -lqslog -ltrikHal

!macx {
        QMAKE_LFLAGS += -Wl,-O1,-rpath,.
}

SOURCES += main.cpp \
    daemon.cpp \
    tcpcommunicator.cpp \
    observer.cpp \
    fakeobserver.cpp \
    fakedaemon.cpp
HEADERS += \
    daemon.h \
    tcpcommunicator.h \
    observer.h \
    telemetry_const.h \
    fakeobserver.h \
    fakedaemon.h
