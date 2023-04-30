#ifndef SOLUTION_ASTRONOMIC_SPHERE_HEADER
#define SOLUTION_ASTRONOMIC_SPHERE_HEADER

#include "point.hpp"

#include <iostream>
#include <vector>

class SolverAstronomicalSphere {
public:
    /*
        phi - широта наблюдателя
        delta - угол склонения (от небесного экватора)
        t - часовой угол светила
    */
    struct CelestialSpherePoint {
        double phi, delta, t;
    };

    SolverAstronomicalSphere() = default;
    ~SolverAstronomicalSphere() = default;

    SolverAstronomicalSphere(const std::vector<CelestialSpherePoint>&);

    void read(std::istream& stream);

    Point calc() const;

private:
    vector<CelestialSpherePoint> pdata;
};

#endif