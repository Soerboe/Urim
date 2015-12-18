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
#include "app.h"
#include <QLibraryInfo>
#include <QTranslator>
#include "color.h"
#include "settingshandler.h"
#include "selectlanguagedialog.h"
#include "updatereminder.h"
#include "updateview.h"


int main(int argc, char *argv[])
{
    RandomGenerator::init();

    qRegisterMetaTypeStreamOperators<Color>("Color");

    QApplication app(argc, argv);
    app.setApplicationName(APPLICATION_NAME);
    app.setApplicationDisplayName(APPLICATION_NAME);
    app.setApplicationVersion(APPLICATION_VERSION);
    app.setOrganizationName(ORG_NAME);
    app.setOrganizationDomain(ORG_DOMAIN);
    QIcon icon(":/gui/icons/lots.svg");
    app.setWindowIcon(icon);

    SettingsHandler::initialize(ORG_NAME, APPLICATION_NAME);

    if (!SettingsHandler::has(SETTING_LANGUAGE)) {
        SelectLanguageDialog dialog;
        if (dialog.exec() == QDialog::Rejected) {
            return -1;
        }
    }

    QString language = SettingsHandler::value(SETTING_LANGUAGE).toString();
    QTranslator translator;
    if (language != "en") {
        QString filename = QString(language).append(".qm");
        translator.load(filename, ":/app/translations");
        app.installTranslator(&translator);
    }

    UpdateView updateView;
    UpdateReminder reminder([&](UpdateInfo info) {
        if (!info.hasError && info.hasUpdate) {
            updateView.setUpdateInfo(info);
            updateView.show();
        }
    });
    bool disableAutoUpdates = SettingsHandler::getValueSetIfNot(SETTING_DISABLE_AUTO_UPDATES, false).toBool();
    if (!disableAutoUpdates) {
        reminder.checkForUpdate();
    }

    DrawingSetupController setupController;
    DrawingSetupDialog setupDialog(&setupController);
    DrawingController controller;
    DrawingView drawingView(&controller, &setupDialog);
    controller.setDrawingView(&drawingView);
    return app.exec();
}
