#ifndef POINT_HEADER
#define POINT_HEADER

/*
все вычисления проводятся с точностью EPS
*/

#include <vector>
#include <cmath>

using std::vector;
using std::cos;
using std::sin;

const double EPS = 1e-8;
const double PI = 3.1415926535897932;

struct Point {
	double x, y, z;

	Point();
	Point(double x, double y, double z);

	// alpha [-PI/2; PI/2]
	// phi   [0; 2*PI)
	// R = 1
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

struct Line {
	Line();
	Line(const Point& s, const Point& v);

	Point s, v;
};

// проверяет |a - b| < EPS
bool eq(double A, double B);

// вычисляет определитель 2x2
double det(
	double a00, double a01,
	double a10, double a11);

// находит решения уравнения ax^2 + bx + c = 0
vector<double> quadraticEq(double a, double b, double c);

// находит угол между векторами [0; PI]
double angle(const Point& L, const Point& R);

// пересекает сферу с центром (0, 0, 0) и радиусом R с прямой L
vector<Point> interSphereLine(double R, const Line& L);

// находит расстояние на сфере радиуса R между точками A, B
double distOnSphere(double R, const Point& A, const Point& B);

#endif