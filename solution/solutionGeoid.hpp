#ifndef SOLUTION_GEOID_HEADER
#define SOLUTION_GEOID_HEADER

#include <iostream>
#include <vector>

#include "point.hpp"

class SolverGeoid {
public:
    SolverGeoid(const vector<std::pair<Point, double>>& pdata);
    ~SolverGeoid() = default;

    Point calc(Point approach) const;

private:
    vector<std::pair<Point, double>> pdata;
};

#endif