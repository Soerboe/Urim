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

#ifndef DRAWINGSETUPCONTROLLER_H
#define DRAWINGSETUPCONTROLLER_H

#include <QList>
#include <memory>
#include "drawingconfiguration.h"

class DrawingSetupController
{
public:
    DrawingSetupController();

    std::shared_ptr<DrawingConfiguration> at(int index) const {return _drawingConfigurations.at(index);}
    int countConfigurations() {return _drawingConfigurations.count();}

private:
    QList<std::shared_ptr<DrawingConfiguration> > _drawingConfigurations;

    void initDefaultDrawingConfigurations();
};

#endif // DRAWINGSETUPCONTROLLER_H
