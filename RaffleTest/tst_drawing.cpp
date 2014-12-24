#include <QtTest>
#include "autotest.h"
#include "drawing.h"
#include "numberlot.h"

using namespace std;

class DrawingTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldCompareEqual();
};

void DrawingTest::shouldCompareEqual()
{
    Drawing drawing1;
    drawing1.addLot(shared_ptr<NumberLot> (new NumberLot(1337)));

    Drawing drawing2;
    drawing2.addLot(shared_ptr<NumberLot> (new NumberLot(1337)));

    QVERIFY(drawing1 == drawing2);
}

DECLARE_TEST(DrawingTest)

#include "tst_drawing.moc"


