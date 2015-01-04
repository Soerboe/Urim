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
