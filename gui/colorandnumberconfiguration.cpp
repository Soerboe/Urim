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
#include "configurecolorandnumberdialog.h"
#include "configurecolorwidget.h"
#include "colors.h"

using namespace std;

ColorAndNumberConfiguration::ColorAndNumberConfiguration(QObject* parent)
    : DrawingConfiguration(tr("Color and number"), parent),
      _min(DEFAULT_MIN),
      _max(DEFAULT_MAX),
      _numberLabel(tr("Number")),
      _colorLabel(tr("Color"))
{
    initColors();
}

ColorAndNumberConfiguration::~ColorAndNumberConfiguration()
{
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
    switch (_viewIndex) {
    case 1:
        return new ColorAndNumberView_Border();
    case 0:
    default:
        return new ColorAndNumberView_POG(minText.length() > maxText.length() ? minText : maxText);

    }

}

void ColorAndNumberConfiguration::configure()
{
    ConfigureColorAndNumberDialog dialog(name());
    dialog.init(_colors, _colorLabel, _min, _max, _numberLabel, _uniqueResults, _viewIndex);
    int retval = dialog.exec();

    if (retval == QDialog::Accepted) {
        _colors = dialog.colors();
        _colorLabel = dialog.colorLabel();
        _min = dialog.min();
        _max = dialog.max();
        _numberLabel = dialog.numberLabel();
        _uniqueResults = dialog.uniqueResults();
        _viewIndex = dialog.viewIndex();
    }
}

bool ColorAndNumberConfiguration::isValid()
{
    return _min <= _max && _colors.size() > 0;
}

QString ColorAndNumberConfiguration::detailedSummary()
{
    QString s;
    s.append("<h3>");
    s.append(tr("Draw a color and a number"));
    s.append("</h3>");
    s.append("<div>");
    s.append(tr("Colors") + ": " + colorsToString());
    s.append("</div><div>");
    s.append(tr("Color label") + ": " + _colorLabel);
    s.append("</div><div>");
    s.append(tr("Minimum number") + ": " + QString::number(_min));
    s.append("</div><div>");
    s.append(tr("Maximum number") + ": " + QString::number(_max));
    s.append("</div><div>");
    s.append(tr("Number label") + ": " + _numberLabel);
    s.append("</div>");
    return s;
}

void ColorAndNumberConfiguration::initColors()
{
    Colors colors;
    _colors.push_back(colors.red());
    _colors.push_back(colors.green());
    _colors.push_back(colors.blue());
    _colors.push_back(colors.yellow());
}

QString ColorAndNumberConfiguration::colorsToString()
{
    QStringList s;
    for(Color color : _colors) {
        s.append(color.name);
    }

    return s.join(", ");
}

