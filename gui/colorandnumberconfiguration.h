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

#ifndef COLORANDNUMBERCONFIGURATION_H
#define COLORANDNUMBERCONFIGURATION_H

#include <QObject>
#include "drawingconfiguration.h"
#include "color.h"

#define DEFAULT_MIN 1
#define DEFAULT_MAX 1000

class ColorAndNumberConfiguration : public DrawingConfiguration
{
    Q_OBJECT

public:
    ColorAndNumberConfiguration();

    std::shared_ptr<DrawingSession> createDrawingSession();
    LotView* createView();
    bool isValid();
    WizardBase* wizard();
    virtual QString summary();

    int min() {return _min;}
    int max() {return _max;}
    QString numberLabel() {return _numberLabel;}
    std::vector<Color> colors() {return _colors;}
    QString colorLabel() {return _colorLabel;}
    int viewIndex() {return _viewIndex;}

    void setMin(int min) {_min = min;}
    void setMax(int max) {_max = max;}
    void setNumberLabel(const QString& l) {_numberLabel = l;}
    void setColors(std::vector<Color> colors) {_colors = colors;}
    void setColorLabel(const QString& l) {_colorLabel = l;}
    void setViewIndex(int i) {_viewIndex = i;}

private:
    int _min, _max;
    QString _numberLabel;
    QString _colorLabel;
    std::vector<Color> _colors;
    int _viewIndex;

    void initColors();
    QString colorsToString();
};

#endif // COLORANDNUMBERCONFIGURATION_H
