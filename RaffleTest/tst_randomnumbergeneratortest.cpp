//#include <QString>
#include <QtTest>
#include <memory>
#include "autotest.h"
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
    RandomNumberGenerator generator;
    shared_ptr<NumberLot> numberLot = dynamic_pointer_cast<NumberLot> (generator.generate());
    QVERIFY(numberLot >= 0 || numberLot < 0);
}

DECLARE_TEST(RandomNumberGeneratorTest)

#include "tst_randomnumbergeneratortest.moc"

