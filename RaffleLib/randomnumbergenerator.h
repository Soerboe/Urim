#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <random>
#include <limits>
#include "randomgenerator.h"
#include "numberlot.h"

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
