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

#include <QString>
#include <QtTest>
#include <memory>
#include "testrunner.h"
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
    lots.append(shared_ptr<Lot>(new ColorLot(Color())));

    DummyLotViewer lotViewer;

    foreach(shared_ptr<Lot> lot, lots) {
        lot->view(lotViewer);
    }

    QVERIFY(lotViewer.textView.at(0) == "NumberLot");
    QVERIFY(lotViewer.textView.at(1) == "ColorLot");
}

REGISTER_TEST(LotViewerTest)

#include "tst_lotviewer.moc"

