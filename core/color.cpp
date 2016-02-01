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
    : _red(0),
      _green(0),
      _blue(0),
      _name("No color"),
      _isDefaultColor(false)
{
}

Color::Color(const Color::DefaultColor color)
    : _red(0),
      _green(0),
      _blue(0),
      _name("Default color"),
      _isDefaultColor(true)
{
    _defaultColor = color;
}

Color::Color(const Color &color)
{
    this->_red = color.red();
    this->_green = color.green();
    this->_blue = color.blue();
    this->_name = color.name();
    this->_isDefaultColor = color._isDefaultColor;
    this->_defaultColor = color._defaultColor;
}

Color::Color(const int red, const int green, const int blue, const QString name)
    : _red(red),
      _green(green),
      _blue(blue),
      _name(name),
      _isDefaultColor(false)
{
}

int Color::red() const
{
    return (_isDefaultColor) ? convertDefaultColor()._red : _red;
}

int Color::green() const
{
    return (_isDefaultColor) ? convertDefaultColor()._green : _green;
}

int Color::blue() const
{
    return (_isDefaultColor) ? convertDefaultColor()._blue : _blue;
}

QString Color::name() const
{
    return (_isDefaultColor) ? convertDefaultColor()._name : _name;
}

bool Color::operator==(const Color &that)
{
    return
            this->name() == that.name() &&
            this->red() == that.red() &&
            this->blue() == that.blue() &&
            this->green() == that.green();
}

bool Color::isWhite()
{
    return red() == 255 && green() == 255 && blue() == 255;
}

size_t Color::hash() const
{
    size_t seed = 0x297d5cb0;
    hash_combine_std(seed, red());
    hash_combine_std(seed, green());
    hash_combine_std(seed, blue());
    hash_combine_std(seed, name().toStdString());
    return seed;
}

Color Color::convertDefaultColor() const
{
    switch (_defaultColor) {
    default:
    case BLACK:         return Color(0, 0, 0,       tr("Black"));
    case DARK_GRAY:     return Color(64, 64, 64,    tr("Dark gray"));
    case GRAY:          return Color(128, 128, 128, tr("Gray"));
    case LIGHT_GRAY:    return Color(208, 208, 208, tr("Light gray"));
    case WHITE:         return Color(255, 255, 255, tr("White"));
    case DARK_RED:      return Color(110, 0, 0,     tr("Dark red"));
    case RED:           return Color(220, 0, 0,     tr("Red"));
    case LIGHT_RED:     return Color(255, 102, 102, tr("Light red"));
    case DARK_GREEN:    return Color(0, 80, 0,      tr("Dark green"));
    case GREEN:         return Color(0, 200, 0,     tr("Green"));
    case LIGHT_GREEN:   return Color(128, 255, 128, tr("Light green"));
    case DARK_BLUE:     return Color(0, 0, 90,      tr("Dark blue"));
    case BLUE:          return Color(0, 0, 255,     tr("Blue"));
    case LIGHT_BLUE:    return Color(153, 153, 255, tr("Light blue"));
    case DARK_YELLOW:   return Color(175, 179, 0,   tr("Dark yellow"));
    case YELLOW:        return Color(255, 255, 40,  tr("Yellow"));
    case LIGHT_YELLOW:  return Color(254, 255, 153, tr("Light yellow"));
    case DARK_PINK:     return Color(179, 0, 57,    tr("Dark pink"));
    case PINK:          return Color(255, 62, 150,  tr("Pink"));
    case LIGHT_PINK:    return Color(255, 179, 204, tr("Light pink"));
    case DARK_PURPLE:   return Color(128, 0, 94,    tr("Dark purple"));
    case PURPLE:        return Color(128, 0, 128,   tr("Purple"));
    case LIGHT_PURPLE:  return Color(255, 128, 222, tr("Light purple"));
    case DARK_ORANGE:   return Color(204, 80, 0,    tr("Dark orange"));
    case ORANGE:        return Color(255, 102, 0,   tr("Orange"));
    case LIGHT_ORANGE:  return Color(255, 179, 128, tr("Light orange"));
    case DARK_BROWN:    return Color(102, 33, 0,    tr("Dark brown"));
    case BROWN:         return Color(138, 54, 15,   tr("Brown"));
    case LIGHT_BROWN:   return Color(210, 105, 30,  tr("Light brown"));
    case DARK_VIOLET:   return Color(179, 0, 130,   tr("Dark violet"));
    case VIOLET:        return Color(255, 26, 196,  tr("Violet"));
    case LIGHT_VIOLET:  return Color(255, 179, 235, tr("Light violet"));
    case TURQUOISE:     return Color(64, 224, 208,  tr("Turquiose"));
    }
}

QDataStream& operator<<(QDataStream& out, const Color& c) {
    out << c._red << c._green << c._blue << c._name << c._isDefaultColor << qint32(c._defaultColor);
    return out;
}

QDataStream& operator>>(QDataStream& in, Color& c) {
    in >> c._red;
    in >> c._green;
    in >> c._blue;
    in >> c._name;
    in >> c._isDefaultColor;
    quint32 dc;
    in >> dc;
    c._defaultColor = Color::DefaultColor(dc);
    return in;
}
