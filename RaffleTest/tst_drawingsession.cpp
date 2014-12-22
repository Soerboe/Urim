#include <QtTest>
#include "autotest.h"
#include "drawingsession.h"
#include "randomnumbergenerator.h"

using namespace std;

class DrawingSessionTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldStoreDrawings();
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

DECLARE_TEST(DrawingSessionTest)

#include "tst_drawingsession.moc"
