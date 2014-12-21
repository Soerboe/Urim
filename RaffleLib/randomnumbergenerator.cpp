#include "randomnumbergenerator.h"

using namespace std;

RandomNumberGenerator::RandomNumberGenerator()
{
}

shared_ptr<Lot> RandomNumberGenerator::generate()
{
    shared_ptr<Lot> lot(new NumberLot(0));
    return lot;
}
