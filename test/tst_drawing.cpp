/*
 * Copyright (C) Dag Henning Liodden Sørbø <daghenning@lioddensorbo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtTest>
#include "testrunner.h"
#include "drawing.h"
#include "numberlot.h"

using namespace std;

class DrawingTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldCompareEqual();
};

void DrawingTest::shouldCompareEqual()
{
    Drawing drawing1;
    drawing1.addLot(shared_ptr<NumberLot> (new NumberLot(1337)));

    Drawing drawing2;
    drawing2.addLot(shared_ptr<NumberLot> (new NumberLot(1337)));

    QVERIFY(drawing1 == drawing2);
}

REGISTER_TEST(DrawingTest)

#include "tst_drawing.moc"


