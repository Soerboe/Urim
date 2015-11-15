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

#include "drawingsetupcontroller.h"
#include "singlenumberconfiguration.h"
#include "colorandnumberconfiguration.h"
#include "lotteryticketbookconfiguration.h"

using namespace std;

DrawingSetupController::DrawingSetupController()
{
    initDefaultDrawingConfigurations();
}

DrawingSetupController::~DrawingSetupController()
{
}

void DrawingSetupController::initDefaultDrawingConfigurations()
{
    _drawingConfigurations.append(shared_ptr<DrawingConfiguration> (new SingleNumberConfiguration()));
    _drawingConfigurations.append(shared_ptr<DrawingConfiguration> (new ColorAndNumberConfiguration()));
    _drawingConfigurations.append(shared_ptr<DrawingConfiguration> (new LotteryTicketBookConfiguration()));
}
