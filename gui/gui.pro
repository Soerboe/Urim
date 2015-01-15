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

TARGET = UrimThummim
TEMPLATE = app

SOURCES += main.cpp\
        mainview.cpp \
    drawingsetupdialog.cpp \
    drawingcontroller.cpp \
    lotelementview.cpp \
    numberlotelementview.cpp \
    lotviewer.cpp \
    colorlotelementview.cpp

HEADERS  += mainview.h \
    drawingsetupdialog.h \
    drawingcontroller.h \
    lotelementview.h \
    numberlotelementview.h \
    lotviewer.h \
    colorlotelementview.h

FORMS    += mainview.ui \
    drawingsetupdialog.ui

CONFIG += c++11

INCLUDEPATH += $$PWD/../lib/
DEPENDPATH += $$PWD/../lib/

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lUrimThummimLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lUrimThummimLib
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lUrimThummimLib

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/release/UrimThummimLib.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/debug/UrimThummimLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/libUrimThummimLib.a
