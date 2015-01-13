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

#include "randomgenerator.h"
#include <time.h>

using namespace std;

random_device::result_type RandomGenerator::_seed = 0;

RandomGenerator::RandomGenerator()
{
}

RandomGenerator::~RandomGenerator()
{
}

void RandomGenerator::pickSeed()
{
    try {
        random_device rnd;
        _seed = rnd();
    } catch (exception& e) {
        _seed = time(NULL);
    }
}
