#ifndef SRC_COLORS
#define SRC_COLORS

class Colors
{
public:
    float r, g, b;

public:
    Colors();
    Colors(float r, float g, float b);
    Colors multiply(float value) const;
    Colors multiply(const Colors& other) const;
    Colors add(const Colors& other) const;
    Colors divide(float value) const;
    float distance(const Colors& other) const;
    bool isEqual(const Colors& other) const;
    ~Colors();
};

#endif