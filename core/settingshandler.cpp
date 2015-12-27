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

#define SETTING_COLORS "colors/lot_colors"
#define SETTING_LANGUAGE "language"
#define SETTING_AUTO_UPDATES_DISABLED "updates/disable_auto_updates"

QSettings* SettingsHandler::_settings = new QSettings;

void SettingsHandler::initialize(QString orgname, QString appname)
{
    if (_settings) {
        delete _settings;
    }

    _settings = new QSettings(orgname, appname);

    setDefaultValues();
}

void SettingsHandler::setDefaultValues()
{
    if (!has(SETTING_COLORS)) {
        resetToDefaultColors();
    }

    if (!has(SETTING_AUTO_UPDATES_DISABLED)) {
        setAutoUpdatesDisabled(false);
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
    QList<Color> defaultColors;

    defaultColors.append(Color(Color::WHITE));
    defaultColors.append(Color(Color::BLACK));
    defaultColors.append(Color(Color::GRAY));
    defaultColors.append(Color(Color::LIGHT_GRAY));
    defaultColors.append(Color(Color::DARK_GRAY));
    defaultColors.append(Color(Color::RED));
    defaultColors.append(Color(Color::LIGHT_RED));
    defaultColors.append(Color(Color::DARK_RED));
    defaultColors.append(Color(Color::GREEN));
    defaultColors.append(Color(Color::LIGHT_GREEN));
    defaultColors.append(Color(Color::DARK_GREEN));
    defaultColors.append(Color(Color::BLUE));
    defaultColors.append(Color(Color::LIGHT_BLUE));
    defaultColors.append(Color(Color::DARK_BLUE));
    defaultColors.append(Color(Color::YELLOW));
    defaultColors.append(Color(Color::LIGHT_YELLOW));
    defaultColors.append(Color(Color::DARK_YELLOW));
    defaultColors.append(Color(Color::PINK));
    defaultColors.append(Color(Color::LIGHT_PINK));
    defaultColors.append(Color(Color::DARK_PINK));
    defaultColors.append(Color(Color::PURPLE));
    defaultColors.append(Color(Color::LIGHT_PURPLE));
    defaultColors.append(Color(Color::DARK_PURPLE));
    defaultColors.append(Color(Color::ORANGE));
    defaultColors.append(Color(Color::LIGHT_ORANGE));
    defaultColors.append(Color(Color::DARK_ORANGE));
    defaultColors.append(Color(Color::BROWN));
    defaultColors.append(Color(Color::LIGHT_BROWN));
    defaultColors.append(Color(Color::DARK_BROWN));
    defaultColors.append(Color(Color::VIOLET));
    defaultColors.append(Color(Color::LIGHT_VIOLET));
    defaultColors.append(Color(Color::DARK_VIOLET));
    defaultColors.append(Color(Color::TURQUOISE));

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

bool SettingsHandler::has(const QString &key)
{
    return _settings->contains(key);
}
