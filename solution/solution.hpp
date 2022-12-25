#ifndef SOLUTION_HEADER
#define SOLUTION_HEADER

#include <iostream>

#include "point.hpp"

class Solver {
public:
	Solver();
	~Solver();

	void read(std::istream& stream);

	Point calc() const;
	
	bool validate(const Point& P) const;

private:
	int sz;
	std::pair<Point, double>* pdata;
};

#endif