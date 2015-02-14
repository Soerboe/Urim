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

#include "drawingview.h"
#include <QApplication>
#include "randomgenerator.h"
#include "drawingcontroller.h"
#include "drawingsetupcontroller.h"
#include "lotwindow.h"
#include "urimthummim.h"

int main(int argc, char *argv[])
{
    RandomGenerator::init();

    QApplication a(argc, argv);
    a.setApplicationName(APPLICATION_NAME);
    a.setApplicationDisplayName(APPLICATION_NAME);
    a.setApplicationVersion(APPLICATION_VERSION);
    DrawingSetupController setupController;
    DrawingSetupDialog setupDialog(&setupController);
    LotWindow lotWindow;
    DrawingController controller(&lotWindow);
    DrawingView drawingView(&controller, &setupDialog, &lotWindow);
    return a.exec();
}
