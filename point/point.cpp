#include "point.hpp"

Point::Point() : x(0), y(0), z(0) {}

Point::Point(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::Point(double alpha, double phi) {
	double cosAlpha = cos(alpha);
	x = cosAlpha*cos(phi);
	y = cosAlpha*sin(phi);
	z = sin(alpha);
}

Point Point::operator+(const Point& T) const {return Point(x + T.x, y + T.y, z + T.z);}
Point Point::operator-(const Point& T) const {return Point(x - T.x, y - T.y, z - T.z);}
Point Point::operator*(double T) const {return Point(x * T, y * T, z * T);}

Point& Point::operator+=(const Point& T) {return *this = *this + T;}
Point& Point::operator-=(const Point& T) {return *this = *this - T;}
Point& Point::operator*=(double T) {return *this = (*this) * T;}

double Point::operator%(const Point& T) const {return x*T.x + y*T.y + z*T.z;}

bool Point::operator==(const Point& T) const {
	return eq(x, T.x) && eq(y, T.y) && eq(z, T.z);
}

double Point::len() const {
	return std::sqrt(*this % *this);
}

Line::Line() = default;

Line::Line(const Point& s, const Point& v) {
	this->s = s;
	this->v = v;
}

bool eq(double A, double B) {
	return std::abs(A - B) < EPS;
}

double det(double a00, double a01, double a10, double a11) {
	return a00*a11 - a01*a10;
}

vector<double> quadraticEq(double a, double b, double c) {
	// bx + c = 0
	if (eq(a, 0)) {
		if (!eq(b, 0)) {
			return {-c/b};
		}
		return {};
	}

	double d = b*b - 4*a*c;
	if (d < -EPS) {
		return vector<double>();
	}

	if (d < EPS) {
		return {-b / (2*a)};
	}

	d = sqrtl(d);
	return {(-b - d) / (2*a), (-b + d) / (2*a)};
}

double angle(const Point& L, const Point& R) {
	double cosAlpha = (L % R) / (L.len() * R.len());
	cosAlpha = std::min(static_cast<double>(1), cosAlpha);
	cosAlpha = std::max(static_cast<double>(-1), cosAlpha);
	return std::acos(cosAlpha);
}

vector<Point> interSphereLine(double R, const Line& L) {
	double a = L.v % L.v;
	double b = 2*(L.v % L.s);
	double c = (L.s % L.s) - R*R;

	vector<double> roots = quadraticEq(a, b, c);

	vector<Point> res(roots.size());
	for (int i = 0; i < res.size(); ++i) {
		res[i] = L.s + L.v*roots[i];
	}
	return res;
}

double distOnSphere(double R, const Point& A, const Point& B) {
	return angle(A,B)*R;
}
