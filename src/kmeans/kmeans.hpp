#ifndef SRC_KMEANS
#define SRC_KMEANS

#include <vector>

#include "colors/colors.hpp"
#include "matrix/matrix.hpp"

class KMeans
{
private:
    const unsigned int COST_THRESHOLD = 10;
    const unsigned int IT_THRESHOLD = 5;
    unsigned int m_k;
    size_t m_length;

    std::vector<Colors> centroids;

public:
    std::vector<Colors> clusters;

private:
    void mainLoop(const std::vector<Colors>& colors);
    void initCentroids(const std::vector<Colors>& colors);

    void fillMatrix(Matrix& matrix, float value) const;
    size_t findMinIndex(const std::vector<float>& array) const;
    size_t findMaxIndex(const std::vector<float>& array) const;

public:
    KMeans();
    KMeans(unsigned int k, size_t length);
    void calculate(const std::vector<Colors>& colors);
    ~KMeans();
};

#endif