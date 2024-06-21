#include <cmath>
#include <cassert>
#include "Math/Geometry/Circle.hpp"
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Polygon.hpp"


using namespace ToyGameEngine::Math;

Geometry::Circle::Circle()
{

}

Geometry::Circle::Circle(const double x, const double y, const double r)
    : Geometry::Point(x, y), radius(r)
{

}

Geometry::Circle::Circle(const Geometry::Point &point, const double r)
    : Geometry::Point(point), radius(r)
{

}

Geometry::Circle::Circle(const Geometry::Circle &circle)
    : Geometry::Point(circle), radius(circle.radius)
{

}

Geometry::Circle &Geometry::Circle::operator=(const Geometry::Circle &circle)
{
    if (this != &circle)
    {
        Geometry::Point::operator=(circle);
        radius = circle.radius;
    }
    return *this;
}

double Geometry::Circle::area() const
{
    return Geometry::PI * radius * radius;
}

double Geometry::Circle::length() const
{
    return 2.0 * Geometry::PI * radius;
}

bool Geometry::Circle::empty() const
{
    return radius <= 0;
}

void Geometry::Circle::clear()
{
    Geometry::Point::clear();
    radius = 0;
}

Geometry::Circle *Geometry::Circle::clone() const
{
    return new Geometry::Circle(*this);
}

void Geometry::Circle::transform(const double a, const double b, const double c, const double d, const double e, const double f)
{
    Geometry::Point::transform(a,b,c,d,e,f);
    radius *= std::abs(a);
}

void Geometry::Circle::transform(const double mat[6])
{
    Geometry::Point::transform(mat);
    radius *= std::abs(mat[0]);
}

void Geometry::Circle::scale(const double x, const double y, const double k)
{
    Geometry::Point::scale(x, y, k);
    radius *= k;
}

Geometry::Type Geometry::Circle::type() const
{
    return Geometry::Type::CIRCLE;
}

Geometry::AABBRect Geometry::Circle::bounding_rect() const
{
    if (radius == 0)
    {
        return Geometry::AABBRect();
    }
    else
    {
        return Geometry::AABBRect(x - radius, y + radius, x + radius, y - radius);
    }
}

Geometry::Polygon Geometry::Circle::mini_bounding_rect() const
{
    if (radius == 0)
    {
        return Geometry::Polygon();
    }
    else
    {
        return Geometry::AABBRect(x - radius, y + radius, x + radius, y - radius);
    }
}

Geometry::Circle Geometry::Circle::operator+(const Geometry::Point &point) const
{
    return Geometry::Circle(x + point.x, y + point.y, radius);
}

Geometry::Circle Geometry::Circle::operator-(const Geometry::Point &point) const
{
    return Geometry::Circle(x - point.x, y - point.y, radius);
}