#ifndef SRC_COLORS
#define SRC_COLORS

class Colors
{
public:
    float r, g, b;

public:
    Colors();
    Colors(float r, float g, float b);

    Colors multiply(float value) const
    {
        return Colors(r * value, g * value, b * value);
    }

    Colors multiply(const Colors& other) const
    {
        return Colors(r * other.r, g * other.g, b * other.b);
    }

    Colors add(const Colors& other) const
    {
        return Colors(r + other.r, g + other.g, b + other.b);
    }

    Colors divide(float value) const
    {
        return Colors(r/value, g/value, b/value);
    }

    float distance(const Colors& other) const;

    ~Colors();
};

#endif