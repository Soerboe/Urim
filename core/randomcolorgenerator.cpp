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

#include "randomcolorgenerator.h"
#include "colorlotelement.h"

using namespace std;

RandomColorGenerator::RandomColorGenerator(const vector<Color> colors)
    : RandomNumberGenerator(0, colors.size() - 1),
      _colors(colors)
{
}

shared_ptr<LotElement> RandomColorGenerator::generate()
{
    int index = doGenerate();
    return shared_ptr<ColorLotElement> (new ColorLotElement(_colors.at(index)));
}
