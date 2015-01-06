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

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <memory>
#include <random>

class Lot;

class RandomGenerator
{
public:
    RandomGenerator();

    virtual std::shared_ptr<Lot> operator ()() = 0;
    virtual unsigned long numberOfUniqueResults() = 0;

    static std::random_device::result_type seed() {return _seed;}
    static void pickSeed();

protected:
    static std::random_device::result_type _seed;
};

#endif // RANDOMGENERATOR_H
