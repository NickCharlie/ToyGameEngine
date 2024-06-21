#include <cmath>
#include <cassert>
#include <algorithm>
#include "Math/Geometry/Line.hpp"
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Polygon.hpp"


using namespace ToyGameEngine::Math;

Geometry::Line::Line()
{

}

Geometry::Line::Line(const double x0, const double y0, const double x1, const double y1)
    : _start_point(x0, y0), _end_point(x1, y1)
{

}

Geometry::Line::Line(const Geometry::Point &start, const Geometry::Point &end)
    : _start_point(start), _end_point(end)
{

}

Geometry::Line::Line(const Geometry::Line &line)
    : Geometry::GeometryObject(line), _start_point(line._start_point), _end_point(line._end_point)
{

}

Geometry::Line &Geometry::Line::operator=(const Geometry::Line &line)
{
    if (this != &line)
    {
        Geometry::GeometryObject::operator=(line);
        _start_point = line._start_point;
        _end_point = line._end_point;
    }
    return *this;
}

Geometry::Line Geometry::Line::operator+(const Geometry::Point &point)
{
    return Geometry::Line(_start_point + point, _end_point + point);
}

Geometry::Line Geometry::Line::operator-(const Geometry::Point &point)
{
    return Geometry::Line(_start_point - point, _end_point - point);
}

void Geometry::Line::operator+=(const Geometry::Point &point)
{
    _start_point += point;
    _end_point += point;
}

void Geometry::Line::operator-=(const Geometry::Point &point)
{
    _start_point -= point;
    _end_point -= point;
}

double Geometry::Line::length() const
{
    return Geometry::distance(_start_point, _end_point);
}

bool Geometry::Line::empty() const
{
    return _start_point == _end_point;
}

void Geometry::Line::clear()
{
    _start_point.clear();
    _end_point.clear();
}

Geometry::Line *Geometry::Line::clone() const
{
    return new Geometry::Line(*this);
}

void Geometry::Line::transform(const double a, const double b, const double c, const double d, const double e, const double f)
{
    _start_point.transform(a,b,c,d,e,f);
    _end_point.transform(a,b,c,d,e,f);
}

void Geometry::Line::transform(const double mat[6])
{
    _start_point.transform(mat);
    _end_point.transform(mat);
}

void Geometry::Line::translate(const double tx, const double ty)
{
    _start_point.translate(tx, ty);
    _end_point.translate(tx, ty);
}

void Geometry::Line::rotate(const double x, const double y, const double rad)
{
    _start_point.rotate(x, y, rad);
    _end_point.rotate(x, y, rad);
}

void Geometry::Line::scale(const double x, const double y, const double k)
{
    _start_point.scale(x, y, k);
    _end_point.scale(x, y, k);
}

Geometry::Type Geometry::Line::type() const
{
    return Geometry::Type::LINE;
}

Geometry::AABBRect Geometry::Line::bounding_rect() const
{
    if (_start_point == _end_point)
    {
        return Geometry::AABBRect();
    }
    else
    {
        return Geometry::AABBRect(std::min(_start_point.x, _end_point.x),
                        std::max(_start_point.y, _end_point.y),
                        std::max(_start_point.x, _end_point.x),
                        std::min(_start_point.y, _end_point.y));
    }
}

Geometry::Polygon Geometry::Line::mini_bounding_rect() const
{
    if (_start_point == _end_point)
    {
        return Geometry::Polygon();
    }
    else
    {
        return Geometry::AABBRect(std::min(_start_point.x, _end_point.x),
                        std::max(_start_point.y, _end_point.y),
                        std::max(_start_point.x, _end_point.x),
                        std::min(_start_point.y, _end_point.y));
    }
}

Geometry::Point &Geometry::Line::front()
{
    return _start_point;
}

const Geometry::Point &Geometry::Line::front() const
{
    return _start_point;
}

Geometry::Point &Geometry::Line::back()
{
    return _end_point;
}

const Geometry::Point &Geometry::Line::back() const
{
    return _end_point;
}