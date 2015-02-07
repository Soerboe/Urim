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

#include "testrunner.h"
#include <QtTest>
#include "singlenumberconfiguration.h"
#include "drawingsession.h"
#include "lotviewer.h"

class SingleNumberConfigurationTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldCreateSameNumberOfViewsAndGenerators();
};

void SingleNumberConfigurationTest::shouldCreateSameNumberOfViewsAndGenerators()
{
    SingleNumberConfiguration singleNumberConfiguration;
    std::shared_ptr<DrawingSession> session = singleNumberConfiguration.createDrawingSession();
    std::shared_ptr<LotViewer> viewer = singleNumberConfiguration.createViewer();
    QVERIFY(session->generatorsCount() == viewer->countViews());
}

REGISTER_TEST(SingleNumberConfigurationTest)

#include "tst_singlenumberconfiguration.moc"
