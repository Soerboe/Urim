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
#include "singlenumberview.h"
#include "singlenumberwizard.h"

using namespace std;

SingleNumberConfiguration::SingleNumberConfiguration()
    : DrawingConfiguration(tr("Simple drawing"), tr("Draws a random number in the chosen number range"), QIcon(":/gui/icons/simpledrawing.svg"), true),
      _min(DEFAULT_MIN),
      _max(DEFAULT_MAX)
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

LotView* SingleNumberConfiguration::createView()
{
    QString minText = QString::number(_min);
    QString maxText = QString::number(_max);
    return new SingleNumberView(minText.length() > maxText.length() ? minText : maxText);
}

bool SingleNumberConfiguration::isValid()
{
    return _min <= _max;
}

WizardBase *SingleNumberConfiguration::wizard()
{
    return new SingleNumberWizard(dynamic_pointer_cast<SingleNumberConfiguration> (shared_from_this()));
}

QString SingleNumberConfiguration::summary()
{
    QString s;
    s.append("<div>");
    s.append(tr("Minimum number") + ": " + QString::number(_min));
    s.append("</div><div>");
    s.append(tr("Maximum number") + ": " + QString::number(_max));
    if (!_label.isEmpty()) {
        s.append("</div><div>");
        s.append(tr("Label") + ": " + _label);
    }
    s.append("</div>");
    s.append(uniqueResultsSummary());
    return s;
}
