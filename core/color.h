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

struct Color {

    Color ()
        : red(0), green(0), blue(0), name("Default color"){}

    Color(const int red, const int green, const int blue, const QString name)
        : red(red),
          green(green),
          blue(blue),
          name(name)
    {}

    bool operator==(const Color& that) {
        return
                this->name == that.name &&
                this->red == that.red &&
                this->blue == that.blue &&
                this->green == that.green;
    }

    size_t hash () const {
        size_t seed = 0x297d5cb0;
        hash_combine_std(seed, red);
        hash_combine_std(seed, green);
        hash_combine_std(seed, blue);
        hash_combine_std(seed, name.toStdString());
        return seed;
    }

    int red, green, blue;
    QString name;
};

#endif // COLOR_H
