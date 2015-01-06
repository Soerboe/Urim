#
# Copyright (C) Dag Henning Liodden Sørbø <daghenning@lioddensorbo.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

QT       += testlib
QT       -= gui

TARGET = testrunner
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    testrunner.h

SOURCES += \
    main.cpp \
    tst_lotviewer.cpp \
    tst_drawingsession.cpp \
    tst_randomnumbergenerator.cpp \
    tst_drawing.cpp \
    benchmarking.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $$PWD/../lib

LIBS += -L$$OUT_PWD/../lib/ -lLibrary

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtQuickSampleLib/release/ -lQtQuickSampleLib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtQuickSampleLib/debug/ -lQtQuickSampleLib

CONFIG += c++11
