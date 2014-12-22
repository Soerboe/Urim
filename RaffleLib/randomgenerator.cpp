#include "randomgenerator.h"
#include <time.h>

using namespace std;

random_device::result_type RandomGenerator::_seed = 0;

RandomGenerator::RandomGenerator()
{
}

void RandomGenerator::pickSeed()
{
    try {
        random_device rnd;
        _seed = rnd();
    } catch (exception& e) {
        _seed = time(NULL);
    }
}
