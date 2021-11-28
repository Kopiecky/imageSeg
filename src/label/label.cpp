#include "label/label.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

Label::Label() : m_height(0), m_width(0) {};

Label::Label(size_t width, size_t height) :
    m_width(width), m_height(height), labels(width * height) {};

Label::~Label() {};

void Label::calculate(const std::vector<Colors>& RGB)
{
    std::vector<bool> matches(1);
    std::vector<Colors> colors(1);
    std::vector<Matches> match_vec(1);

    matches.push_back(false);

    Colors start_color(RGB[0].r, RGB[0].g, RGB[0].b);
    colors.push_back(start_color);

    Matches start_match(false, false, false);
    match_vec.push_back(start_match);

    for (size_t i = 0; i < m_width * m_height; ++i)
    {
        Colors color(RGB[i].r, RGB[i].g, RGB[i].b);

        for (size_t j = 0; j < colors.size(); ++j)
        {
            if (j >= match_vec.size())
            {
                Matches match(false, false, false);
                match_vec.push_back(match);
            }
            match_vec[j] = isMember(colors[j], color);
        }

        for (size_t j = 0; j < match_vec.size(); ++j)
        {
            if (j >= matches.size())
            {
                matches.push_back(false);
            }
            matches[j] = match_vec[j].r * match_vec[j].g * match_vec[j].b;
        }
        size_t l = findTrue(matches);
        if (l)
        {
            labels[i] = static_cast<float>(l);
        }
        else
        {
            colors.push_back(color);
            labels[i] = static_cast<float>(colors.size());
        }
    }
    std::cout << colors.size() << std::endl;
}

Matches Label::isMember(const Colors& c1, const Colors& c2) const
{
    Matches match(false, false, false);

    if (c1.r == c2.r)
    {
        match.r = true;
    }
    if (c1.g == c2.g)
    {
        match.g = true;
    }
    if (c1.b == c2.b)
    {
        match.b = true;
    }
    return match;
}

size_t Label::findTrue(const std::vector<bool>& array) const
{
    size_t ret = 0;
    for (size_t i = 0; i < array.size(); ++i)
    {
        if (array[i] == 1)
        {
            ret = i;
            break;
        }
    }
    return ret;
}

void Label::print() const
{
    for (size_t i = 0; i < m_width * m_height; ++i)
    {
        std::cout << labels[i] << std::endl;
    }
}

void Label::save(const char* path) const
{
    std::ofstream fout;
    fout.open(path);
    if (fout)
    {
        for (size_t i = 0; i < m_height * m_width; ++i)
        {
            if (i == 512)
                fout << std::endl;
            else
                fout << labels[i] << ", ";
        }
    }
}