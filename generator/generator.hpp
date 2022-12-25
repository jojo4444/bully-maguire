#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "point.hpp"
#include <iostream>
#include <iomanip>
#include <random>

using std::ostream;
using std::uniform_real_distribution;
using std::mt19937;
using SpherePoint = std::pair<double, double>;


class Generator {
public:
	Generator(size_t n, size_t seed);
	~Generator();
	void write(ostream& stream);

private:
	void generate();
	Point convert(const SpherePoint& p);
	SpherePoint p;
	SpherePoint* pdata;
	size_t n;
	mt19937 rnd;
};

#endif