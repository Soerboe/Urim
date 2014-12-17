QT       += testlib

QT       -= gui

TARGET = tst_raffletest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_raffletest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $$PWD/../RaffleLib

LIBS += -L$$OUT_PWD/../RaffleLib/ -lRaffleLib

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtQuickSampleLib/release/ -lQtQuickSampleLib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtQuickSampleLib/debug/ -lQtQuickSampleLib
