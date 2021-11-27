#ifndef SRC_MATRIX
#define SRC_MATRIX

#include <vector>

class Matrix
{
private:
    size_t m_width;
    size_t m_height;

public:
    std::vector<std::vector<float>> values;

public:
    Matrix();
    Matrix(size_t width, size_t height);
    void print() const;
    void fill(float value);
};


#endif