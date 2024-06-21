#include <cmath>
#include <cassert>
#include <utility>
#include <algorithm>
#include "Math/Geometry/Triangle.hpp"
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/Polygon.hpp"
#include "Math/Geometry/AABBRect.hpp"


using namespace ToyGameEngine::Math;

Geometry::Triangle::Triangle()
{

}

Geometry::Triangle::Triangle(const Geometry::Point &point0, const Geometry::Point &point1, const Geometry::Point &point2)
{
    _vecs[0] = point0;
    _vecs[1] = point1;
    _vecs[2] = point2;
}

Geometry::Triangle::Triangle(const double x0, const double y0, const double x1, const double y1, const double x2, const double y2)
{
    _vecs[0].x = x0;
    _vecs[0].y = y0;
    _vecs[1].x = x1;
    _vecs[1].y = y1;
    _vecs[2].x = x2;
    _vecs[2].y = y2;
}

Geometry::Triangle::Triangle(const Geometry::Triangle &triangle)
    : Geometry::GeometryObject(triangle)
{
    _vecs[0] = triangle._vecs[0];
    _vecs[1] = triangle._vecs[1];
    _vecs[2] = triangle._vecs[2];
}

bool Geometry::Triangle::empty() const
{
    return _vecs[0] == _vecs[1] || _vecs[1] == _vecs[2] || _vecs[0] == _vecs[2];
}

double Geometry::Triangle::length() const
{
    return Geometry::distance(_vecs[0], _vecs[1]) + Geometry::distance(_vecs[1], _vecs[2]) + Geometry::distance(_vecs[0], _vecs[2]);
}

void Geometry::Triangle::clear()
{
    _vecs[0].clear();
    _vecs[1].clear();
    _vecs[2].clear();
}

Geometry::Triangle *Geometry::Triangle::clone() const
{
    return new Geometry::Triangle(*this);
}

double Geometry::Triangle::area() const
{
    if (empty())
    {
        return 0;
    }
    const double a = Geometry::distance(_vecs[0], _vecs[1]);
    const double b = Geometry::distance(_vecs[1], _vecs[2]);
    const double c = Geometry::distance(_vecs[0], _vecs[2]);
    const double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p- c));
}

double Geometry::Triangle::angle(const size_t index) const
{
    assert(index <= 2);
    if (empty())
    {
        return 0;
    }

    const double len0 = Geometry::distance(_vecs[1], _vecs[2]);
    const double len1 = Geometry::distance(_vecs[0], _vecs[2]);
    const double len2 = Geometry::distance(_vecs[0], _vecs[1]);

    switch (index)
    {
    case 0:
        return std::acos((len1 * len1 + len2 * len2 - len0 * len0) / (2 * len1 * len2));
    case 1:
        return std::acos((len0 * len0 + len2 * len2 - len1 * len1) / (2 * len0 * len2));
    case 2:
        return std::acos((len0 * len0 + len1 * len1 - len2 * len2) / (2 * len0 * len1));
    default:
        return 0; 
    }
}

void Geometry::Triangle::reorder_points(const bool cw)
{
    if (cw)
    {
        if (!is_cw())
        {
            std::swap(_vecs[1], _vecs[2]);
        }
    }
    else
    {
        if (is_cw())
        {
            std::swap(_vecs[1], _vecs[2]);
        }
    }
}

bool Geometry::Triangle::is_cw() const
{
    return Geometry::is_on_left(_vecs[2], _vecs[1], _vecs[0]);
}

Geometry::Point &Geometry::Triangle::operator[](const size_t index)
{
    assert(index <= 2);
    return _vecs[index];
}

const Geometry::Point &Geometry::Triangle::operator[](const size_t index) const
{
    assert(index <= 2);
    return _vecs[index];
}

Geometry::Triangle &Geometry::Triangle::operator=(const Geometry::Triangle &triangle)
{
    if (this != &triangle)
    {
        Geometry::GeometryObject::operator=(triangle);
        _vecs[0] = triangle._vecs[0];
        _vecs[1] = triangle._vecs[1];
        _vecs[2] = triangle._vecs[2];
    }
    return *this;
}

Geometry::Triangle Geometry::Triangle::operator+(const Geometry::Point &point) const
{
    Geometry::Triangle triangle(*this);
    triangle._vecs[0] += point;
    triangle._vecs[1] += point;
    triangle._vecs[2] += point;
    return triangle;
}

