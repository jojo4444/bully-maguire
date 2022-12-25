#include "generator.hpp"

int main() {
	int n;
	std::cin >> n;

	std::random_device d;
	Generator g(n, d());

	g.write(std::cout);

	return 0;
}