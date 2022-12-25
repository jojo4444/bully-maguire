#include <iomanip>

#include "solution.hpp"

/*
test:

*/

int main() {
	Solver s;
	
	s.read(std::cin);
	Point res = s.calc();

	if (!s.validate(res)) {
		return -1;
	}

	std::cout << std::setprecision(9) << std::fixed << res.x << " " << res.y << " " << res.z << "\n";

	return 0;
}