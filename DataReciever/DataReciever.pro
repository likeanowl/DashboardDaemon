QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = DataReciever
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    communicator.cpp

HEADERS += \
    communicator.h
