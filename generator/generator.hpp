#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "point.hpp"
#include <iostream>
#include <random>

using std::iostream;
using std::mt19937;
using PolarPoint = std::pair<double, double>;

class Generator {
public:
	Generator(size_t n, const mt19937& rnd);
	~Generator();
	void write(iostream stream);

private:
	void generate();
	mt19937 rnd_;
	Point cpoint_;
	Point* pdata_;
	size_t n_;

};

#endif