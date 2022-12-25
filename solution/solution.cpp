#include "solution.hpp"

Solver::Solver() : sz(0), pdata(nullptr) {}

Solver::~Solver() {
	if (pdata == nullptr)  {
		return;
	}
	delete pdata;
}

void Solver::read(std::istream& file) {
	file >> sz;
	pdata = new std::pair<Point, double>[sz];

	double alpha, phi, d;
	for (int i = 0; i < sz; ++i) {
		file >> alpha >> phi >> d;
		pdata[i].first = Point(alpha, phi);
		pdata[i].second = d;
	}
}

Point Solver::calc() const {
	return Point(0, 0, 0);
}

bool Solver::validate(const Point& P) const {
	// точка на сфере
	if (!eq(1, P.len())) {
		return false;
	}

	// не противоречит данным
	for (int i = 0; i < sz; ++i) {
		double realDist = pdata[i].second;
		double dist = distOnSphere(1, P, pdata[i].first);
		if (!eq(realDist, dist)) {
			return false;
		}
	}
	
	return true;
}