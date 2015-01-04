#include <QtTest>
#include "testrunner.h"
#include "drawingsession.h"
#include "randomnumbergenerator.h"

using namespace std;

class GeneratorStub : public RandomGenerator
{
public:
    GeneratorStub()
        : _index(0)
    {
    }

    virtual shared_ptr<Lot> operator ()() {
        int result = _results.at(_index);
        _index++;
        return shared_ptr<Lot>(new NumberLot(result));
    }

    void setResults(vector<int> results) {_results = results;}

private:
    vector<int> _results;
    int _index;
};

class DrawingSessionTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldStoreDrawings();
    void shouldGetUniqueResults();
};

void DrawingSessionTest::shouldStoreDrawings()
{
    DrawingSession session;
    session.addGenerator(shared_ptr<RandomGenerator>(new RandomNumberGenerator(0, 10000)));

    for (int i = 0; i < 10; i++) {
        session.draw();
    }

    QVERIFY(session.drawings().size() == 10);
}

void DrawingSessionTest::shouldGetUniqueResults()
{
    shared_ptr<GeneratorStub> numberGeneratorStub(new GeneratorStub);
    vector<int> v = {1, 1, 2, 3};
    numberGeneratorStub->setResults(v);

    DrawingSession session(true);
    session.addGenerator(numberGeneratorStub);

    for (int i = 0; i < 3; ++i) {
        session.draw();
    }

    QCOMPARE(session.drawings().size(), 3);
}

REGISTER_TEST(DrawingSessionTest)

#include "tst_drawingsession.moc"
