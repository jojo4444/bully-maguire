#ifndef SOLUTION_SPHERE_HEADER
#define SOLUTION_SPHERE_HEADER

#include <iostream>
#include <vector>

#include "point.hpp"

class SolverSphere {
public:
    SolverSphere() = default;
    ~SolverSphere() = default;

    void read(std::istream& stream);

    Point calc() const;

private:
    vector<std::pair<Point, double>> pdata;
};

#endif