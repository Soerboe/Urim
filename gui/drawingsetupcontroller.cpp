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
#include "bingoconfiguration.h"

using namespace std;

DrawingSetupController::DrawingSetupController()
{
    initDefaultConfigurations();
}

void DrawingSetupController::initDefaultConfigurations()
{
    _configurations.append(shared_ptr<Configuration> (new SingleNumberConfiguration()));
    _configurations.append(shared_ptr<Configuration> (new ColorAndNumberConfiguration()));
    _configurations.append(shared_ptr<Configuration> (new LotteryTicketBookConfiguration()));
    _configurations.append(shared_ptr<Configuration> (new BingoConfiguration()));
}
