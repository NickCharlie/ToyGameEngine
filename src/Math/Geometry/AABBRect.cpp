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
    _points.assign({Geometry::Point(0, 0), Geometry::Point(0, 0), Geometry::Point(0, 0), Geometry::Point(0, 0), Geometry::Point(0, 0)});
}

Geometry::AABBRect::AABBRect(const double x0, const double y0, const double x1, const double y1)
{
    if (x0 < x1)
    {
        if (y0 > y1)
        {   
            _points.assign({Geometry::Point(x0, y0), Geometry::Point(x1, y0), Geometry::Point(x1, y1), Geometry::Point(x0, y1), Geometry::Point(x0, y0)});
        }
        else
        {
            _points.assign({Geometry::Point(x0, y1), Geometry::Point(x1, y1), Geometry::Point(x1, y0), Geometry::Point(x0, y0), Geometry::Point(x0, y1)});
        }
    }
    else
    {
        if (y0 > y1)
        {   
            _points.assign({Geometry::Point(x1, y0), Geometry::Point(x0, y0), Geometry::Point(x0, y1), Geometry::Point(x1, y1), Geometry::Point(x1, y0)});
        }
        else
        {
            _points.assign({Geometry::Point(x1, y1), Geometry::Point(x0, y1), Geometry::Point(x0, y0), Geometry::Point(x1, y0), Geometry::Point(x1, y1)});
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
            _points.assign({Geometry::Point(x0, y0), Geometry::Point(x1, y0), Geometry::Point(x1, y1), Geometry::Point(x0, y1), Geometry::Point(x0, y0)});
        }
        else
        {
            _points.assign({Geometry::Point(x0, y1), Geometry::Point(x1, y1), Geometry::Point(x1, y0), Geometry::Point(x0, y0), Geometry::Point(x0, y1)});
        }
    }
    else
    {
        if (y0 > y1)
        {   
            _points.assign({Geometry::Point(x1, y0), Geometry::Point(x0, y0), Geometry::Point(x0, y1), Geometry::Point(x1, y1), Geometry::Point(x1, y0)});
        }
        else
        {
            _points.assign({Geometry::Point(x1, y1), Geometry::Point(x0, y1), Geometry::Point(x0, y0), Geometry::Point(x1, y0), Geometry::Point(x1, y1)});
        }
    }
}

Geometry::AABBRect::AABBRect(const Geometry::AABBRect &rect)
    : Geometry::GeometryObject(rect), _points(rect._points)
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
    return _points[2].x;
}

double Geometry::AABBRect::bottom() const
{
    return _points[2].y;
}

void Geometry::AABBRect::set_left(const double value)
{
    _points.front().x = value;
    _points[3].x = value;
    _points.back().x = value;
}

void Geometry::AABBRect::set_top(const double value)
{
    _points.front().y = value;
    _points[1].y = value;
    _points.back().y = value;
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
        Geometry::GeometryObject::operator=(rect);
        _points = rect._points;
    }
    return *this;
}

Geometry::Point Geometry::AABBRect::center() const
{
    return (_points[0] + _points[2]) / 2;
}

const Geometry::Point &Geometry::AABBRect::operator[](const size_t index) const
{
    assert(!_points.empty() && index <= 4);
    return _points[index];
}

bool Geometry::AABBRect::empty() const
{
    return _points.empty();
}

double Geometry::AABBRect::length() const
{
    double reuslt = 0;
    for (size_t i = 1, count = _points.size(); i < count; ++i)
    {
        reuslt += Geometry::distance(_points[i], _points[i-1]);
    }
    return reuslt;
}

void Geometry::AABBRect::clear()
{
    _points.clear();
}

Geometry::AABBRect *Geometry::AABBRect::clone() const
{
    return new Geometry::AABBRect(*this);
}

double Geometry::AABBRect::area() const
{
    if (empty())
    {
        return 0;
    }
    else
    {
        return Geometry::distance(_points[0], _points[1]) * Geometry::distance(_points[1], _points[2]);
    }
}

double Geometry::AABBRect::width() const
{
    if (!_points.empty())
    {
        return Geometry::distance(_points.front(), _points[1]);
    }
    else
    {
        return 0;
    }
}

double Geometry::AABBRect::height() const
{
    if (!_points.empty())
    {
        return Geometry::distance(_points[1], _points[2]);
    }
    else
    {
        return 0;
    }
}

void Geometry::AABBRect::set_width(const double value)
{
    const double d = (value - width()) / 2;
    _points[0].x = _points[3].x = _points[4].x = _points[0].x - d;
    _points[1].x = _points[2].x = _points[1].x + d;
}

