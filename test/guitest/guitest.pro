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

lessThan(QT_VERSION, 5.3): error("Requires Qt >= 5.3")

include(../testutils/testutils.pri)
include(../../core/core.pri)
include(../../gui/gui.pri)

QT += testlib core gui widgets svg

TARGET = guitester
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

CONFIG += c++11

SOURCES += *.cpp
