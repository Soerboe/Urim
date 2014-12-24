#include "randomcolorgenerator.h"

RandomColorGenerator::RandomColorGenerator(const std::vector<Color> colors)
    : RandomNumberGenerator(0, colors.size() - 1),
      _colors(colors)
{
}
