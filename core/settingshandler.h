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
#include <color.h>

class QSettings;

class SettingsHandler
{
public:
    static void initialize(QString orgname, QString appname);
    static void clear();

    static QList<Color> colors();
    static void setColors(QList<Color> colorList);
    static void resetToDefaultColors();

    static QString language();
    static bool hasLanguage();
    static void setLanguage(const QString& l);

    static bool autoUpdatesDisabled();
    static void setAutoUpdatesDisabled(bool a);

signals:
    //

private:
    static QSettings* _settings;
    static bool has(const QString& key);
};

#endif // SETTINGSHANDLER_H

