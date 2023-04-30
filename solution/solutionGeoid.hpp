#ifndef SOLUTION_GEOID_HEADER
#define SOLUTION_GEOID_HEADER

#include <iostream>
#include <vector>

#include <GeographicLib/GeodesicLine.hpp>

#include "point.hpp"

class SolverGeoid {
public:
    SolverGeoid() = delete;
    SolverGeoid(const vector<std::pair<Point, double>>& pdata);
    ~SolverGeoid() = default;

    Point calc(Point approach) const;

private:
    // возвращает ближайшую к P точку на кривой, точки которой равноудалены от C на s
    //
    // O(log(eps^-1))
    GeoPoint getNearest(GeoPoint C, double s, GeoPoint P) const;

    vector<std::pair<Point, double>> pdata;
};

#endif