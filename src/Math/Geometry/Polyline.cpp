#include <cmath>
#include <cassert>
#include <utility>
#include <algorithm>
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Polygon.hpp"


using namespace ToyGameEngine::Math;

Geometry::Polyline::Polyline()
{

}

Geometry::Polyline::Polyline(const Geometry::Polyline &polyline)
    : Geometry::GeometryObject(polyline), _points(polyline._points)
{

}

Geometry::Polyline::Polyline(std::vector<Geometry::Point>::const_iterator begin, std::vector<Geometry::Point>::const_iterator end)
{
    _points.emplace_back(*begin);
    while (++begin != end)
    {
        if (*begin != _points.back())
        {
            _points.emplace_back(*begin);
        }
    }
}

Geometry::Polyline::Polyline(std::array<Point, 4>::const_iterator begin, std::array<Point, 4>::const_iterator end)
{
    while (begin != end)
    {
        _points.emplace_back(*(begin++));
    }
}

Geometry::Polyline::Polyline(const std::initializer_list<Geometry::Point> &points)
{
    _points.emplace_back(*points.begin());
    for (const Geometry::Point& point : points)
    {
        if (point != _points.back())
        {
            _points.emplace_back(point);
        }
    }
}

size_t Geometry::Polyline::size() const
{
    return _points.size();
}

bool Geometry::Polyline::empty() const
{
    return _points.empty();
}

double Geometry::Polyline::length() const
{
    double reuslt = 0;
    for (size_t i = 1, count = _points.size(); i < count; ++i)
    {
        reuslt += Geometry::distance(_points[i], _points[i-1]);
    }
    return reuslt;
}

void Geometry::Polyline::clear()
{
    _points.clear();
}

Geometry::Polyline *Geometry::Polyline::clone() const
{
    return new Geometry::Polyline(*this);
}

bool Geometry::Polyline::is_self_intersected() const
{
    if (_points.size() < 4)
    {
        return false;
    }

    Geometry::Point point;
    for (size_t j = 2, count = _points.size() - 2; j < count; ++j)
    {
        if (Geometry::is_intersected(_points[0], _points[1], _points[j], _points[j + 1], point))
        {
            return true;
        }
    }
    for (size_t i = 1, count = _points.size() - 1; i < count; ++i)
    {
        for (size_t j = i + 2; j < count; ++j)
        {
            if (Geometry::is_intersected(_points[i], _points[i + 1], _points[j], _points[j + 1], point))
            {
                return true;
            }
        }
    }
    return false;
}

Geometry::Point &Geometry::Polyline::operator[](const size_t index)
{
    assert(index < _points.size());
    return _points[index];
}

const Geometry::Point &Geometry::Polyline::operator[](const size_t index) const
{
    assert(index < _points.size());
    return _points[index];
}

Geometry::Polyline &Geometry::Polyline::operator=(const Geometry::Polyline &polyline)
{
    if (this != &polyline)
    {
        Geometry::GeometryObject::operator=(polyline);
        _points = polyline._points;
    }
    return *this;
}

Geometry::Polyline Geometry::Polyline::operator+(const Geometry::Point &point) const
{
    std::vector<Geometry::Point> temp(_points);
    for (Geometry::Point &p : temp)
    {
        p += point;
    }
    return Geometry::Polyline(temp.cbegin(), temp.cend());
}

Geometry::Polyline Geometry::Polyline::operator-(const Geometry::Point &point) const
{
    std::vector<Geometry::Point> temp(_points);
    for (Geometry::Point &p : temp)
    {
        p -= point;
    }
    return Geometry::Polyline(temp.cbegin(), temp.cend());
}

void Geometry::Polyline::operator+=(const Geometry::Point &point)
{
    for (Geometry::Point &p : _points)
    {
        p += point;
    }
}

void Geometry::Polyline::operator-=(const Geometry::Point &point)
{
    for (Geometry::Point &p : _points)
    {
        p -= point;
    }
}

void Geometry::Polyline::append(const Geometry::Point &point)
{
    if (_points.empty() || _points.back() != point)
    {
        _points.emplace_back(point);
    }
}

void Geometry::Polyline::append(const Geometry::Polyline &polyline)
{
    if (_points.empty() ||  _points.back() != polyline._points.front())
    {
        _points.insert(_points.cend(), polyline._points.cbegin(), polyline._points.cend());
    }
    else
    {
        _points.insert(_points.cend(), polyline._points.cbegin() + 1, polyline._points.cend());
    }
}

