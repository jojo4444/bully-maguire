#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include <iostream>
#include <iomanip>
#include <random>

#include "point.hpp"

using SpherePoint = std::pair<double, double>;

class Generator {
public:
	Generator(int n, uint32_t seed);
	~Generator();

	void write(std::ostream& stream) const;

private:
	void generate();
	SpherePoint genPoint() const;

	int n;
	SpherePoint* pdata;
	mutable std::mt19937 rnd;
	SpherePoint result;
};

#endif