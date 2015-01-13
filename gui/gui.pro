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

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

SOURCES += main.cpp\
        mainview.cpp \
    lotelementview.cpp \
    numberlotelementview.cpp \
    lotviewer.cpp \
    colorlotelementview.cpp

HEADERS  += mainview.h \
    lotelementview.h \
    numberlotelementview.h \
    lotviewer.h \
    colorlotelementview.h

FORMS    += mainview.ui

INCLUDEPATH += $$PWD/../lib

LIBS += -L$$OUT_PWD/../lib/ -lLibrary

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtQuickSampleLib/release/ -lQtQuickSampleLib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtQuickSampleLib/debug/ -lQtQuickSampleLib

CONFIG += c++11
