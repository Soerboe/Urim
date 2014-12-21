#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <random>
#include "randomgenerator.h"
#include "numberlot.h"

class RandomNumberGenerator : public RandomGenerator
{
public:
    RandomNumberGenerator();

    virtual std::shared_ptr<Lot> generate();

//private:
    //std::default_random_engine _rng;
};

#endif // RANDOMNUMBERGENERATOR_H
