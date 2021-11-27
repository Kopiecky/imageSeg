#include "matrix.hpp"
#include <iostream>

Matrix::Matrix() : m_width(0), m_height(0) {};

Matrix::Matrix(size_t width, size_t height) :
    m_width(width), m_height(height), values(width, std::vector<float>(height)) {}

void Matrix::print() const
{
    for (size_t i = 0; i < m_height; ++i)
    {
        for (size_t j = 0; j < m_width; ++j)
        {
            std::cout << values[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
}

void Matrix::fill(float value)
    {
        for (size_t i = 0; i < m_width; ++i)
        {
            for (size_t j = 0; j < m_height; ++j)
            {
                values[i][j] = value;
            }
        }
    };