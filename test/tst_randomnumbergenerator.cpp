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
#include <memory>
#include "testrunner.h"
#include "randomnumbergenerator.h"
#include "numberlotelement.h"

using namespace std;

class RandomNumberGeneratorTest : public QObject
{
    Q_OBJECT

public:
    RandomNumberGeneratorTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void shouldGenerateRandomInteger();
};

RandomNumberGeneratorTest::RandomNumberGeneratorTest()
{
}

void RandomNumberGeneratorTest::initTestCase()
{
}

void RandomNumberGeneratorTest::cleanupTestCase()
{
}

void RandomNumberGeneratorTest::shouldGenerateRandomInteger()
{
    RandomGenerator::init();
    RandomNumberGenerator generator;
    shared_ptr<NumberLotElement> numberLotElement = dynamic_pointer_cast<NumberLotElement> (generator());
    QVERIFY(numberLotElement->number() >= 0);
}

REGISTER_TEST(RandomNumberGeneratorTest)

#include "tst_randomnumbergenerator.moc"

