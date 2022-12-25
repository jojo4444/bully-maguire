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
		std::cout << "Bad point!\n";
		return -1;
	} 

	std::cout << "Correct point!\n";

	return 0;
}