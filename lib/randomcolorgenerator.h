#ifndef RANDOMCOLORGENERATOR_H
#define RANDOMCOLORGENERATOR_H

#include <vector>
#include "randomnumbergenerator.h"
#include "color.h"

class RandomColorGenerator : public RandomNumberGenerator
{
public:
    RandomColorGenerator(const std::vector<Color> colors);

private:
    std::vector<Color> _colors;
};

#endif // RANDOMCOLORGENERATOR_H