void Geometry::Polyline::append(std::vector<Geometry::Point>::const_iterator begin, std::vector<Geometry::Point>::const_iterator end)
{
    if (_points.empty() || _points.back() != *begin)
    {
        _points.insert(_points.cend(), begin, end);
    }
    else
    {
        _points.insert(_points.cend(), begin + 1, end);
    }
}

void Geometry::Polyline::insert(const size_t index, const Geometry::Point &point)
{
    assert(index < _points.size());
    if (_points[index] == point || (index > 0 && _points[index - 1] == point))
    {
        return;
    }
    else
    {
        _points.insert(_points.cbegin() + index, point);
    }
}

void Geometry::Polyline::insert(const size_t index, const Geometry::Polyline &polyline)
{
    assert(index < _points.size());
    if (polyline.empty())
    {
        return;
    }
    int i = (index > 0 && _points[index - 1] == polyline._points.front()), j = _points[index] == polyline._points.back();
    _points.insert(_points.cbegin() + index, polyline._points.cbegin() + i, polyline._points.cend() - j);
}

void Geometry::Polyline::insert(const size_t index, std::vector<Geometry::Point>::const_iterator begin, std::vector<Geometry::Point>::const_iterator end)
{
    assert(index < _points.size());
    int i = (index > 0 && _points[index] == *begin);
    _points.insert(_points.end(), begin + i, end);
    const size_t len = std::distance(begin, end);
    if (_points[index + len] == _points[index + len + 1])
    {
        _points.erase(_points.begin() + index + len + 1);
    }
}

void Geometry::Polyline::remove(const size_t index)
{
    assert(index < _points.size());
    _points.erase(_points.begin() + index);
}

void Geometry::Polyline::remove(const size_t index, const size_t count)
{
    assert(index < _points.size());
    _points.erase(_points.begin() + index, _points.begin() + index + count);
}

Geometry::Point Geometry::Polyline::pop(const size_t index)
{
    assert(index < _points.size());
    Geometry::Point point(_points[index]);
    _points.erase(_points.begin() + index);
    return point;
}

void Geometry::Polyline::flip()
{
    std::reverse(_points.begin(), _points.end());
}

Geometry::Point &Geometry::Polyline::front()
{
    assert(!empty());
    return _points.front();
}

const Geometry::Point &Geometry::Polyline::front() const
{
    assert(!empty());
    return _points.front();
}

Geometry::Point &Geometry::Polyline::back()
{
    assert(!empty());
    return _points.back();
}

const Geometry::Point &Geometry::Polyline::back() const
{
    assert(!empty());
    return _points.back();
}

std::vector<Geometry::Point>::iterator Geometry::Polyline::begin()
{
    return _points.begin();
}

std::vector<Geometry::Point>::const_iterator Geometry::Polyline::begin() const
{
    return _points.cbegin();
}

std::vector<Geometry::Point>::const_iterator Geometry::Polyline::cbegin() const
{
    return _points.cbegin();
}

std::vector<Geometry::Point>::iterator Geometry::Polyline::end()
{
    return _points.end();
}

std::vector<Geometry::Point>::const_iterator Geometry::Polyline::end() const
{
    return _points.cend();
}

std::vector<Geometry::Point>::const_iterator Geometry::Polyline::cend() const
{
    return _points.cend();
}

std::vector<Geometry::Point>::reverse_iterator Geometry::Polyline::rbegin()
{
    return _points.rbegin();
}

std::vector<Geometry::Point>::const_reverse_iterator Geometry::Polyline::rbegin() const
{
    return _points.crbegin();
}

std::vector<Geometry::Point>::const_reverse_iterator Geometry::Polyline::crbegin() const
{
    return _points.crbegin();
}

std::vector<Geometry::Point>::reverse_iterator Geometry::Polyline::rend()
{
    return _points.rend();
}

std::vector<Geometry::Point>::const_reverse_iterator Geometry::Polyline::rend() const
{
    return _points.crend();
}

std::vector<Geometry::Point>::const_reverse_iterator Geometry::Polyline::crend() const
{
    return _points.crend();
}

std::vector<Geometry::Point>::iterator Geometry::Polyline::find(const Geometry::Point &point)
{
    return std::find(_points.begin(), _points.end(), point);
}

std::vector<Geometry::Point>::const_iterator Geometry::Polyline::find(const Geometry::Point &point) const
{
    return std::find(_points.cbegin(), _points.cend(), point);
}