void Geometry::AABBRect::set_height(const double value)
{
    const double d = (value - height()) / 2;
    _points[0].y = _points[1].y = _points[4].y = _points[0].y + d;
    _points[2].x = _points[3].x = _points[2].x + d;
}

void Geometry::AABBRect::transform(const double a, const double b, const double c, const double d, const double e, const double f)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point){point.transform(a,b,c,d,e,f);});
    if (_points[0].x > _points[1].x)
    {
        std::swap(_points[0], _points[1]);
        std::swap(_points[2], _points[3]);
    }
    if (_points[0].y < _points[2].y)
    {
        std::swap(_points[0], _points[3]);
        std::swap(_points[1], _points[2]);
    }
    _points[4] = _points[0];
}

void Geometry::AABBRect::transform(const double mat[6])
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point){point.transform(mat);});
    if (_points[0].x > _points[1].x)
    {
        std::swap(_points[0], _points[1]);
        std::swap(_points[2], _points[3]);
    }
    if (_points[0].y < _points[2].y)
    {
        std::swap(_points[0], _points[3]);
        std::swap(_points[1], _points[2]);
    }
    _points[4] = _points[0];
}

void Geometry::AABBRect::translate(const double tx, const double ty)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point){point.translate(tx, ty);});
}

void Geometry::AABBRect::rotate(const double x, const double y, const double rad)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point){point.rotate(x, y, rad);});
}

void Geometry::AABBRect::scale(const double x, const double y, const double k)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point){point.scale(x, y, k);});
}

Geometry::Type Geometry::AABBRect::type() const
{
    return Geometry::Type::AABBRECT;
}

Geometry::Polygon Geometry::AABBRect::convex_hull() const
{
    return Geometry::Polygon(_points.cbegin(), _points.cend());
}

Geometry::AABBRect Geometry::AABBRect::bounding_rect() const
{
    if (_points.empty())
    {
        return Geometry::AABBRect();
    }
    double x0 = DBL_MAX, y0 = DBL_MAX, x1 = (-FLT_MAX), y1 = (-FLT_MAX);
    for (const Geometry::Point &point : _points)
    {
        x0 = std::min(x0, point.x);
        y0 = std::min(y0, point.y);
        x1 = std::max(x1, point.x);
        y1 = std::max(y1, point.y);
    }
    return Geometry::AABBRect(x0, y0, x1, y1);
}

Geometry::Polygon Geometry::AABBRect::mini_bounding_rect() const
{
    return *this;
}

std::vector<Geometry::Point>::const_iterator Geometry::AABBRect::begin() const
{
    return _points.cbegin();
}

std::vector<Geometry::Point>::const_iterator Geometry::AABBRect::cbegin() const
{
    return _points.cbegin();
}

std::vector<Geometry::Point>::const_iterator Geometry::AABBRect::end() const
{
    return _points.cend();
}

std::vector<Geometry::Point>::const_iterator Geometry::AABBRect::cend() const
{
    return _points.cend();
}

std::vector<Geometry::Point>::const_reverse_iterator Geometry::AABBRect::rbegin() const
{
    return _points.crbegin();
}

std::vector<Geometry::Point>::const_reverse_iterator Geometry::AABBRect::crbegin() const
{
    return _points.crbegin();
}

std::vector<Geometry::Point>::const_reverse_iterator Geometry::AABBRect::rend() const
{
    return _points.crend();
}

std::vector<Geometry::Point>::const_reverse_iterator Geometry::AABBRect::crend() const
{
    return _points.crend();
}

std::vector<Geometry::Point>::const_iterator Geometry::AABBRect::find(const Geometry::Point &point) const
{
    return std::find(_points.cbegin(), _points.cend(), point);
}

Geometry::AABBRect Geometry::AABBRect::operator+(const Point &point) const
{
    return Geometry::AABBRect(_points[0].x + point.x, _points[0].y + point.y,
                    _points[2].x + point.x, _points[2].y + point.y);
}

Geometry::AABBRect Geometry::AABBRect::operator-(const Point &point) const
{
    return Geometry::AABBRect(_points[0].x - point.x, _points[0].y - point.y,
                    _points[2].x - point.x, _points[2].y - point.y);
}

void Geometry::AABBRect::operator+=(const Point &point)
{
    for (Geometry::Point &p : _points)
    {
        p += point;
    }
}

void Geometry::AABBRect::operator-=(const Geometry::Point &point)
{
    for (Geometry::Point &p : _points)
    {
        p -= point;
    }
}