#include <QString>
#include <QtTest>

#include "rafflelib.h"

class RaffleTest : public QObject
{
    Q_OBJECT

public:
    RaffleTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

RaffleTest::RaffleTest()
{
}

void RaffleTest::initTestCase()
{
}

void RaffleTest::cleanupTestCase()
{
}

void RaffleTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void RaffleTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_APPLESS_MAIN(RaffleTest)

#include "tst_raffletest.moc"
