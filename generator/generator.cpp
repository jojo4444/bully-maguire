#include "generator.hpp"

Generator::Generator(int n, uint32_t seed): rnd(seed) {
	this->n = n;
	pdata = new SpherePoint[n];
	generate();
}

Generator::~Generator() {
	if (pdata != nullptr) {
		delete[] pdata;
	}
}

void Generator::generate() {
	for (int i = 0; i < n; ++i) {
		pdata[i] = genPoint();
	}
	result = genPoint();
}

SpherePoint Generator::genPoint() const {
	std::uniform_real_distribution<double> alpha(-PI/2, PI/2), phi(0., 2*PI);
	return SpherePoint(alpha(rnd), phi(rnd));
}

void Generator::write(std::ostream& stream) const {
	Point res(result.first, result.second);
	stream << n << "\n";
	for (size_t i = 0; i < n; ++i) {
		auto [alpha, phi] = std::tie(pdata[i].first, pdata[i].second);
		Point here = Point(alpha, phi);
		double dist = distOnSphere(1, here, res);
		stream << std::setprecision(9) << std::fixed << alpha << " " << phi << " " <<  dist << "\n";
	}
}
