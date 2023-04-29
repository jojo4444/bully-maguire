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
    // возвращает геодезическую кривую относительно i точки pdata
    GeographicLib::GeodesicLine getGeoLine(int i) const;

    vector<std::pair<Point, double>> pdata;
};

#endif