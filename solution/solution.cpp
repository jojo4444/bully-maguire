#include "solution.hpp"

Solver::Solver() : pdata(nullptr) {}

Solver::~Solver() {
	delete pdata;
}