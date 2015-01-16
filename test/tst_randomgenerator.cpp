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
#include "randomgenerator.h"
#include "numberlotelement.h"

using namespace std;

class DummyRandomGenerator : public RandomGenerator
{
public:
    unsigned long numberOfUniqueResults() const
    {
        return 0;
    }

    shared_ptr<LotElement> generate()
    {
        return shared_ptr<NumberLotElement>(new NumberLotElement(0));
    }
};

class RandomGeneratorTest : public QObject
{
    Q_OBJECT

//public:
//    RandomGeneratorTest();

private Q_SLOTS:
    void shouldAddNameToGeneratedLotElement();
};

//RandomGeneratorTest::RandomGeneratorTest()
//{
//}


void RandomGeneratorTest::shouldAddNameToGeneratedLotElement()
{
    DummyRandomGenerator generator;
    generator.setName("Dummy");
    shared_ptr<LotElement> lotElement = generator();
    QVERIFY(lotElement->name() == "Dummy2");
}

REGISTER_TEST(RandomGeneratorTest)

#include "tst_randomgenerator.moc"

