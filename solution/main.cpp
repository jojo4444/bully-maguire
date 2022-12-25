#include <iomanip>

#include "solution.hpp"

/*
test:

3
0 0 0.78539816339
0 1.57079632679 0.78539816339
1.57079632679 0 1.57079632679
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