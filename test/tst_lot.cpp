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

using namespace std;

class LotTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldCompareEqual();
};

void LotTest::shouldCompareEqual()
{
    Lot lot1;
    lot1.addLotElement(shared_ptr<NumberLotElement> (new NumberLotElement(1337)));

    Lot lot2;
    lot2.addLotElement(shared_ptr<NumberLotElement> (new NumberLotElement(1337)));

    QVERIFY(lot1 == lot2);
}

REGISTER_TEST(LotTest)

#include "tst_lot.moc"


