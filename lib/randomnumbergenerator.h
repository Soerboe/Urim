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

#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <random>
#include <limits>
#include "randomgenerator.h"

class RandomNumberGenerator : public RandomGenerator
{
public:
    RandomNumberGenerator(int min = 0, int max = std::numeric_limits<int>::max());

    virtual std::shared_ptr<Lot> operator ()();
    virtual unsigned long numberOfUniqueResults();

private:
    std::default_random_engine _rng;
    std::uniform_int_distribution<int> _dist;
};

#endif // RANDOMNUMBERGENERATOR_H
