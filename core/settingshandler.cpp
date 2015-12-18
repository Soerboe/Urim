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

QSettings* SettingsHandler::_settings = new QSettings;

void SettingsHandler::initialize(QString orgname, QString appname)
{
    if (_settings) {
        delete _settings;
    }

    _settings = new QSettings(orgname, appname);
}

void SettingsHandler::setValue(const QString &key, const QVariant &value)
{
    _settings->setValue(key, value);
}

QVariant SettingsHandler::value(const QString &key)
{
    return _settings->value(key);
}

QVariant SettingsHandler::getValueSetIfNot(const QString &key, const QVariant &newValueIfNot)
{
    if (!has(key)) {
        setValue(key, newValueIfNot);
    }

    return value(key);
}

void SettingsHandler::removeValue(const QString &key)
{
    _settings->remove(key);
}

bool SettingsHandler::has(const QString &key)
{
    QString s = _settings->applicationName();
    QString d = _settings->organizationName();
    return _settings->contains(key);
}
