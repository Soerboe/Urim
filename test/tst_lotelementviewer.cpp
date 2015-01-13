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
#include "lotelementviewer.h"
#include "numberlotelement.h"
#include "colorlotelement.h"
#include "utils.h"

using namespace std;

class DummyLotElementViewer : public LotElementViewer {
public:
    QStringList textView;

    void view(const NumberLotElement& numberLotElement, const int& id) {
        ignore_unused(numberLotElement, id);
        textView.append("NumberLotElement");
    }

    void view(const ColorLotElement& colorLotElement, const int& id) {
        ignore_unused(colorLotElement, id);
        textView.append("ColorLotElement");
    }
};

class LotElementViewerTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldCallCorrectViewer();
};

void LotElementViewerTest::shouldCallCorrectViewer()
{
    QList<shared_ptr<LotElement> > lotElements;
    lotElements.append(shared_ptr<LotElement>(new NumberLotElement(0)));
    lotElements.append(shared_ptr<LotElement>(new ColorLotElement(Color())));

    DummyLotElementViewer viewer;
    int id = 0;
    foreach(shared_ptr<LotElement> lotElement, lotElements) {
        lotElement->view(viewer, id++);
    }

    QVERIFY(viewer.textView.at(0) == "NumberLotElement");
    QVERIFY(viewer.textView.at(1) == "ColorLotElement");
}

REGISTER_TEST(LotElementViewerTest)

#include "tst_lotelementviewer.moc"

