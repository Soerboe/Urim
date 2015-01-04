#include <QtTest>
#include <memory>
#include "testrunner.h"
#include "randomnumbergenerator.h"

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
    RandomGenerator::pickSeed();
    RandomNumberGenerator generator;
    shared_ptr<NumberLot> numberLot = dynamic_pointer_cast<NumberLot> (generator());
    QVERIFY(numberLot->number() >= 0);
}

REGISTER_TEST(RandomNumberGeneratorTest)

#include "tst_randomnumbergenerator.moc"

