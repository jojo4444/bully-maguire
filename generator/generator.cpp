#include "generator.hpp"

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
            pdata[i] = SpherePoint(0, step * i);
        }
        pdata[pdata.size() - 1] = genPoint();
    }
    result = genPoint();
}

Point Generator::getResult() const {
    return Point(result.first, result.second);
}

SpherePoint Generator::genPoint() const {
    std::uniform_real_distribution<double> alpha(-PI / 2, PI / 2), phi(0., 2 * PI);
    return SpherePoint(alpha(rnd), phi(rnd));
}

void Generator::write(std::ostream& stream) const {
    Point res(result.first, result.second);
    stream << pdata.size() << "\n";
    for (size_t i = 0; i < pdata.size(); ++i) {
        auto [alpha, phi] = std::tie(pdata[i].first, pdata[i].second);
        Point here = Point(alpha, phi);
        double dist = distOnSphere(here, res);
        stream << std::setprecision(18) << std::fixed << alpha << " " << phi << " " << dist << "\n";
    }
}
