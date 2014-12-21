#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <memory>
#include "lot.h"

class RandomGenerator
{
public:
    RandomGenerator();

    virtual std::shared_ptr<Lot> generate() = 0;
};

#endif // RANDOMGENERATOR_H
