#include "solutionGeoid.hpp"

SolverGeoid::SolverGeoid(const vector<std::pair<Point, double>>& pdata)
    : pdata(pdata) {}

Point SolverGeoid::calc(Point approach) const {
    return approach;
}