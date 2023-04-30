#include "point.hpp"

// TODO: replace to WGS84
GeographicLib::Geodesic& Earth() {
    static GeographicLib::Geodesic earth(Rmean, 0);
    // static GeographicLib::Geodesic earth = GeographicLib::Geodesic::WGS84();
    return earth;
}

Point::Point(double x, double y, double z)
    : x(x)
    , y(y)
    , z(z) {

    lat = PI / 2 - atan2(std::hypot(x, y), z);
    lon = atan2(y, x);
}

Point::Point(double lat, double lon)
    : lat(lat)
    , lon(lon) {
    double cosLat = cos(lat);
    x = cosLat * cos(lon) * Rmean;
    y = cosLat * sin(lon) * Rmean;
    z = sin(lat) * Rmean;
}

Point Point::operator+(const Point& T) const {
    Point res = *this;
    res += T;
    return res;
}
Point Point::operator-(const Point& T) const {
    Point res = *this;
    res -= T;
    return res;
}
Point Point::operator*(double T) const {
    Point res = *this;
    res *= T;
    return res;
}

Point& Point::operator+=(const Point& T) {
    x += T.x;
    y += T.y;
    z += T.z;
    return *this;
}
Point& Point::operator-=(const Point& T) {
    x -= T.x;
    y -= T.y;
    z -= T.z;
    return *this;
}
Point& Point::operator*=(double T) {
    x *= T;
    y *= T;
    z *= T;
    return *this;
}

double Point::operator%(const Point& T) const {
    return x * T.x + y * T.y + z * T.z;
}

bool Point::operator==(const Point& T) const {
    return eq(x, T.x) && eq(y, T.y) && eq(z, T.z);
}

double Point::len() const {
    return std::sqrt(*this % *this);
}

bool eq(double A, double B) {
    return std::abs(A - B) < EPS;
}

double det33(double a00, double a01, double a02, double a10, double a11, double a12, double a20, double a21, double a22) {
    double add = a00 * a11 * a22 + a10 * a02 * a21 + a20 * a01 * a12;
    double sub = a20 * a11 * a02 + a10 * a01 * a22 + a00 * a21 * a12;
    return add - sub;
}

double angle(const Point& L, const Point& R) {
    double cosAlpha = (L % R) / (L.len() * R.len());
    cosAlpha = std::min<double>(1, cosAlpha);
    cosAlpha = std::max<double>(-1, cosAlpha);
    return std::acos(cosAlpha);
}

double distOnSphere(const Point& A, const Point& B) {
    return angle(A, B) * Rmean;
}

double distOnGeoidDeg(const GeoPoint& A, const GeoPoint& B) {
    double result;
    Earth().Inverse(A.first, A.second, B.first, B.second, result);
    return result;
}