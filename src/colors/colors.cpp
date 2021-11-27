#include "colors.hpp"
#include <cmath>

Colors::Colors() : r(0), g(0), b(0) {}

Colors::Colors(float r, float g, float b) : r(r), g(g), b(b) {}

Colors::~Colors() {}

float Colors::distance(const Colors& other) const
{
    return (fabs(r - other.r) + fabs(g - other.g) + fabs(b - other.b));
}