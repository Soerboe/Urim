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

#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QString>
#include <QVariant>

class QSettings;

#define SETTING_COLORS "colors"
#define SETTING_LANGUAGE "language"
#define SETTING_DISABLE_AUTO_UPDATES "updates/disable_auto"

class SettingsHandler
{
public:
    static void initialize(QString orgname, QString appname);

    static void setValue(const QString& key, const QVariant& value);
    static QVariant value(const QString& key);
    static QVariant getValueSetIfNot(const QString& key, const QVariant& newValueIfNot);
    static void removeValue(const QString& key);
    static bool has(const QString& key);

private:
    static QSettings* _settings;
};

#endif // SETTINGSHANDLER_H

