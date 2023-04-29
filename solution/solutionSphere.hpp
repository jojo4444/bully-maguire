#ifndef SOLUTION_SPHERE_HEADER
#define SOLUTION_SPHERE_HEADER

#include <iostream>
#include <vector>

#include "point.hpp"

class SolverSphere {
public:
    SolverSphere() = default;

    ~SolverSphere() = default;

    SolverSphere(vector<std::pair<Point, double>>);

    vector<std::pair<Point, double>> getData() const;

    void read(std::istream& stream);

    Point calc() const;

private:
    vector<std::pair<Point, double>> pdata;
};

#endif