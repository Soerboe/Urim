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
#include "drawingsession.h"
#include "randomnumbergenerator.h"
#include "randomcolorgenerator.h"
#include "nomoreuniqueresultsexception.h"
#include "numberlotelement.h"

using namespace std;

class GeneratorStub : public RandomGenerator
{
public:
    GeneratorStub(const vector<int> results, unsigned long numberOfUniqueResults)
        : _index(0),
          _results(results),
          _numberOfUniqueResults(numberOfUniqueResults)
    {}

    virtual shared_ptr<LotElement> operator ()() {
        int result = _results.at(_index);
        _index = _index >= _results.size() -1 ? 0 : _index + 1;
        return shared_ptr<LotElement>(new NumberLotElement(result));
    }

    virtual unsigned long numberOfUniqueResults() {return _numberOfUniqueResults;}

private:
    unsigned int _index;
    vector<int> _results;
    unsigned long _numberOfUniqueResults;
};

class DrawingSessionTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldStoreDrawings();
    void shouldGetUniqueResultsWithOneGenerator();
    void shouldReturnNumberOfUniqueResults();
    void shouldThrowExceptionWhenNoMoreUniqueResults();
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

void DrawingSessionTest::shouldGetUniqueResultsWithOneGenerator()
{
    vector<int> v = {1, 1, 2, 3};
    shared_ptr<GeneratorStub> numberGeneratorStub(new GeneratorStub(v, 3));

    DrawingSession session(true);
    session.addGenerator(numberGeneratorStub);

    for (int i = 0; i < 3; ++i) {
        session.draw();
    }

    QCOMPARE(session.drawings().size(), 3);
}
void DrawingSessionTest::shouldReturnNumberOfUniqueResults()
{
    shared_ptr<RandomGenerator> generator1(new RandomNumberGenerator(1, 2));
    vector<Color> colors = {Color(), Color(), Color()};
    shared_ptr<RandomGenerator> generator2(new RandomColorGenerator(colors));

    DrawingSession session;
    session.addGenerator(generator1);
    session.addGenerator(generator2);

    unsigned long EXPECTED = 6;
    QCOMPARE(session.numberOfUniqueResults(), EXPECTED);
}

void DrawingSessionTest::shouldThrowExceptionWhenNoMoreUniqueResults()
{
    vector<int> v = {1, 2};
    shared_ptr<GeneratorStub> numberGeneratorStub(new GeneratorStub(v, 2));

    vector<int> v2 = {100, 200, 300};
    shared_ptr<GeneratorStub> anotherNumberGeneratorStub(new GeneratorStub(v2, 3));

    DrawingSession session(true);
    session.addGenerator(numberGeneratorStub);
    session.addGenerator(anotherNumberGeneratorStub);

    try {
        for (int i = 0; i < 7; ++i) {
            session.draw();
        }

        QFAIL("Should have thrown NoMoreUniqueResultsException");

    } catch(NoMoreUniqueResultsException& e) {
    }
}

REGISTER_TEST(DrawingSessionTest)

#include "tst_drawingsession.moc"
