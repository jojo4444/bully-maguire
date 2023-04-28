#ifndef SOLUTION_HEADER
#define SOLUTION_HEADER

#include <iostream>
#include <vector>

#include "point.hpp"

class Solver {
public:
    Solver() = default;
    ~Solver() = default;

    void read(std::istream& stream);

    Point calc() const;

private:
    vector<std::pair<Point, double>> pdata;
};

#endif