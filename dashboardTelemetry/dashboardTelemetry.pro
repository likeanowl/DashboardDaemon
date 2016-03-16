#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T19:50:25
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dashboardTelemetry
TEMPLATE = app

DEFINES += WIDGETSLIB_LIBRARY

SOURCES += \
    controlpanel.cpp \
    dashboard.cpp \
    facade.cpp \
    main.cpp \
    toolbar.cpp \
    tcpcommunicator.cpp \
    parser.cpp \
    isensorwidget.cpp \
    elementarydatasource.cpp \
    idatasource.cpp \
    widgetbutton.cpp \
    qcustomplot.cpp \
    customplotwidget.cpp \
    lcdnumberwidget.cpp \
    progressbarwidget.cpp \
    tablewidget.cpp \
    udpcommunicator.cpp

HEADERS  += \
    controlpanel.h \
    dashboard.h \
    facade.h \
    telemetry_const.h \
    toolbar.h \
    icommunicator.h \
    tcpcommunicator.h \
    parser.h \
    isensorwidget.h \
    widgetslib_global.h \
    idatasource.h \
    elementarydatasource.h \
    widgetbutton.h \
    qcustomplot.h \
    customplotwidget.h \
    lcdnumberwidget.h \
    progressbarwidget.h \
    tablewidget.h \
    udpcommunicator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
