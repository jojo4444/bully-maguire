#include "solutionSphere.hpp"

#include <stdexcept>

SolverSphere::SolverSphere(vector<std::pair<Point, double>> pdata)
    : pdata(pdata){}

vector<std::pair<Point, double>> SolverSphere::getData() const {
    return pdata;
}

void SolverSphere::read(std::istream& stream) {
    int sz;
    stream >> sz;

    if (sz < 3) {
        throw std::logic_error("small amount of data (requires at least 3)");
    }

    pdata.resize(sz);

    double lat, lon, d;
    for (int i = 0; i < sz; ++i) {
        stream >> lat >> lon >> d;
        lat = (lat / 180) * PI;
        lon = (lon / 180) * PI;
        pdata[i].first = Point(lat, lon);
        pdata[i].second = d;
    }
}

Point SolverSphere::calc() const {
    /*
        p - ответ

        скалярная система

        p % O1 = g1
        p % O2 = g2
        p % O3 = g3

        это система плоскостей

        x*O1.x + y*O1.y + z*O1.z = g1
        x*O2.x + y*O2.y + z*O2.z = g2
        x*O3.x + y*O3.y + z*O3.z = g3

        ее решением будет точка, если определитель
        | O1.x O1.y O1.z|
        | O2.x O2.y O2.z| = detMax != 0
        | O3.x O3.y O3.z|

        выбор O1, O2, O3 можно сделать так:
        O1 = pdata[0]
        O2 = pdata[1]
        если эти точки не противоположны, то O3 можно найти среди остальных, и для точности |detMax| -> max
        иначе O2 = pdata[2] и действуем аналогично
    */

    int o1, o2, o3;
    double detMax = 0;
    for (int i = 0; i <= 0; ++i) {
        for (int j = 1; j <= 2; ++j) {
            for (int k = j + 1; k < static_cast<int>(pdata.size()); ++k) {
                Point O1 = pdata[i].first;
                Point O2 = pdata[j].first;
                Point O3 = pdata[k].first;
                double detHere = det33(O1.x, O1.y, O1.z, O2.x, O2.y, O2.z, O3.x, O3.y, O3.z);

                if (std::abs(detHere) > detMax) {
                    detMax = detHere;
                    o1 = i;
                    o2 = j;
                    o3 = k;
                }
            }
        }
    }

    if (eq(detMax, 0)) {
        throw std::logic_error("not the only solution");
    }

    Point O1 = pdata[o1].first;
    double r1 = pdata[o1].second;

    Point O2 = pdata[o2].first;
    double r2 = pdata[o2].second;

    Point O3 = pdata[o3].first;
    double r3 = pdata[o3].second;

    double Rmean2 = Rmean * Rmean;
    double r1_sqr = std::max<double>(0, 2 * Rmean2 - 2 * Rmean2 * cos(r1 / Rmean));
    double r2_sqr = std::max<double>(0, 2 * Rmean2 - 2 * Rmean2 * cos(r2 / Rmean));
    double r3_sqr = std::max<double>(0, 2 * Rmean2 - 2 * Rmean2 * cos(r3 / Rmean));

    double g1 = ((O1 % O1) - r1_sqr + Rmean2) / 2;
    double g2 = ((O2 % O2) - r2_sqr + Rmean2) / 2;
    double g3 = ((O3 % O3) - r3_sqr + Rmean2) / 2;

    double detX = det33(g1, O1.y, O1.z, g2, O2.y, O2.z, g3, O3.y, O3.z);

    double detY = det33(O1.x, g1, O1.z, O2.x, g2, O2.z, O3.x, g3, O3.z);

    double detZ = det33(O1.x, O1.y, g1, O2.x, O2.y, g2, O3.x, O3.y, g3);

    return Point(detX / detMax, detY / detMax, detZ / detMax);
}