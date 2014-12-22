#include "randomnumbergenerator.h"

using namespace std;

RandomNumberGenerator::RandomNumberGenerator(int min, int max)
    : _rng(_seed),
      _dist(min, max)
{
}

shared_ptr<Lot> RandomNumberGenerator::generate()
{
    return shared_ptr<Lot>(new NumberLot(_dist(_rng)));
}
