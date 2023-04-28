#include "generator.hpp"

#include <GeographicLib/Geodesic.hpp>

Generator::Generator(int n, uint32_t seed)
    : rnd(seed) {
    pdata.resize(n);
}

void Generator::generate(Mode m) {
    if (m == Mode::Random) {
        for (auto& p : pdata) {
            p = genPoint();
        }
    } else {
        double step = 2 * PI / pdata.size();
        for (size_t i = 0; i + 1 < pdata.size(); ++i) {
            pdata[i] = GeoPoint(0, step * i);
        }
        pdata[pdata.size() - 1] = genPoint();
    }
    result = genPoint();
}

Point Generator::getResult() const {
    return Point(result.first / 180 * PI, result.second / 180 * PI);
}

// Генерация в градусах
// https://geographiclib.sourceforge.io/C++/doc/classGeographicLib_1_1Geodesic.html#afdca5eb7c37fa2fecf124aecd6c436fd
// https://geographiclib.sourceforge.io/html/python/interface.html#restrictions-on-the-parameters
GeoPoint Generator::genPoint() const {
    std::uniform_real_distribution<double> lat(-90, 90), lon(-180, 180);
    return GeoPoint(lat(rnd), lon(rnd));
}

void Generator::write(std::ostream& stream) const {
    stream << pdata.size() << "\n";
    for (size_t i = 0; i < pdata.size(); ++i) {
        double dist = distOnGeoidDeg(result, pdata[i]);
        auto [lat, lon] = std::tie(pdata[i].first, pdata[i].second);
        stream << std::setprecision(18) << std::fixed << lat << " " << lon << " " << dist << "\n";
    }
}
