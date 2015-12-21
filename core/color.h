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

#ifndef COLOR_H
#define COLOR_H

#include <QString>
#include "utils.h"
#include <QMetaType>
#include <QCoreApplication>

class Color {
    Q_DECLARE_TR_FUNCTIONS(Color)

public:
    enum DefaultColor {
        WHITE,
        BLACK,
        GRAY,
        LIGHT_GRAY,
        DARK_GRAY,
        RED,
        LIGHT_RED,
        DARK_RED,
        GREEN,
        LIGHT_GREEN,
        DARK_GREEN,
        BLUE,
        LIGHT_BLUE,
        DARK_BLUE,
        YELLOW,
        LIGHT_YELLOW,
        DARK_YELLOW,
        PINK,
        LIGHT_PINK,
        DARK_PINK,
        PURPLE,
        LIGHT_PURPLE,
        DARK_PURPLE,
        ORANGE,
        LIGHT_ORANGE,
        DARK_ORANGE,
        BROWN,
        LIGHT_BROWN,
        DARK_BROWN,
        VIOLET,
        LIGHT_VIOLET,
        DARK_VIOLET,
        TURQUOISE,
    };

    Color ();

    Color (const DefaultColor color);

    Color(const Color& color);

    Color(const int red, const int green, const int blue, const QString name);

    int red() const;
    int green() const;
    int blue() const;
    QString name() const;

    bool isWhite();
    bool operator==(const Color& that);
    size_t hash () const;

    friend QDataStream& operator<<(QDataStream& out, const Color& c);
    friend QDataStream& operator>>(QDataStream& in, Color& c);

private:
    int _red, _green, _blue;
    QString _name;

    bool _isDefaultColor;
    DefaultColor _defaultColor;
    Color convertDefaultColor() const;
};

Q_DECLARE_METATYPE(Color)

QDataStream& operator<<(QDataStream& out, const Color& c);
QDataStream& operator>>(QDataStream& in, Color& c);

#endif // COLOR_H
