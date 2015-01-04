QT       -= gui

TARGET = RaffleLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    randomgenerator.cpp \
    randomnumbergenerator.cpp \
    drawingsession.cpp \
    lot.cpp \
    drawing.cpp \
    numberlot.cpp \
    colorlot.cpp \
    randomcolorgenerator.cpp

HEADERS += \
    randomgenerator.h \
    randomnumbergenerator.h \
    drawingsession.h \
    lot.h \
    drawing.h \
    numberlot.h \
    lotviewer.h \
    colorlot.h \
    color.h \
    randomcolorgenerator.h \
    nomoreuniqueresultsexception.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG += c++11
