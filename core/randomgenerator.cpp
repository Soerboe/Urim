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
#include "lotelement.h"
#include <qdebug.h>
#include <chrono>

using namespace std;

mt19937 RandomGenerator::_rng;

RandomGenerator::RandomGenerator()
{
}

RandomGenerator::~RandomGenerator()
{
}

shared_ptr<LotElement> RandomGenerator::operator ()()
{
    shared_ptr<LotElement> lotElement = generate();
    lotElement->setName(_name);
    return lotElement;
}

void RandomGenerator::init()
{
//    random_device on under gcc on Windows is not working
//    try {
//        random_device rnd;
//        seed = rnd();
//    } catch (exception& e) {
//    }

    auto now = chrono::high_resolution_clock::now();
    auto seed = chrono::time_point_cast<chrono::nanoseconds>(now).time_since_epoch().count();

    qDebug() << "Seed for RNG:" << seed << "\n";

    _rng = mt19937(seed);
}
