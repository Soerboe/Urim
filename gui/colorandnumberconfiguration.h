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

#include "drawingconfiguration.h"
#include "color.h"

#define DEFAULT_MIN 1
#define DEFAULT_MAX 1000

class ColorAndNumberConfiguration : public DrawingConfiguration
{
public:
    ColorAndNumberConfiguration();
    ~ColorAndNumberConfiguration();

    std::shared_ptr<DrawingSession> createDrawingSession();
    virtual std::shared_ptr<LotViewer> createViewer();
    void configure();

private:
    int _min, _max;
    std::vector<Color> _colors;

    void initColors();
};

#endif // COLORANDNUMBERCONFIGURATION_H
