#include "solutionGeoid.hpp"
#include "solutionSphere.hpp"

#include <vector>

using std::vector, std::pair;

extern "C" struct DLLInData {
    double lat;
    double lon;
    double d;
};

extern "C" struct OutData {
    double x;
    double y;
    double z;
};

extern "C" __declspec(dllexport) int __cdecl calc(int n, DLLInData* in, OutData* out) {
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
