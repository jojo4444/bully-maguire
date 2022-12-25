#include "generator.hpp"

/*
mode:
- random
- section
*/

Mode getMode(const std::string& mode) {
	if (mode == "random") {
		return Mode::Random;
	}
	return Mode::Section;
}

int main() {
	int n;
	std::string mode;
	std::cin >> n >> mode;

	std::random_device d;
	Generator g(n, d());

	g.generate(getMode(mode));

	g.write(std::cout);

	Point res = g.getResult();
	std::cout << std::setprecision(9) << std::fixed << res.x << " " << res.y << " " << res.z << "\n";

	return 0;
}