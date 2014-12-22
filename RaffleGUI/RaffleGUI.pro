QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RaffleGUI
TEMPLATE = app

SOURCES += main.cpp\
        mainview.cpp

HEADERS  += mainview.h

FORMS    += mainview.ui

INCLUDEPATH += $$PWD/../RaffleLib

LIBS += -L$$OUT_PWD/../RaffleLib/ -lRaffleLib

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtQuickSampleLib/release/ -lQtQuickSampleLib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtQuickSampleLib/debug/ -lQtQuickSampleLib

CONFIG += c++11
