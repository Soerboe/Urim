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

TEMPLATE = subdirs
OTHER_FILES += common.pri
SUBDIRS += \
    core \
    gui \
    testutils \
    coretest \
    guitest \
    app

gui.depends = core
coretest.depends = core testutils
guitest.depends = core gui testutils
app.depends = core gui
