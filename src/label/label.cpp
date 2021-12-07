#include "label/label.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

Label::Label() : m_height(0), m_width(0) {};

Label::Label(size_t width, size_t height) :
    m_width(width),
    m_height(height),
    labels(width * height),
    labelMatrix(width, height),
    visited(width, height),
    colors(1),
    area(1),
    colors_ex(1) {};

Label::~Label() {};

void Label::calculate(const std::vector<Colors>& RGB)
{
    std::vector<bool> matches(1);
    std::vector<Matches> match_vec(1);

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
            labels[i] = static_cast<float>(colors.size() - 1);
        }
        colors_ex.push_back(color);
    }
    makeLabelMatrix();
    std::cout << connectedComponents(m_width) << std::endl;
    print();
    invert();
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
    std::cout << "Colors: " << std::endl;
    for (size_t i = 0; i < colors.size(); ++i)
    {
        std::cout << i << ": " << std::setprecision(2) << std::fixed << colors[i].r
                  << ", " << colors[i].g << ", " << colors[i].b << std::endl;
    }
    std::cout << "Area: " << std::endl;
    for (size_t i = 0; i < area.size() - 1; ++i)
    {
        std::cout << i << ": " << area[i] << std::endl;
    }
}

void Label::makeLabelMatrix()
{
    Matrix temp(m_width, m_height);
    size_t k = 0;

    for (size_t i = 0; i < m_width; ++i)
    {
        for (size_t j = 0; j < m_height; ++j)
        {
            labelMatrix.values[i][j] = labels[k];
            k++;
        }
    }
}

void Label::invert()
{
    Matrix temp(m_width, m_height);
    size_t k = 0;

    for (size_t i = 0; i < m_width; ++i)
    {
        for (size_t j = 0; j < m_height; ++j)
        {
            temp.values[i][j] = labelMatrix.values[i][j];
            k++;
        }
    }

    for (size_t i = 0; i < m_width; ++i)
    {
        for (size_t j = 0; j < m_height; ++j)
        {
            labelMatrix.values[i][j] = temp.values[m_width - i - 1][j];
        }
    }
}

void Label::save(const char* path) const
{
    std::string p = path;
    std::ofstream fout;
    fout.open(p + "viz.txt");

    if (fout)
    {
        fout << "Wizualizacja macierzy kolorów\n";
        for (size_t i = 0; i < m_width; ++i)
        {
            for (size_t j = 0; j < m_height; ++j)
            {
                fout << labelMatrix.values[i][j] << ", ";
            }
            fout << std::endl;
        }
    }

    fout.close();

    std::ofstream colors_path;
    colors_path.open(p + "colors.txt");

    if (colors_path)
    {
        colors_path << "Kolory dla danych obszarów\n";
        for (size_t j = 0; j < colors.size(); ++j)
        {
            colors_path << j << ": " << std::setprecision(2) << std::fixed << colors[j].r
                        << ", " << colors[j].g << ", " << colors[j].b << std::endl;
        }
    }

    colors_path.close();

    std::ofstream area_path;
    area_path.open(p + "areas.txt");

    if (area_path)
    {
        area_path << "Pole danych obszarów\n";
        for (size_t j = 0; j < area.size() - 1; ++j)
        {
            area_path << j << ": " << area[j] << std::endl;
        }
    }

    area_path.close();
}

bool Label::isSafe(int row, int col, float c, int n, int l)
{
    return (row >= 0 && row < n) && (col >= 0 && col < l)
           && (labelMatrix.values[row][col] == c && !visited.values[row][col]);
}

void Label::DFS(int row, int col, float c, int n, int l)
{
    int rowNbr[] = {-1, 1, 0, 0};
    int colNbr[] = {0, 0, 1, -1};

    visited.values[row][col] = true;

    for (int k = 0; k < 4; ++k)
        if (isSafe(row + rowNbr[k], col + colNbr[k], c, n, l))
            DFS(row + rowNbr[k], col + colNbr[k], c, n, l);
}

int Label::connectedComponents(int n)
{
    int connectedComp = 0;
    int l             = m_height;
    int k             = 0;
    colors.clear();
    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            if (!visited.values[i][j])
            {
                float c = labelMatrix.values[i][j];
                DFS(i, j, c, n, l);
                area.push_back(1);
                colors.push_back(colors_ex[k + 1]);
                insertConnectedComponents(i, j, connectedComp);
                connectedComp++;
            }
            ++k;
        }
    }
    return connectedComp;
}

void Label::insertConnectedComponents(int i, int j, int component)
{
    float start     = labelMatrix.values[i][j];
    int iMovement[] = {0, 1, 0, 1, 1, -1, -1};
    int jMovement[] = {1, 1, -1, 0, -1, 1, -1};


    if (i == 0 && j == 0)
    {
        for (size_t k = 0; k < m_width; ++k)
        {
            for (size_t l = 0; l < m_height; ++l)
            {
                if (labelMatrix.values[k][l] == start)
                {
                    area[0] += 1;
                    labelMatrix.values[k][l] = component;
                }
            }
        }
    }

    size_t k       = 0;
    size_t it      = 0;
    bool breakflag = false;

    while ((i < m_height) && (j < m_height) && i && j)
    {
        labelMatrix.values[i][j] = component;
        for (k = 0; k < 7; ++k)
        {
            if (labelMatrix.values[i + iMovement[k]][j + jMovement[k]] == start)
            {
                area[component] += 1;
                i += iMovement[k];
                j += jMovement[k];
                break;
            }

            ++it;

            if (it >= m_width * m_height)
            {
                breakflag = true;
                break;
            }
        }
        if (k == 7 || breakflag)
        {
            break;
        }
    }
}