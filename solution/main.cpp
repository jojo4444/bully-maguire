#include "solution.hpp"

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