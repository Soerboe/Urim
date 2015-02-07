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
#include "configuresinglenumberdialog.h"

using namespace std;

SingleNumberConfiguration::SingleNumberConfiguration(QObject* parent)
    : DrawingConfiguration(tr("Single number"), parent),
      _min(DEFAULT_MIN),
      _max(DEFAULT_MAX),
      _label(tr("Number"))
{
}

SingleNumberConfiguration::~SingleNumberConfiguration()
{
}

shared_ptr<DrawingSession> SingleNumberConfiguration::createDrawingSession()
{
    shared_ptr<RandomNumberGenerator> generator(new RandomNumberGenerator(_min, _max));
    generator->setName(_label.toStdString());
    shared_ptr<DrawingSession> session(new DrawingSession(_uniqueResults));
    session->addGenerator(generator);
    return session;
}

shared_ptr<LotViewer> SingleNumberConfiguration::createViewer()
{
    shared_ptr<LotViewer> viewer(new LotViewer);
    NumberLotElementView* view = buildNumberLotElementView(_min, _max);
    viewer->addView(view);
    return viewer;
}

void SingleNumberConfiguration::configure()
{
    ConfigureSingleNumberDialog dialog(name());
    dialog.init(_min, _max, _label, _uniqueResults);
    int retval = dialog.exec();

    if (retval == QDialog::Accepted) {
        _min = dialog.min();
        _max = dialog.max();
        _label = dialog.label();
        _uniqueResults = dialog.uniqueResults();
    }
}

bool SingleNumberConfiguration::isValid()
{
    return _min <= _max;
}

QString SingleNumberConfiguration::detailedSummary()
{
    QString s;
    s.append("<h3>");
    s.append(tr("Draw a singel number"));
    s.append("</h3>");
    s.append("<div>");
    s.append(tr("Minimum number") + ": " + QString::number(_min));
    s.append("</div><div>");
    s.append(tr("Maximum number") + ": " + QString::number(_max));
    s.append("</div><div>");
    s.append(tr("Label") + ": " + _label);
    s.append("</div>");
    return s;
}
