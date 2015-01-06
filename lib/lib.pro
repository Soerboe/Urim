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

QT       -= gui

TARGET = Library
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
