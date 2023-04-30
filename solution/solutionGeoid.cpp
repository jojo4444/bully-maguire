#include "solutionGeoid.hpp"

SolverGeoid::SolverGeoid(const vector<std::pair<Point, double>>& pdata)
    : pdata(pdata) {}

Point SolverGeoid::calc(Point approach) const {
    GeoPoint P(approach.lat / PI * 180, approach.lon / PI * 180);

    GeoPoint Ca = GeoPoint(pdata[0].first.lat / PI * 180, pdata[0].first.lon / PI * 180);
    GeoPoint Cb = GeoPoint(pdata[1].first.lat / PI * 180, pdata[1].first.lon / PI * 180);
    double sa = pdata[0].second;
    double sb = pdata[1].second;

    GeoPoint A = getNearest(Ca, sa, P);
    GeoPoint B = getNearest(Cb, sb, P);

    for (int cnt = 0; cnt < 200; ++cnt) {
        if (cnt & 1) {
            A = getNearest(Ca, sa, B);
        } else {
            B = getNearest(Cb, sb, A);
        }
    }
    return Point(A.first / 180 * PI, A.second / 180 * PI);
}

GeoPoint SolverGeoid::getNearest(GeoPoint C, double s, GeoPoint P) const {
    double lat_start, lon_start;
    double lat_midd, lon_midd;
    double s_start, s_midd;

    Earth().Direct(C.first, C.second, 0, s, lat_start, lon_start);
    Earth().Direct(C.first, C.second, 180, s, lat_midd, lon_midd);

    Earth().Inverse(lat_start, lon_start, P.first, P.second, s_start);
    Earth().Inverse(lat_midd, lon_midd, P.first, P.second, s_midd);

    double l = (s_start < s_midd ? -90 : 90);
    double r = l + 180;

    double lsave = l;

    int limSteps = 200; // 10^18*(2/3)^200 ~ 6.05*10^(-18)
    for (int i = 0; i < limSteps; ++i) {
        double d = (r - l) / 3;
        double m1 = l + d;
        double m2 = r - d;

        // quantum precision
        if (m1 == l || m2 == l || m1 == r || m2 == r) {
            break;
        }

        double lat1, lon1;
        double lat2, lon2;

        Earth().Direct(C.first, C.second, m1, s, lat1, lon1);
        Earth().Direct(C.first, C.second, m2, s, lat2, lon2);

        double s1 = distOnGeoidDeg(GeoPoint(lat1, lon1), P);
        double s2 = distOnGeoidDeg(GeoPoint(lat2, lon2), P);

        if (s1 < s2) {
            r = m2;
        } else {
            l = m1;
        }
    }

    double lat_res, lon_res;
    Earth().Direct(C.first, C.second, l, s, lat_res, lon_res);
    return GeoPoint(lat_res, lon_res);
}