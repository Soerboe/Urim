#include <QString>
#include <QtTest>
#include <memory>
#include "autotest.h"
#include "lotviewer.h"
#include "numberlot.h"
#include "colorlot.h"

using namespace std;

class DummyLotViewer : public LotViewer {
public:
    QStringList textView;

    void view(const NumberLot* numberLot) {
        textView.append("NumberLot");
    }

    void view(const ColorLot* colorLot) {
        textView.append("ColorLot");
    }
};

class LotViewerTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldCallCorrectViewer();
};

void LotViewerTest::shouldCallCorrectViewer()
{
    QList<shared_ptr<Lot> > lots;
    lots.append(shared_ptr<Lot>(new NumberLot(0)));
    lots.append(shared_ptr<Lot>(new ColorLot));

    DummyLotViewer lotViewer;

    foreach(shared_ptr<Lot> lot, lots) {
        lot->view(lotViewer);
    }

    QVERIFY(lotViewer.textView.at(0) == "NumberLot");
    QVERIFY(lotViewer.textView.at(1) == "ColorLot");
}

DECLARE_TEST(LotViewerTest)

#include "tst_lotviewer.moc"

