#include <QtTest>
#include "testrunner.h"
#include "drawingsession.h"
#include "randomnumbergenerator.h"

using namespace std;

class Benchmarking : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void benchmarkUniqueResultsFromDrawingSession();
    void benchmarkUniqueResultsFromDrawingSession_data();
};

void Benchmarking::benchmarkUniqueResultsFromDrawingSession()
{
    QFETCH(int, uniqueResults);
    QFETCH(int, iterations);

    DrawingSession session(true);
    session.addGenerator(shared_ptr<RandomGenerator>(new RandomNumberGenerator(1, uniqueResults)));

    QBENCHMARK {
        for (int i = 0; i < iterations; i++) {
            session.draw();
        }
    }
}

void Benchmarking::benchmarkUniqueResultsFromDrawingSession_data()
{
    QTest::addColumn<int> ("iterations");
    QTest::addColumn<int> ("uniqueResults");

    QTest::newRow("get 90 % of 1 000 unique results") << 900 << 1000;
    QTest::newRow("get all 1 000 unique results") << 1000 << 1000;

    QTest::newRow("get 10 % of 100 000 unique results") << 10000 << 100000;
}

//REGISTER_SINGLE_TEST(Benchmarking)

#include "benchmarking.moc"
