#include <cmath>
#include <cassert>
#include <algorithm>
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Polygon.hpp"


using namespace ToyGameEngine::Math;

Geometry::Point::Point()
{

}

Geometry::Point::Point(const double x_, const double y_)
    : x(x_), y(y_)
{

}

Geometry::Point::Point(const Point &point)
    : Geometry::GeometryObject(point), x(point.x), y(point.y)
{

}

Geometry::Point::Point(const Geometry::MarkedPoint &point)
    : x(point.x), y(point.y)
{

}

Geometry::Point &Geometry::Point::operator=(const Geometry::Point &point)
{
    if (&point != this)
    {
        Geometry::GeometryObject::operator=(point);
        x = point.x;
        y = point.y;
    }
    return *this;
}

bool Geometry::Point::operator==(const Geometry::Point &point) const
{
    return x == point.x && y == point.y;
}

bool Geometry::Point::operator!=(const Geometry::Point &point) const
{
    return x != point.x || y != point.y;
}

Geometry::Point &Geometry::Point::normalize()
{
    const double len = length();
    assert(len > 0);
    x /= len;
    y /= len;
    return *this;
}

Geometry::Point Geometry::Point::normalized() const
{
    const double len = length();
    assert(len > 0);
    return Geometry::Point(x / len, y / len);
}

Geometry::Point Geometry::Point::vertical() const
{
    return Geometry::Point(-y, x);
}

double Geometry::Point::length() const
{
    return std::sqrt(x * x + y * y);
}

bool Geometry::Point::empty() const
{
    return x == 0 && y == 0;
}

void Geometry::Point::clear()
{
    x = y = 0;
}

Geometry::Point *Geometry::Point::clone() const
{
    return new Geometry::Point(x, y);
}

void Geometry::Point::transform(const double a, const double b, const double c, const double d, const double e, const double f)
{
    const double x_ = x, y_ = y;
    x = a * x_ + b * y_ + c;
    y = d * x_ + e * y_ + f;
}

void Geometry::Point::transform(const double mat[6])
{
    const double x_ = x, y_ = y;
    x = mat[0] * x_ + mat[1] * y_ + mat[2];
    y = mat[3] * x_ + mat[4] * y_ + mat[5];
}

void Geometry::Point::translate(const double tx, const double ty)
{
    x += tx;
    y += ty;
}

void Geometry::Point::rotate(const double x_, const double y_, const double rad)
{
    x -= x_;
    y -= y_;
    const double x1 = x, y1 = y;
    x = x1 * std::cos(rad) - y1 * std::sin(rad);
    y = x1 * std::sin(rad) + y1 * std::cos(rad);
    x += x_;
    y += y_;
}

void Geometry::Point::scale(const double x_, const double y_, const double k)
{
    const double x1 = x, y1 = y;
    x = k * x1 + x_ * (1 - k);
    y = k * y1 + y_ * (1 - k);
}

Geometry::Type Geometry::Point::type() const
{
    return Geometry::Type::POINT;
}

Geometry::AABBRect Geometry::Point::bounding_rect() const
{
    if (length() == 0)
    {
        return Geometry::AABBRect();
    }
    else
    {
        return Geometry::AABBRect(std::min(0.0, x), std::min(0.0, y), std::max(0.0, x), std::max(0.0, y));
    }
}

Geometry::Polygon Geometry::Point::mini_bounding_rect() const
{
    if (length() == 0)
    {
        return Geometry::Polygon();
    }
    else
    {
        return Geometry::AABBRect(std::min(0.0, x), std::min(0.0, y), std::max(0.0, x), std::max(0.0, y));
    }
}

Geometry::Point Geometry::Point::operator*(const double k) const
{
    return Geometry::Point(x * k, y * k);
}

double Geometry::Point::operator*(const Point &point) const
{
    return x * point.x + y * point.y;
}

double Geometry::Point::cross(const Point &point) const
{
    return x * point.y - y * point.x;
}

Geometry::Point Geometry::Point::operator+(const Point &point) const
{
    return Geometry::Point(x + point.x, y + point.y);
}

Geometry::Point Geometry::Point::operator-(const Point &point) const
{
    return Geometry::Point(x - point.x, y - point.y);
}

Geometry::Point Geometry::Point::operator/(const double k) const
{
    assert(k != 0);
    return Geometry::Point(x / k, y / k);
}

void Geometry::Point::operator*=(const double k)
{
    x *= k;
    y *= k;
}

void Geometry::Point::operator+=(const Point &point)
{
    x += point.x;
    y += point.y;
}

void Geometry::Point::operator-=(const Point &point)
{
    x -= point.x;
    y -= point.y;
}

void Geometry::Point::operator/=(const double k)
{
    assert(k != 0);
    x /= k;
    y /= k;
}