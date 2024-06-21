#include <cmath>
#include <cassert>
#include "Math/Geometry/Bezier.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Polygon.hpp"


using namespace ToyGameEngine::Math;

Geometry::Bezier::Bezier(const size_t n)
    : _order(n)
{

}

Geometry::Bezier::Bezier(const Geometry::Bezier &bezier)
    :  Geometry::Polyline(bezier), _order(bezier._order), _shape(bezier._shape)
{

}

Geometry::Bezier::Bezier(std::vector<Geometry::Point>::const_iterator begin, std::vector<Geometry::Point>::const_iterator end, const size_t n)
    : Geometry::Polyline(begin, end), _order(n)
{
    update_shape();
}

Geometry::Bezier::Bezier(const std::initializer_list<Geometry::Point> &points, const size_t n)
    : Geometry::Polyline(points), _order(n)
{
    update_shape();
}

size_t Geometry::Bezier::order() const
{
    return _order;
}

const Geometry::Polyline &Geometry::Bezier::shape() const
{
    return _shape;
}

void Geometry::Bezier::update_shape(const double step)
{
    assert(0 < step && step < 1);
    _shape.clear();
    std::vector<int> temp(1, 1), nums(_order + 1, 1);
    for (size_t i = 1; i <= _order; ++i)
    {
        for (size_t j = 1; j < i; ++j)
        {
            nums[j] = temp[j - 1] + temp[j]; 
        }
        temp.assign(nums.begin(), nums.begin() + i + 1);
    }

    double t = 0;
    Geometry::Point point;
    for (size_t i = 0, end = _points.size() - _order; i < end; i += _order)
    {
        _shape.append(_points[i]);
        t = 0;
        while (t <= 1)
        {
            point.clear();
            for (size_t j = 0; j <= _order; ++j)
            {
                point += (_points[j + i] * (nums[j] * std::pow(1 - t, _order - j) * std::pow(t, j))); 
            }
            _shape.append(point);
            t += step;
        }
    }
    _shape.append(_points.back());
}

void Geometry::Bezier::append_shape(const double step)
{
    assert(0 < step && step < 1);
    if ((_points.size() - 1) % _order > 0)
    {
        return;
    }

    std::vector<int> temp(1, 1), nums(_order + 1, 1);
    for (size_t i = 1; i <= _order; ++i)
    {
        for (size_t j = 1; j < i; ++j)
        {
            nums[j] = temp[j - 1] + temp[j]; 
        }
        temp.assign(nums.begin(), nums.begin() + i + 1);
    }

    double t = 0;
    Geometry::Point point;
    const size_t i = _points.size() - _order - 1;
    while (t <= 1)
    {
        point.clear();
        for (size_t j = 0; j <= _order; ++j)
        {
            point += (_points[j + i] * (nums[j] * std::pow(1 - t, _order - j) * std::pow(t, j))); 
        }
        _shape.append(point);
        t += step;
    }
    _shape.append(_points.back());
}

double Geometry::Bezier::length() const
{
    return _shape.length();
}

void Geometry::Bezier::clear()
{
    _shape.clear();
    Polyline::clear();
}

Geometry::Bezier *Geometry::Bezier::clone() const
{
    return new Geometry::Bezier(*this);
}

Geometry::Bezier &Geometry::Bezier::operator=(const Geometry::Bezier &bezier)
{
    if (this != &bezier)
    {
        Polyline::operator=(bezier);
        _shape = bezier._shape;
    }
    return *this;
}

void Geometry::Bezier::transform(const double a, const double b, const double c, const double d, const double e, const double f)
{
    Polyline::transform(a, b, c, d, e, f);
    _shape.transform(a, b, c, d, e, f);
}

void Geometry::Bezier::transform(const double mat[6])
{
    Polyline::transform(mat);
    _shape.transform(mat);
}

void Geometry::Bezier::translate(const double tx, const double ty)
{
    Polyline::translate(tx, ty);
    _shape.translate(tx, ty);
}

void Geometry::Bezier::rotate(const double x, const double y, const double rad)
{
    Polyline::rotate(x, y, rad);
    _shape.rotate(x, y, rad);
}

void Geometry::Bezier::scale(const double x, const double y, const double k)
{
    Polyline::scale(x, y, k);
    _shape.scale(x, y, k);
}

Geometry::Type Geometry::Bezier::type() const
{
    return Geometry::Type::BEZIER;
}

Geometry::Polygon Geometry::Bezier::convex_hull() const
{
    return _shape.convex_hull();
}

Geometry::AABBRect Geometry::Bezier::bounding_rect() const
{
    return _shape.bounding_rect();
}

Geometry::Polygon Geometry::Bezier::mini_bounding_rect() const
{
    return _shape.mini_bounding_rect();
}