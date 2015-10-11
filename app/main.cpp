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
#include <QLibraryInfo>
#include <QTranslator>

int main(int argc, char *argv[])
{
    RandomGenerator::init();

    QApplication app(argc, argv);
    app.setApplicationName(APPLICATION_NAME);
    app.setApplicationDisplayName(APPLICATION_NAME);
    app.setApplicationVersion(APPLICATION_VERSION);

    QTranslator translator;
    translator.load("gui_no.qm", ":/gui/translations");
    app.installTranslator(&translator);

    DrawingSetupController setupController;
    DrawingSetupDialog setupDialog(&setupController);
    DrawingController controller;
    DrawingView drawingView(&controller, &setupDialog);
    controller.setDrawingView(&drawingView);
    return app.exec();
}
