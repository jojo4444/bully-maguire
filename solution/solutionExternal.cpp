#include "solutionGeoid.hpp"
#include "solutionSphere.hpp"
#include "solutionAstronomicalSphere.hpp"

#include <vector>

using std::vector, std::pair;

extern "C" {
    struct DllPolarСircle {
        double lat, lon, d;
    };

    struct DllCelestialSpherePoint {
        double phi, delta, t;
    };

    struct DllPoint {
        double x, y, z;
    };
}

extern "C" __declspec(dllexport) int __cdecl pharosCalc(int n, DllPolarСircle* in, DllPoint* out) {
    int r = 0;
    try {
        vector<pair<Point, double>> pdata(n);
        for (int i = 0; i < n; ++i) {
            pdata[i].first = Point((in[i].lat / 180) * PI, (in[i].lon / 180) * PI);
            pdata[i].second = in[i].d;
        }

        SolverSphere sphere(pdata);
        Point approach = sphere.calc();

        SolverGeoid geoid(sphere.getData());
        Point res = geoid.calc(approach);

        out->x = res.x;
        out->y = res.y;
        out->z = res.z;

    } catch (...) {
        r = -1;
    }

    return r;
}

extern "C" __declspec(dllexport) int __cdecl astronomicCalc(int n, DllCelestialSpherePoint* in, DllPoint* out) {
    int r = 0;
    try {
        vector<SolverAstronomicalSphere::CelestialSpherePoint> pdata(n);
        for (int i = 0; i < n; ++i) {
            pdata[i].phi = in[i].phi;
            pdata[i].delta = in[i].delta;
            pdata[i].t = in[i].t;
        }

        SolverAstronomicalSphere solver(pdata);
        Point res = solver.calc();

        out->x = res.x;
        out->y = res.y;
        out->z = res.z;

    } catch (...) {
        r = -1;
    }

    return r;
}
