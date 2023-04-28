#include <iomanip>

#include "solutionSphere.hpp"

/*
test:

*/

int main() {
    SolverSphere s;

    s.read(std::cin);
    Point res = s.calc();

    std::cout << std::setprecision(18) << std::fixed << res.x << " " << res.y << " " << res.z << "\n";

    return 0;
}