Geometry::Triangle Geometry::Triangle::operator-(const Geometry::Point &point) const
{
    Geometry::Triangle triangle(*this);
    triangle._vecs[0] -= point;
    triangle._vecs[1] -= point;
    triangle._vecs[2] -= point;
    return triangle;
}

void Geometry::Triangle::operator+=(const Geometry::Point &point)
{
    _vecs[0] += point;
    _vecs[1] += point;
    _vecs[2] += point;
}

void Geometry::Triangle::operator-=(const Geometry::Point &point)
{
    _vecs[0] -= point;
    _vecs[1] -= point;
    _vecs[2] -= point;
}

void Geometry::Triangle::transform(const double a, const double b, const double c, const double d, const double e, const double f)
{
    _vecs[0].transform(a, b, c, d, e, f);
    _vecs[1].transform(a, b, c, d, e, f);
    _vecs[2].transform(a, b, c, d, e, f);
}

void Geometry::Triangle::transform(const double mat[6])
{
    _vecs[0].transform(mat);
    _vecs[1].transform(mat);
    _vecs[2].transform(mat);
}

void Geometry::Triangle::translate(const double tx, const double ty)
{
    _vecs[0].translate(tx, ty);
    _vecs[1].translate(tx, ty);
    _vecs[2].translate(tx, ty);
}

void Geometry::Triangle::rotate(const double x, const double y, const double rad)
{
    _vecs[0].rotate(x, y, rad);
    _vecs[1].rotate(x, y, rad);
    _vecs[2].rotate(x, y, rad);
}

void Geometry::Triangle::scale(const double x, const double y, const double k)
{
    _vecs[0].scale(x, y, k);
    _vecs[1].scale(x, y, k);
    _vecs[2].scale(x, y, k);
}

Geometry::Type Geometry::Triangle::type() const
{
    return Geometry::Type::TRIANGLE;
}

Geometry::Polygon Geometry::Triangle::convex_hull() const
{
    if (empty())
    {
        return Geometry::Polygon();
    }
    else
    {
        return Geometry::Polygon({_vecs[0], _vecs[1], _vecs[2], _vecs[0]});
    }
}

Geometry::AABBRect Geometry::Triangle::bounding_rect() const
{
    if (empty())
    {
        return Geometry::AABBRect();
    }

    const double left = std::min(_vecs[0].x, std::min(_vecs[1].x, _vecs[2].x));
    const double right = std::max(_vecs[0].x, std::max(_vecs[1].x, _vecs[2].x));
    const double top = std::max(_vecs[0].y, std::max(_vecs[1].y, _vecs[2].y));
    const double bottom = std::min(_vecs[0].y, std::min(_vecs[1].y, _vecs[2].y));
    return Geometry::AABBRect(left, top, right, bottom);
}

Geometry::Polygon Geometry::Triangle::mini_bounding_rect() const
{
    if (empty())
    {
        return Geometry::Polygon();
    }

    double cs, area = DBL_MAX;
    Geometry::AABBRect rect, temp;
    for (size_t i = 0; i < 3; ++i)
    {
        Geometry::Triangle triangle(*this);
        cs = (triangle[i].x * triangle[i < 2 ? i + 1 : 0].y - triangle[i < 2 ? i + 1 : 0].x * triangle[i].y)
            / (triangle[i < 2 ? i + 1 : 0].length() * triangle[i].length());
        triangle.rotate(triangle[i].x, triangle[i].y, std::acos(cs));
        temp = triangle.bounding_rect();
        if (temp.area() < area)
        {
            rect = temp;
            area = temp.area();
            rect.rotate(triangle[i].x, triangle[i].y, -std::acos(cs));
        }
    }
    return rect;
}

Geometry::Point Geometry::Triangle::inner_circle_center() const
{
    const double a = Geometry::distance(_vecs[1], _vecs[2]);
    const double b = Geometry::distance(_vecs[0], _vecs[2]);
    const double c = Geometry::distance(_vecs[0], _vecs[1]);
    return (_vecs[0] * a + _vecs[1] * b + _vecs[2] * c) / (a + b + c);
}

double Geometry::Triangle::inner_circle_radius() const
{
    const double a = Geometry::distance(_vecs[1], _vecs[2]);
    const double b = Geometry::distance(_vecs[0], _vecs[2]);
    const double c = Geometry::distance(_vecs[0], _vecs[1]);
    const double p = (a + b + c) / 2;
    return std::sqrt((p - a) * (p - b) * (p - c) / p);
}