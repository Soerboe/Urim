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

#include "settingshandler.h"
#include <QSettings>
#include <QCoreApplication>
#include "colors.h"

#define INITIALIZED "initialized"
#define SETTING_COLORS "colors"
#define SETTING_LANGUAGE "language"
#define SETTING_AUTO_UPDATES_DISABLED "updates/disable_auto_updates"

QSettings* SettingsHandler::_settings = new QSettings;

void SettingsHandler::initialize(QString orgname, QString appname)
{
    if (_settings) {
        delete _settings;
    }

    _settings = new QSettings(orgname, appname);

    if (!_settings->contains(INITIALIZED) || _settings->value(INITIALIZED).toBool() == false) {
        setDefaultValues();
    }
}

void SettingsHandler::clear()
{
    _settings->clear();
}

QList<Color> SettingsHandler::colors()
{
    QList<Color> colors;

    foreach(QVariant v, _settings->value(SETTING_COLORS).toList()) {
        colors.append(v.value<Color>());
    }

    return colors;
}

void SettingsHandler::setColors(QList<Color> colorList)
{
    QList<QVariant> list;

    foreach(Color c, colorList) {
        QVariant v;
        v.setValue(c);
        list.append(v);
    }

    _settings->setValue(SETTING_COLORS, list);
}

void SettingsHandler::resetToDefaultColors()
{
    Colors colors;

    QList<Color> defaultColors;
    defaultColors.append(colors.red());
    defaultColors.append(colors.green());
    defaultColors.append(colors.blue());
    defaultColors.append(colors.yellow());
    defaultColors.append(colors.white());
    defaultColors.append(colors.black());
    defaultColors.append(colors.grey());
    defaultColors.append(colors.darkRed());
    defaultColors.append(colors.darkBlue());
    defaultColors.append(colors.darkGreen());
    defaultColors.append(colors.pink());
    defaultColors.append(colors.purple());
    defaultColors.append(colors.orange());
    defaultColors.append(colors.brown());
    defaultColors.append(colors.violet());
    defaultColors.append(colors.turquoise());
    defaultColors.append(colors.olive());
    defaultColors.append(colors.lightBrown());

    setColors(defaultColors);
}

QString SettingsHandler::language()
{
    return _settings->value(SETTING_LANGUAGE).toString();
}

bool SettingsHandler::hasLanguage()
{
    return _settings->contains(SETTING_LANGUAGE);
}

void SettingsHandler::setLanguage(const QString &l)
{
    _settings->setValue(SETTING_LANGUAGE, l);
}

bool SettingsHandler::autoUpdatesDisabled()
{
    return _settings->value(SETTING_AUTO_UPDATES_DISABLED).toBool();
}

void SettingsHandler::setAutoUpdatesDisabled(bool a)
{
    _settings->setValue(SETTING_AUTO_UPDATES_DISABLED, a);
}

void SettingsHandler::setDefaultValues()
{
    _settings->setValue(INITIALIZED, true);

    resetToDefaultColors();
    _settings->remove(SETTING_LANGUAGE);
    setAutoUpdatesDisabled(false);
}
