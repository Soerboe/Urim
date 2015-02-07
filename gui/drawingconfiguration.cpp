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

#include "drawingconfiguration.h"
#include "numberlotelementview.h"
#include "colorlotelementview.h"

DrawingConfiguration::DrawingConfiguration(const QString& name, QObject* parent)
    : QObject(parent),
      _uniqueResults(false),
      _name(name)
{

}

DrawingConfiguration::~DrawingConfiguration()
{
}

QString DrawingConfiguration::summary()
{
    QString s;
    s.append("<h1>" + _name + "</h1>");
    s.append(detailedSummary());
    s.append("<div>");
    s.append(tr("Unique results") + ": ");
    s.append(_uniqueResults ? tr("Yes") : tr("No"));
    s.append("</div>");
    return s;
}

NumberLotElementView* DrawingConfiguration::buildNumberLotElementView(int min, int max)
{
    NumberLotElementView* view = new NumberLotElementView();
    QString minText = QString::number(min);
    QString maxText = QString::number(max);
    view->setLongestResultText(minText.length() > maxText.length() ? minText : maxText);
    return view;
}

ColorLotElementView* DrawingConfiguration::buildColorLotElementView(std::vector<Color>& colors)
{
    ColorLotElementView* view = new ColorLotElementView();
    QString longestColorName;
    for (unsigned int i = 0; i < colors.size(); ++i) {
        QString colorName = colors.at(i).name;
        if (colorName.length() > longestColorName.length()) {
            longestColorName = colorName;
        }
    }

    view->setLongestResultText(longestColorName);

    return view;
}

