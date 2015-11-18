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

#include "color.h"
#include <QDataStream>

Color::Color()
    : red(0), green(0), blue(0), name("Default color")
{
}

Color::Color(const Color &color)
{
    this->name = color.name;
    this->red = color.red;
    this->green = color.green;
    this->blue = color.blue;
}

Color::Color(const int red, const int green, const int blue, const QString name)
    : red(red),
      green(green),
      blue(blue),
      name(name)
{
}

bool Color::operator==(const Color &that)
{
    return
            this->name == that.name &&
            this->red == that.red &&
            this->blue == that.blue &&
            this->green == that.green;
}

bool Color::isWhite()
{
    return red == 255 && green == 255 && blue == 255;
}

size_t Color::hash() const
{
    size_t seed = 0x297d5cb0;
    hash_combine_std(seed, red);
    hash_combine_std(seed, green);
    hash_combine_std(seed, blue);
    hash_combine_std(seed, name.toStdString());
    return seed;
}

QDataStream& operator<<(QDataStream& out, const Color& c) {
    out << c.red << c.green << c.blue << c.name;
    return out;
}

QDataStream& operator>>(QDataStream& in, Color& c) {
    in >> c.red;
    in >> c.green;
    in >> c.blue;
    in >> c.name;
    return in;
}
