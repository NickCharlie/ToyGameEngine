#include <cassert>
#include <algorithm>
#include <functional>
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Polygon.hpp"


using namespace ToyGameEngine::Math;

Geometry::Rectangle::Rectangle()
{

}

Geometry::Rectangle::Rectangle(const double x, const double y, const double w, const double h)
{
    assert(w >= 0 && h >= 0);
    _points[0].x = _points[3].x = x - w / 2;
    _points[1].x = _points[2].x = x + w / 2;
    _points[0].y = _points[1].y = y + h / 2;
    _points[2].y = _points[3].y = y - h / 2;
}

Geometry::Rectangle::Rectangle(const Point &point0, const Point &point1)
{
    _points[0] = point0;
    _points[2] = point1;
    _points[1].x = point1.x;
    _points[1].y = point0.y;
    _points[3].x = point0.x;
    _points[3].y = point1.y;
}

Geometry::Rectangle::Rectangle(const Rectangle &rect)
    : _points(rect._points)
{

}

Geometry::Rectangle::Rectangle(const Point &center, const double w, const double h)
{
    assert(w >= 0 && h >= 0);
    _points[0].x = _points[3].x = center.x - w / 2;
    _points[1].x = _points[2].x = center.x + w / 2;
    _points[0].y = _points[1].y = center.y + h / 2;
    _points[2].y = _points[3].y = center.y - h / 2;
}

Geometry::Rectangle &Geometry::Rectangle::operator=(const Rectangle &rect)
{
    if (this != &rect)
    {
        _points = rect._points;
    }
    return *this;
}

Geometry::Point Geometry::Rectangle::center() const
{
    return (_points[0] + _points[2]) / 2;
}

const Geometry::Point &Geometry::Rectangle::operator[](const size_t index) const
{
    assert(index < 4);
    return _points[index];
}

bool Geometry::Rectangle::empty() const
{
    return _points[0] == _points[1] || _points[1] == _points[2];
}

double Geometry::Rectangle::length() const
{
    return (Geometry::distance(_points[0], _points[1]) + Geometry::distance(_points[1], _points[2])) * 2;
}

void Geometry::Rectangle::clear()
{
    _points[0].clear();
    _points[1].clear();
    _points[2].clear();
    _points[3].clear();
}

Geometry::Rectangle *Geometry::Rectangle::clone() const
{
    return new Geometry::Rectangle(*this);
}

double Geometry::Rectangle::area() const
{
    return Geometry::distance(_points[0], _points[1]) * Geometry::distance(_points[1], _points[2]);
}

double Geometry::Rectangle::width() const
{
    return Geometry::distance(_points[0], _points[1]);
}

double Geometry::Rectangle::height() const
{
    return Geometry::distance(_points[1], _points[2]);
}

void Geometry::Rectangle::transform(const double a, const double b, const double c, const double d, const double e, const double f)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point) {point.transform(a,b,c,d,e,f);});
}

void Geometry::Rectangle::transform(const double mat[6])
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point) {point.transform(mat);});
}

void Geometry::Rectangle::translate(const double tx, const double ty)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point) {point.translate(tx, ty);});
}

void Geometry::Rectangle::rotate(const double x, const double y, const double rad)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point) {point.rotate(x, y, rad);});
}

void Geometry::Rectangle::scale(const double x, const double y, const double k)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point) {point.scale(x, y, k);});
}

Geometry::Type Geometry::Rectangle::type() const
{
    return Geometry::Type::RECTANGLE;
}

Geometry::Polygon Geometry::Rectangle::convex_hull() const
{
    return Geometry::Polygon({_points[0], _points[1], _points[2], _points[3], _points[0]});
}

Geometry::AABBRect Geometry::Rectangle::bounding_rect() const
{
    double x0 = DBL_MAX, y0 = DBL_MAX, x1 = (-FLT_MAX), y1 = (-FLT_MAX);
    for (const Point &point : _points)
    {
        x0 = std::min(x0, point.x);
        y0 = std::min(y0, point.y);
        x1 = std::max(x1, point.x);
        y1 = std::max(y1, point.y);
    }
    return Geometry::AABBRect(x0, y1, x1, y0);
}

Geometry::Polygon Geometry::Rectangle::mini_bounding_rect() const
{
    return Geometry::Polygon({_points[0], _points[1], _points[2], _points[3], _points[0]});
}

Geometry::Point Geometry::Rectangle::average_point() const
{
    return (_points[0] + _points[2]) / 2;
}

std::array<Geometry::Point, 4>::const_iterator Geometry::Rectangle::begin() const
{
    return _points.begin();
}

std::array<Geometry::Point, 4>::const_iterator Geometry::Rectangle::cbegin() const
{
    return _points.cbegin();
}

std::array<Geometry::Point, 4>::const_iterator Geometry::Rectangle::end() const
{
    return _points.end();
}

std::array<Geometry::Point, 4>::const_iterator Geometry::Rectangle::cend() const
{
    return _points.cend();
}

std::array<Geometry::Point, 4>::const_reverse_iterator Geometry::Rectangle::rbegin() const
{
    return _points.rbegin();
}

std::array<Geometry::Point, 4>::const_reverse_iterator Geometry::Rectangle::crbegin() const
{
    return _points.crbegin();
}

std::array<Geometry::Point, 4>::const_reverse_iterator Geometry::Rectangle::rend() const
{
    return _points.rend();
}

std::array<Geometry::Point, 4>::const_reverse_iterator Geometry::Rectangle::crend() const
{
    return _points.crend();
}

std::array<Geometry::Point, 4>::const_iterator Geometry::Rectangle::find(const Geometry::Point &point) const
{
    return std::find(_points.cbegin(), _points.cend(), point);
}

Geometry::Rectangle Geometry::Rectangle::operator+(const Geometry::Point &point) const
{
    Geometry::Rectangle rect(*this);
    rect._points[0] += point;
    rect._points[1] += point;
    rect._points[2] += point;
    rect._points[3] += point;
    return rect;
}

Geometry::Rectangle Geometry::Rectangle::operator-(const Geometry::Point &point) const
{
    Geometry::Rectangle rect(*this);
    rect._points[0] -= point;
    rect._points[1] -= point;
    rect._points[2] -= point;
    rect._points[3] -= point;
    return rect;
}

void Geometry::Rectangle::operator+=(const Geometry::Point &point)
{
    _points[0] += point;
    _points[1] += point;
    _points[2] += point;
    _points[3] += point;
}

void Geometry::Rectangle::operator-=(const Geometry::Point &point)
{
    _points[0] -= point;
    _points[1] -= point;
    _points[2] -= point;
    _points[3] -= point;
}

size_t Geometry::Rectangle::next_point_index(const size_t index) const
{
    return index < 3 ? index + 1 : 0;
}

const Geometry::Point &Geometry::Rectangle::next_point(const size_t index) const
{
    return _points[index < 3 ? index + 1 : 0];
}

size_t Geometry::Rectangle::last_point_index(const size_t index) const
{
    return index > 0 ? index - 1 : 3;
}

const Geometry::Point &Geometry::Rectangle::last_point(const size_t index) const
{
    return _points[index > 0 ? index - 1 : 3];
}

size_t Geometry::Rectangle::index(const double x, const double y) const
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (_points[i].x == x && _points[i].y == y)
        {
            return i;
        }
    }
    return SIZE_MAX;
}

size_t Geometry::Rectangle::index(const Point &point) const
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (_points[i] == point)
        {
            return i;
        }
    }
    return SIZE_MAX;
}

double Geometry::Rectangle::outer_circle_radius() const
{
    return Geometry::distance(_points[0], _points[2]) / 2;
}