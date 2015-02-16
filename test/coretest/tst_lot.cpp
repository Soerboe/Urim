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
#include "lot.h"
#include "numberlotelement.h"
#include "colorlotelement.h"

using namespace std;

class LotTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:

void shouldCompareEqual()
{
    Lot lot1;
    lot1.addLotElement(shared_ptr<NumberLotElement> (new NumberLotElement(1337)));

    Lot lot2;
    lot2.addLotElement(shared_ptr<NumberLotElement> (new NumberLotElement(1337)));

    QVERIFY(lot1 == lot2);
}

void shouldNotCompareEqual()
{
    Lot lot1;
    lot1.addLotElement(shared_ptr<NumberLotElement> (new NumberLotElement(1337)));

    Lot lot2;
    lot2.addLotElement(shared_ptr<NumberLotElement> (new NumberLotElement(1338)));

    QVERIFY(lot1 != lot2);
}

void shouldHaveEqualHash()
{
    Lot lot1;
    lot1.addLotElement(shared_ptr<NumberLotElement> (new NumberLotElement(1337)));
    lot1.addLotElement(shared_ptr<ColorLotElement> (new ColorLotElement(Color(255, 0, 1, "Red"))));

    Lot lot2;
    lot2.addLotElement(shared_ptr<NumberLotElement> (new NumberLotElement(1337)));
    lot2.addLotElement(shared_ptr<ColorLotElement> (new ColorLotElement(Color(255, 0, 1, "Red"))));

    QVERIFY(lot1.hash() == lot2.hash());
}

void shouldHaveDifferentHash()
{
    Lot lot1;
    lot1.addLotElement(shared_ptr<ColorLotElement> (new ColorLotElement(Color(255, 0, 1, "Red"))));

    Lot lot2;
    lot2.addLotElement(shared_ptr<ColorLotElement> (new ColorLotElement(Color(255, 0, 1, "Bed"))));

    QVERIFY(lot1.hash() != lot2.hash());
}

};

REGISTER_TEST(LotTest)

#include "tst_lot.moc"


