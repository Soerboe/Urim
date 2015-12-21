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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settingshandler.h"
#include "i18n.h"
#include <QDesktopWidget>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->saveButton, SIGNAL(clicked()), SLOT(saveClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(reject()));

    ui->tabWidget->setCurrentIndex(0);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    initialize();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::saveClicked()
{
    /* LANGUAGE */
    QString lang = ui->languageSelector->currentData().toString();
    SettingsHandler::setLanguage(lang);

    /* UPDATES */
    SettingsHandler::setAutoUpdatesDisabled(ui->disableAutoUpdates->isChecked());

    accept();
}

void SettingsDialog::initialize()
{
    /* LANGUAGE */
    QString currentLang = SettingsHandler::language();
    for (int i = 0; i < NUM_LANGUAGES; ++i) {
        const char** language = LANGUAGES[i];
        QString langCode(language[1]);
        ui->languageSelector->addItem(language[0], langCode);
        if (currentLang == langCode) {
            ui->languageSelector->setCurrentIndex(i);
        }
    }

    /* UPDATES */
    bool autoUpdatesDisabled = SettingsHandler::autoUpdatesDisabled();
    ui->disableAutoUpdates->setChecked(autoUpdatesDisabled);
}
