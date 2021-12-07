#ifndef SRC_LABEL
#define SRC_LABEL

#include <vector>

#include "colors/colors.hpp"
#include "matrix/matrix.hpp"
struct Matches
{
    bool r;
    bool g;
    bool b;

    Matches() : r(0), g(0), b(0) {};
    Matches(bool r, bool g, bool b) : r(r), g(g), b(b) {};
    ~Matches() {};
};

class Label
{
private:
    const size_t MATCHES_SIZE = 3;
    size_t m_width;
    size_t m_height;

public:
    std::vector<int> labels;
    std::vector<Colors> colors;
    std::vector<Colors> colors_ex;
    Matrix labelMatrix;
    Matrix visited;
    std::vector<int> area;

private:
    Matches isMember(const Colors& c1, const Colors& c2) const;
    size_t findTrue(const std::vector<bool>& array) const;
    void makeLabelMatrix();
    bool isSafe(int row, int col, float c, int n, int l);
    void DFS(int row, int col, float c, int n, int l);
    int connectedComponents(int n);
    void insertConnectedComponents(int i, int j, int component);
    void invert();


public:
    Label();
    Label(size_t width, size_t height);
    ~Label();
    void calculate(const std::vector<Colors>& RGB);
    void print() const;
    void save(const char* path) const;
};

#endif