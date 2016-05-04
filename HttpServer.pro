QT += core network widgets
QT -= gui

TARGET = HttpServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    HttpServer.cpp \
    TCPConnection.cpp \
    TCPConnectionPrivate.cpp \
    ThreadManager.cpp \
    TCPProcessor.cpp

HEADERS += \
    HttpServer.h \
    TCPConnection.h \
    TCPConnectionPrivate.h \
    ThreadManager.h \
    TCPProcessor.h

