QT       -= gui

TARGET = RaffleLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += rafflelib.cpp

HEADERS += rafflelib.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
