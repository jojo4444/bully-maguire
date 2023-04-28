#ifndef POINT_HEADER
#define POINT_HEADER

#include <cmath>
#include <vector>

using std::cos;
using std::sin;
using std::vector;

const double EPS = 1e-8;
const double PI = 3.1415926535897932;

// https://en.wikipedia.org/wiki/Earth_radius
const double Rmean = 6371008.8;

struct Point {
    double x = 0;
    double y = 0;
    double z = 0;

    Point() = default;
    Point(double x, double y, double z);

    // alpha [-PI/2; PI/2]
    // phi   [0; 2*PI)
    // R = Rmean
    Point(double alpha, double phi);

    Point operator+(const Point& T) const;
    Point operator-(const Point& T) const;
    Point operator*(double T) const;

    Point& operator+=(const Point& T);
    Point& operator-=(const Point& T);
    Point& operator*=(double T);

    // скалярное произведение
    double operator%(const Point& T) const;

    bool operator==(const Point& T) const;

    double len() const;
};

// проверяет |a - b| < EPS
bool eq(double A, double B);

// вычисляет определитель 3x3
double det33(double a00, double a01, double a02, double a10, double a11, double a12, double a20, double a21, double a22);

// находит угол между векторами [0; PI]
double angle(const Point& L, const Point& R);

// находит расстояние на сфере радиуса Rmean между точками A, B
double distOnSphere(const Point& A, const Point& B);

#endif