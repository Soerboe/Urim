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
#include "editcolorswidget.h"
#include "colorandnumberwizard.h"
#include "advancedcolorandnumberoptions.h"

using namespace std;

ColorAndNumberConfiguration::ColorAndNumberConfiguration()
    : DrawingConfiguration(tr("Color and number"), tr("Draw lots containing a color and a number"), QIcon(":/gui/icons/colorandnumberdrawing.svg"), true),
      _min(DEFAULT_MIN),
      _max(DEFAULT_MAX),
      _viewIndex(0)
{
    initColors();
}

shared_ptr<DrawingSession> ColorAndNumberConfiguration::createDrawingSession()
{
    shared_ptr<DrawingSession> session(new DrawingSession(_uniqueResults));
    shared_ptr<RandomColorGenerator> colorGenerator(new RandomColorGenerator(_colors));
    colorGenerator->setName(_colorLabel.toStdString());
    shared_ptr<RandomNumberGenerator> numberGenerator(new RandomNumberGenerator(_min, _max));
    numberGenerator->setName(_numberLabel.toStdString());
    session->addGenerator(colorGenerator);
    session->addGenerator(numberGenerator);
    return session;
}

LotView* ColorAndNumberConfiguration::createView()
{
    QString minText = QString::number(_min);
    QString maxText = QString::number(_max);
    QString longestText = minText.length() > maxText.length() ? minText : maxText;
    switch (_viewIndex) {
    case 1:
        return new ColorAndNumberView_Border(longestText);
    case 0:
    default:
        return new ColorAndNumberView_POG(longestText);
    }
}

bool ColorAndNumberConfiguration::isValid()
{
    return _min <= _max && _colors.size() > 0;
}

WizardBase *ColorAndNumberConfiguration::wizard()
{
    return new ColorAndNumberWizard(dynamic_pointer_cast<ColorAndNumberConfiguration> (shared_from_this()));
}

QString ColorAndNumberConfiguration::summary()
{
    QString s;
    s.append("<div>");
    s.append(tr("Colors") + ": " + colorsToString());
    s.append("</div><div>");
    if (!_colorLabel.isEmpty()) {
        s.append(tr("Color label") + ": " + _colorLabel);
        s.append("</div><div>");
    }
    s.append(tr("Minimum number") + ": " + QString::number(_min));
    s.append("</div><div>");
    s.append(tr("Maximum number") + ": " + QString::number(_max));
    if (!_numberLabel.isEmpty()) {
        s.append("</div><div>");
        s.append(tr("Number label") + ": " + _numberLabel);
    }
    s.append("</div>");
    s.append(uniqueResultsSummary());
    return s;
}

void ColorAndNumberConfiguration::initColors()
{
    _colors.push_back(Color(Color::RED));
    _colors.push_back(Color(Color::GREEN));
    _colors.push_back(Color(Color::BLUE));
    _colors.push_back(Color(Color::YELLOW));
}

QString ColorAndNumberConfiguration::colorsToString()
{
    QStringList s;
    for(Color color : _colors) {
        s.append(color.name());
    }

    return s.join(", ");
}

