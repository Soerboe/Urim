#include "randomnumbergenerator.h"

using namespace std;

RandomNumberGenerator::RandomNumberGenerator(int min, int max)
    : _rng(_seed),
      _dist(min, max)
{
}

std::shared_ptr<Lot> RandomNumberGenerator::operator ()()
{
    return shared_ptr<Lot>(new NumberLot(_dist(_rng)));
}

unsigned long RandomNumberGenerator::numberOfUniqueResults()
{
    return _dist.max() - _dist.min() + 1;
}
