#ifndef SRC_IMAGE
#define SRC_IMAGE

#include <vector>

#include "colors/colors.hpp"

class Image
{
    std::vector<Colors> m_colors;

    const size_t IMAGE_FILE_HEADER_SIZE        = 14;
    const size_t IMAGE_INFORMATION_HEADER_SIZE = 40;
    size_t m_width;
    size_t m_height;

private:
    Colors getColor(int x, int y) const;
    int bitPadding(int value) const;
    void bitShifts(size_t start, int value, unsigned char* array) const;

public:
    Image();
    Image(size_t width, size_t height);
    ~Image();

    void read(const char* path);
    void save(const char* path);
    std::vector<Colors> getColors() const;
    void parseColors(const std::vector<Colors>& colors);
    size_t width() const;
    size_t hight() const;
};

#endif