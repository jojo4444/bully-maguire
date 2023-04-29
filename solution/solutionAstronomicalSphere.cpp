#include "solutionAstronomicalSphere.hpp"

#include "point.hpp"
#include "solutionSphere.hpp"

#include <cmath>

SolverAstronomicalSphere::SolverAstronomicalSphere(const vector<SolverAstronomicalSphere::CelestialSpherePoint>& pdata)
    : pdata(pdata) {}

void SolverAstronomicalSphere::read(std::istream& stream) {
    int sz;
    stream >> sz;

    if (sz < 3) {
        throw std::logic_error("small amount of data (requires at least 3)");
    }

    pdata.resize(sz);

    double phi, delta, t;
    for (int i = 0; i < sz; ++i) {
        stream >> pdata[i].phi >> pdata[i].delta >> pdata[i].t;
    }
}

Point SolverAstronomicalSphere::calc() const {
    vector<std::pair<Point, double>> v(pdata.size());
    double delta, phi, t, hsin, d;
    for (int i = 0; i < pdata.size(); ++i) {

        delta = (pdata[i].delta / 180) * PI; // lat
        t = (pdata[i].t / 180) * PI; //lon
        phi = (pdata[i].phi / 180) * PI;
        
        /* 
         * sin(h) - синус высоты 
         * sin(h) = sin(phi) * sin(delta) + cos(phi) * cos(delta) * cos(t)
        */
        hsin = sin(phi) * sin(delta) + cos(phi) * cos(delta) * cos(t);
        hsin = std::max<double>(-1, std::min<double>(1, hsin));
        d = (PI - asin(hsin)) * Rmean;
        
        v[i].first = Point(delta, t);
        v[i].second = d;
    }

    SolverSphere pharosSolver(v);
    return pharosSolver.calc();
}
