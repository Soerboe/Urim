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

#ifndef RANDOMCOLORGENERATOR_H
#define RANDOMCOLORGENERATOR_H

#include <vector>
#include "randomnumbergenerator.h"
#include "color.h"

class RandomColorGenerator : public RandomNumberGenerator
{
public:
    RandomColorGenerator(const std::vector<Color> colors);

    virtual std::shared_ptr<LotElement> operator ()();

private:
    std::vector<Color> _colors;
};

#endif // RANDOMCOLORGENERATOR_H
