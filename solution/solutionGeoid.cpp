#include "solutionGeoid.hpp"

SolverGeoid::SolverGeoid(const vector<std::pair<Point, double>>& pdata)
    : pdata(pdata) {}

Point SolverGeoid::calc(Point approach) const {
    GeographicLib::GeodesicLine gl[] = {
        getGeoLine(0),
        getGeoLine(1),
        getGeoLine(2),
    };

    ///

    return approach;
}

GeographicLib::GeodesicLine SolverGeoid::getGeoLine(int i) const {
    double lat1, lon1;
    double lat2, lon2;

    double lat = pdata[i].first.lat / PI * 180;
    double lon = pdata[i].first.lon / PI * 180;
    double s = pdata[i].second;

    // находим две точки, удаленные от i на заданную длину
    Earth().Direct(lat, lon, 4, s, lat1, lon1);
    Earth().Direct(lat, lon, 10, s, lat2, lon2);

    // строим геодезическую по полученным точкам
    return Earth().InverseLine(lat1, lon1, lat2, lon2);
}