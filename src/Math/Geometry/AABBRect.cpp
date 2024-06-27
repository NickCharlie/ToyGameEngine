#include <cmath>
#include <cassert>
#include <utility>
#include <algorithm>
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Polygon.hpp"


using namespace ToyGameEngine::Math;

Geometry::AABBRect::AABBRect()
{

}

Geometry::AABBRect::AABBRect(const double x0, const double y0, const double x1, const double y1)
{
    if (x0 < x1)
    {
        if (y0 > y1)
        {
            _points[0].x = x0, _points[0].y = y0;
            _points[1].x = x1, _points[1].y = y0;
            _points[2].x = x1, _points[2].y = y1;
            _points[3].x = x0, _points[3].y = y1;
        }
        else
        {
            _points[0].x = x0, _points[0].y = y1;
            _points[1].x = x1, _points[1].y = y1;
            _points[2].x = x1, _points[2].y = y0;
            _points[3].x = x0, _points[3].y = y0;
        }
    }
    else
    {
        if (y0 > y1)
        {
            _points[0].x = x1, _points[0].y = y0;
            _points[1].x = x0, _points[1].y = y0;
            _points[2].x = x0, _points[2].y = y1;
            _points[3].x = x1, _points[3].y = y1;
        }
        else
        {
            _points[0].x = x1, _points[0].y = y1;
            _points[1].x = x0, _points[1].y = y1;
            _points[2].x = x0, _points[2].y = y0;
            _points[3].x = x1, _points[3].y = y0;
        }
    }
}

Geometry::AABBRect::AABBRect(const Geometry::Point &point0, const Geometry::Point &point1)
{
    const double x0 = point0.x, y0 = point0.y, x1 = point1.x, y1 = point1.y;
    if (x0 < x1)
    {
        if (y0 > y1)
        {
            _points[0].x = x0, _points[0].y = y0;
            _points[1].x = x1, _points[1].y = y0;
            _points[2].x = x1, _points[2].y = y1;
            _points[3].x = x0, _points[3].y = y1;
        }
        else
        {
            _points[0].x = x0, _points[0].y = y1;
            _points[1].x = x1, _points[1].y = y1;
            _points[2].x = x1, _points[2].y = y0;
            _points[3].x = x0, _points[3].y = y0;
        }
    }
    else
    {
        if (y0 > y1)
        {
            _points[0].x = x1, _points[0].y = y0;
            _points[1].x = x0, _points[1].y = y0;
            _points[2].x = x0, _points[2].y = y1;
            _points[3].x = x1, _points[3].y = y1;
        }
        else
        {
            _points[0].x = x1, _points[0].y = y1;
            _points[1].x = x0, _points[1].y = y1;
            _points[2].x = x0, _points[2].y = y0;
            _points[3].x = x1, _points[3].y = y0;
        }
    }
}

Geometry::AABBRect::AABBRect(const Geometry::AABBRect &rect)
    : Geometry::Rectangle(rect)
{

}

double Geometry::AABBRect::left() const
{
    return _points.front().x;
}

double Geometry::AABBRect::top() const
{
    return _points.front().y;
}

double Geometry::AABBRect::right() const
{
    return _points[1].x;
}

double Geometry::AABBRect::bottom() const
{
    return _points.back().y;
}

void Geometry::AABBRect::set_left(const double value)
{
    _points.front().x = value;
    _points.back().x = value;
}

void Geometry::AABBRect::set_top(const double value)
{
    _points.front().y = value;
    _points[1].y = value;
}

void Geometry::AABBRect::set_right(const double value)
{
    _points[1].x = value;
    _points[2].x = value;
}

void Geometry::AABBRect::set_bottom(const double value)
{
    _points[2].y = value;
    _points[3].y = value;
}

Geometry::AABBRect &Geometry::AABBRect::operator=(const Geometry::AABBRect &rect)
{
    if (this != &rect)
    {
        Geometry::Rectangle::operator=(rect);
    }
    return *this;
}

Geometry::AABBRect *Geometry::AABBRect::clone() const
{
    return new Geometry::AABBRect(*this);
}

void Geometry::AABBRect::set_width(const double value)
{
    const double d = (value - width()) / 2;
    _points[0].x = _points[3].x = _points[0].x - d;
    _points[1].x = _points[2].x = _points[1].x + d;
}

void Geometry::AABBRect::set_height(const double value)
{
    const double d = (value - height()) / 2;
    _points[0].y = _points[1].y = _points[0].y + d;
    _points[2].x = _points[3].x = _points[2].x + d;
}

Geometry::Type Geometry::AABBRect::type() const
{
    return Geometry::Type::AABBRECT;
}