void Geometry::Polyline::transform(const double a, const double b, const double c, const double d, const double e, const double f)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point){point.transform(a,b,c,d,e,f);});
}

void Geometry::Polyline::transform(const double mat[6])
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point){point.transform(mat);});
}

void Geometry::Polyline::translate(const double tx, const double ty)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point){point.translate(tx, ty);});
}

void Geometry::Polyline::rotate(const double x, const double y, const double rad)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point){point.rotate(x, y, rad);});
}

void Geometry::Polyline::scale(const double x, const double y, const double k)
{
    std::for_each(_points.begin(), _points.end(), [=](Geometry::Point &point){point.scale(x, y, k);});
}

Geometry::Type Geometry::Polyline::type() const
{
    return Geometry::Type::POLYLINE;
}

Geometry::Polygon Geometry::Polyline::convex_hull() const
{
    std::vector<Geometry::Point> points(_points);
    std::sort(points.begin(), points.end(), [](const Geometry::Point &a, const Geometry::Point &b)
        {return a.y < b.y;});
    const Geometry::Point origin(points.front());
    std::for_each(points.begin(), points.end(), [=](Geometry::Point &p){p -= origin;});
    std::sort(points.begin() + 1, points.end(), [](const Geometry::Point &a, const Geometry::Point &b)
        {
            if (a.x / a.length() != b.x / b.length())
            {
                return a.x / a.length() > b.x / b.length();
            }
            else
            {
                return a.length() < b.length();
            }
        });
    std::for_each(points.begin(), points.end(), [=](Geometry::Point &p){p += origin;});

    std::vector<Geometry::Point> hull(points.begin(), points.begin() + 2);
    size_t count = hull.size(), index = 0;
    Geometry::Vector vec0, vec1;
    std::vector<bool> used(points.size(), false);
    for (size_t i = 2, end = points.size(); i < end; ++i)
    {
        vec0 = hull.back() - hull[count - 2];
        vec1 = vec0 + points[i] - hull.back();
        while (count >= 2 && vec0.x * vec1.y - vec1.x * vec0.y < 0)
        {
            hull.pop_back();
            --count;
            vec0 = hull.back() - hull[count - 2];
            vec1 = vec0 + points[i] - hull.back();
        }
        ++count;
        hull.emplace_back(points[i]);
        used[i] = true;
    }

    for (size_t i = 1; count < 2; ++i)
    {
        if (used[i])
        {
            continue;
        }
        hull.emplace_back(points[points.size() - i]);
        ++count;
        used[points.size() - i] = true;  
    }

    for (size_t i = points.size() - 1; i > 0; --i)   
    {
        if (used[i])
        {
            continue;
        }

        vec0 = hull.back() - hull[count - 2];
        vec1 = vec0 + points[i] - hull.back();
        while (count >= 2 && vec0.x * vec1.y - vec1.x * vec0.y < 0)
        {
            hull.pop_back();
            --count;
            vec0 = hull.back() - hull[count - 2];
            vec1 = vec0 + points[i] - hull.back();
        }
        ++count;
        hull.emplace_back(points[i]);
    }

    vec0 = hull.back() - hull[count - 2];
    vec1 = vec0 + points.front() - hull.back();
    if (count >= 2 && vec0.x * vec1.y - vec0.y * vec1.x < 0)
    {
        hull.pop_back();
    }
    
    hull.emplace_back(points.front());    
    return Geometry::Polygon(hull.cbegin(), hull.cend());
}

Geometry::AABBRect Geometry::Polyline::bounding_rect() const
{
    if (_points.empty())
    {
        return Geometry::AABBRect();
    }

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

Geometry::Polygon Geometry::Polyline::mini_bounding_rect() const
{
    if (_points.empty())
    {
        return Geometry::Polygon();
    }

    double cs, area = DBL_MAX;
    Geometry::AABBRect rect, temp;
    const Geometry::Polygon hull(convex_hull());
    for (size_t i = 1, count = hull.size(); i < count; ++i)
    {
        Geometry::Polygon polygon(hull);
        cs = (polygon[i - 1].x * polygon[i].y - polygon[i].x * polygon[i - 1].y)
            / (polygon[i].length() * polygon[i - 1].length());
        polygon.rotate(polygon[i - 1].x, polygon[i - 1].y, std::acos(cs));
        temp = polygon.bounding_rect();
        if (temp.area() < area)
        {
            rect = temp;
            area = temp.area();
            rect.rotate(polygon[i - 1].x, polygon[i - 1].y, -std::acos(cs));
        }
    }
    return rect;
}