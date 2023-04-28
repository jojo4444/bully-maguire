#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include <iomanip>
#include <iostream>
#include <random>

#include "point.hpp"

enum class Mode { Random, Section };

class Generator {
public:
    Generator(int n, uint32_t seed);
    ~Generator() = default;

    void generate(Mode m);

    Point getResult() const;

    void write(std::ostream& stream) const;

private:
    GeoPoint genPoint() const;

    vector<GeoPoint> pdata;
    mutable std::mt19937 rnd;
    GeoPoint result;
};

#endif