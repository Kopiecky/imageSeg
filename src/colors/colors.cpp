#include "colors.hpp"

#include <cmath>

Colors::Colors() : r(0), g(0), b(0) {}

Colors::Colors(float r, float g, float b) : r(r), g(g), b(b) {}

Colors::~Colors() {}

Colors Colors::multiply(float value) const
{
    return Colors(r * value, g * value, b * value);
}

Colors Colors::multiply(const Colors& other) const
{
    return Colors(r * other.r, g * other.g, b * other.b);
}

Colors Colors::add(const Colors& other) const
{
    return Colors(r + other.r, g + other.g, b + other.b);
}

Colors Colors::divide(float value) const
{
    return Colors(r / value, g / value, b / value);
}

float Colors::distance(const Colors& other) const
{
    return (fabs(r - other.r) + fabs(g - other.g) + fabs(b - other.b));
}