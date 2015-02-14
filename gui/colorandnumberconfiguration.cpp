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

#include "colorandnumberconfiguration.h"
#include "randomnumbergenerator.h"
#include "randomcolorgenerator.h"
#include "drawingsession.h"
#include "colorandnumberview_pog.h"
#include "colorandnumberview_border.h"

using namespace std;

ColorAndNumberConfiguration::ColorAndNumberConfiguration(QObject* parent)
    : DrawingConfiguration(tr("Color and number"), parent),
      _min(DEFAULT_MIN),
      _max(DEFAULT_MAX)
{
    initColors();
}

ColorAndNumberConfiguration::~ColorAndNumberConfiguration()
{
}

shared_ptr<DrawingSession> ColorAndNumberConfiguration::createDrawingSession()
{
    shared_ptr<DrawingSession> session(new DrawingSession());
    shared_ptr<RandomColorGenerator> colorGenerator(new RandomColorGenerator(_colors));
    colorGenerator->setName(tr("Color").toStdString());
    shared_ptr<RandomNumberGenerator> numberGenerator(new RandomNumberGenerator(_min, _max));
    numberGenerator->setName(tr("Number").toStdString());
    session->addGenerator(colorGenerator);
    session->addGenerator(numberGenerator);
    return session;
}

LotView* ColorAndNumberConfiguration::createView()
{
    // TODO choose between: return new ColorAndNumberView_Border();
    QString minText = QString::number(_min);
    QString maxText = QString::number(_max);
    return new ColorAndNumberView_POG(minText.length() > maxText.length() ? minText : maxText);
}

void ColorAndNumberConfiguration::configure()
{
    // TODO
}

bool ColorAndNumberConfiguration::isValid()
{
    return _min <= _max && _colors.size() > 0;
}

QString ColorAndNumberConfiguration::detailedSummary()
{
    return QString();
}

void ColorAndNumberConfiguration::initColors()
{
    _colors.push_back(Color(255, 0, 0, tr("Red")));
    _colors.push_back(Color(0, 153, 0, tr("Green")));
    _colors.push_back(Color(0, 0, 255, tr("Blue")));
    _colors.push_back(Color(255, 255, 0, tr("Yellow")));
}

