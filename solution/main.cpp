#include <iomanip>

#include "solutionGeoid.hpp"
#include "solutionSphere.hpp"

/*
test:

*/

int main() {
    SolverSphere sphere;
    sphere.read(std::cin);
    Point approach = sphere.calc();

    SolverGeoid geoid(sphere.getData());
    Point res = geoid.calc(approach);

    std::cout << std::setprecision(18) << std::fixed << res.x << " " << res.y << " " << res.z << "\n";

    return 0;
}