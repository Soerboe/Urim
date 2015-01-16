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

class LotElement;

class RandomGenerator
{
public:
    RandomGenerator();
    virtual ~RandomGenerator();

    std::shared_ptr<LotElement> operator ()();
    virtual unsigned long numberOfUniqueResults() const = 0;
    virtual std::shared_ptr<LotElement> generate() = 0;

    static void init();

    std::string name() const {return _name;}
    void setName(const std::string& name) {_name = name;}

protected:
    static std::default_random_engine _rng;

private:
    std::string _name;
};

#endif // RANDOMGENERATOR_H
