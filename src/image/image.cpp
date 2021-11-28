#include "image.hpp"

#include <fstream>
#include <iostream>

Image::Image() : m_width(0), m_height(0) {}

Image::Image(size_t width, size_t height)
{
    m_width  = width;
    m_height = height;
    std::vector<Colors>(width * height);
}

Image::~Image() {}

std::vector<Colors> Image::getColors() const
{
    return m_colors;
}

void Image::parseColors(const std::vector<Colors>& colors)
{
    for (size_t i = 0; i < m_colors.size(); ++i)
    {
        m_colors[i].r = colors[i].r;
        m_colors[i].g = colors[i].g;
        m_colors[i].b = colors[i].b;
    }
}

void Image::read(const char* path)
{
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open())
    {
        std::cout << "Error opening file\n";
    }

    unsigned char fileHeader[IMAGE_FILE_HEADER_SIZE];
    f.read(reinterpret_cast<char*>(fileHeader), IMAGE_FILE_HEADER_SIZE);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
    {
        std::cout << "Specified file isn't a bmp image\n";
        f.close();
        return;
    }
    unsigned char informationHeader[IMAGE_INFORMATION_HEADER_SIZE];
    f.read(reinterpret_cast<char*>(informationHeader), IMAGE_INFORMATION_HEADER_SIZE);

    int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16)
                   + (fileHeader[5] << 24);

    m_width = informationHeader[4] + (informationHeader[5] << 8)
              + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    m_height = informationHeader[8] + (informationHeader[9] << 8)
               + (informationHeader[10] << 16) + (informationHeader[11] << 24);

    m_colors.resize(m_width * m_height);

    const int padding = bitPadding(m_width);

    for (size_t y = 0; y < m_height; ++y)
    {
        for (size_t x = 0; x < m_width; ++x)
        {
            unsigned char color[3] = {0};
            f.read(reinterpret_cast<char*>(color), 3);

            m_colors[y * m_width + x].r = static_cast<float>(color[2]) / 255.0f;
            m_colors[y * m_width + x].g = static_cast<float>(color[1]) / 255.0f;
            m_colors[y * m_width + x].b = static_cast<float>(color[0]) / 255.0f;
        }
        f.ignore(padding);
    }

    f.close();
    std::cout << "File read\n";
}

void Image::save(const char* path)
{
    std::ofstream f;

    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open())
    {
        std::cout << "Error opening file\n";
    }

    unsigned char bmpPadding[3] = {0, 0, 0};

    const int padding  = ((4 - (m_width * 3) % 4) % 4);
    const int fileSize = IMAGE_FILE_HEADER_SIZE + IMAGE_INFORMATION_HEADER_SIZE
                         + m_width * m_height * 3 + padding * m_width;

    unsigned char fileHeader[IMAGE_FILE_HEADER_SIZE];

    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    bitShifts(2, fileSize, fileHeader);

    for (size_t i = 6; i < 14; ++i)
    {
        fileHeader[i] = 0;
    }

    unsigned char informationHeader[IMAGE_INFORMATION_HEADER_SIZE];

    informationHeader[0] = IMAGE_INFORMATION_HEADER_SIZE;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;


    bitShifts(4, m_width, informationHeader);
    bitShifts(8, m_height, informationHeader);

    informationHeader[12] = 1;
    informationHeader[13] = 0;

    informationHeader[14] = 24;
    informationHeader[15] = 0;

    for (size_t i = 16; i < 40; ++i)
    {
        informationHeader[i] = 0;
    }

    f.write(reinterpret_cast<char*>(fileHeader), IMAGE_FILE_HEADER_SIZE);
    f.write(reinterpret_cast<char*>(informationHeader), IMAGE_INFORMATION_HEADER_SIZE);

    for (size_t y = 0; y < m_height; ++y)
    {
        for (size_t x = 0; x < m_width; ++x)
        {
            unsigned char r = static_cast<unsigned char>(getColor(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(getColor(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(getColor(x, y).b * 255.0f);

            unsigned char color[] = {b, g, r};
            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmpPadding), padding);
    }
    f.close();
    std::cout << "File saved\n";
}

size_t Image::width() const
{
    return m_width;
}

size_t Image::hight() const
{
    return m_height;
}

inline Colors Image::getColor(int x, int y) const
{
    return m_colors[y * m_width + x];
}

inline int Image::bitPadding(int value) const
{
    return ((4 - (value * 3) % 4) % 4);
}

inline void Image::bitShifts(size_t start, int value, unsigned char* array) const
{
    array[start]     = value;
    array[start + 1] = value >> 8;
    array[start + 2] = value >> 16;
    array[start + 3] = value >> 24;
}