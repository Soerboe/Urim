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

#include "singlenumberconfiguration.h"
#include "drawingsetupdialog.h"
#include "randomnumbergenerator.h"
#include "drawingsession.h"
#include "numberlotelementview.h"
#include "lotviewer.h"

using namespace std;

SingleNumberConfiguration::SingleNumberConfiguration()
    : DrawingConfiguration(DrawingSetupDialog::tr("Single number")),
      _min(DEFAULT_MIN),
      _max(DEFAULT_MAX)
{
}

SingleNumberConfiguration::~SingleNumberConfiguration()
{
}

shared_ptr<DrawingSession> SingleNumberConfiguration::createDrawingSession()
{
    shared_ptr<RandomNumberGenerator> generator(new RandomNumberGenerator(_min, _max));
    generator->setName(DrawingSetupDialog::tr("Number").toStdString());
    shared_ptr<DrawingSession> session(new DrawingSession());
    session->addGenerator(generator);
    return session;
}

shared_ptr<LotViewer> SingleNumberConfiguration::createViewer()
{
    shared_ptr<LotViewer> viewer(new LotViewer);
    NumberLotElementView* view = new NumberLotElementView();
    viewer->addView(view);
    return viewer;
}

void SingleNumberConfiguration::configure()
{
    // TODO
}
