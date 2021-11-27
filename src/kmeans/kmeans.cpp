#include "kmeans.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

KMeans::~KMeans() {}

KMeans::KMeans() : m_k(0), m_length(0) {}

KMeans::KMeans(unsigned int k, size_t length) : m_k(k), m_length(length) {}

void KMeans::calculate(const std::vector<Colors>& colors)
{
    centroids.resize(m_k);
    initCentroids(colors);

    clusters.resize(m_length);
    mainLoop(colors);
}

size_t KMeans::findMinIndex(const std::vector<float>& array) const
{
    auto min           = std::min_element(array.begin(), array.end());
    unsigned int index = std::distance(array.begin(), min);
    return index;
}

size_t KMeans::findMaxIndex(const std::vector<float>& array) const
{
    auto max     = std::max_element(array.begin(), array.end());
    size_t index = std::distance(array.begin(), max);
    return index;
}


void KMeans::fillMatrix(Matrix& matrix, float value) const
{
    for (size_t i = 0; i < m_length; ++i)
    {
        for (size_t j = 0; j < m_k; ++j)
        {
            matrix.values[i][j] = value;
        }
    }
}

void KMeans::mainLoop(const std::vector<Colors>& colors)
{
    size_t i = 1;

    std::vector<float> cost(IT_THRESHOLD + 1);
    std::vector<float> sum(m_k);

    Matrix distance(m_length, m_k);
    Matrix R_nk(m_length, m_k);

    cost[0] = 0;
    cost[1] = 0;

    while (i < IT_THRESHOLD)
    {
        distance.fill(0);
        R_nk.fill(0);

        for (size_t j = 0; j < m_length; ++j)
        {
            for (size_t k = 0; k < m_k; ++k)
            {
                distance.values[j][k] = colors[j].distance(centroids[k]);
            }
            size_t minIndex   = findMinIndex(distance.values[j]);
            R_nk.values[j][minIndex] = 1.0;
        }

        cost[i] = 0;
        sum     = {0};

        for (size_t j = 0; j < m_length; ++j)
        {
            for (size_t k = 0; k < m_k; ++k)
            {
                cost[i] += R_nk.values[j][k] * distance.values[j][k];
            }
            for (size_t s = 0; s < m_k; ++s)
            {
                sum[s] += R_nk.values[j][s];
            }
        }

        for (size_t j = 0; j < m_length; ++j)
        {
            for (size_t k = 0; k < m_k; ++k)
            {
                Colors temp = colors[j].multiply(R_nk.values[j][k]);

                if (!(temp.r == 0 && temp.g == 0 && temp.b == 0))
                {
                    centroids[k] = centroids[k].add(temp);
                }
            }
        }
        for (size_t j = 0; j < m_k; ++j)
        {
            if (sum[j] != 0)
            {
                centroids[j] = centroids[j].divide(sum[j]);
            }
        }
        if (fabs(cost[i] - cost[i - 1]) < COST_THRESHOLD)
        {
            break;
        }
        ++i;
    }
    for (size_t i = 0; i < m_length; ++i)
    {
        unsigned long int maxIndex = findMaxIndex(R_nk.values[i]);
        clusters[i].r              = centroids[maxIndex].r;
        clusters[i].g              = centroids[maxIndex].g;
        clusters[i].b              = centroids[maxIndex].b;
    }
}

void KMeans::initCentroids(const std::vector<Colors>& colors)
{
    std::random_device rd;
    std::mt19937 e1(rd());
    std::uniform_int_distribution<> uniform_dist(0, m_length - 1);

    for (size_t i = 0; i < m_k; ++i)
    {
        centroids[i].r = colors[uniform_dist(e1)].r;
        centroids[i].g = colors[uniform_dist(e1)].g;
        centroids[i].b = colors[uniform_dist(e1)].b;
    }
}