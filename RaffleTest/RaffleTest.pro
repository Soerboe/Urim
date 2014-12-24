QT       += testlib

QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    tst_lotviewer.cpp \
    tst_drawingsession.cpp \
    tst_randomnumbergenerator.cpp \
    tst_drawing.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $$PWD/../RaffleLib

LIBS += -L$$OUT_PWD/../RaffleLib/ -lRaffleLib

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtQuickSampleLib/release/ -lQtQuickSampleLib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtQuickSampleLib/debug/ -lQtQuickSampleLib

CONFIG += c++11

HEADERS += \
    autotest.h
