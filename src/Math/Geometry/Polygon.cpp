#include <cmath>
#include <cassert>
#include "Math/Geometry/Polygon.hpp"
#include "Math/Geometry/AABBRect.hpp"


using namespace ToyGameEngine::Math;

Geometry::Polygon::Polygon()
{

}

Geometry::Polygon::Polygon(const Geometry::Polygon &polygon)
    : Geometry::Polyline(polygon)
{

}

Geometry::Polygon::Polygon(std::vector<Geometry::Point>::const_iterator begin, std::vector<Geometry::Point>::const_iterator end)
    : Geometry::Polyline(begin, end)
{
    assert(size() >= 3);
    if (_points.back() != _points.front())
    {
        _points.emplace_back(_points.front());
    }
}

Geometry::Polygon::Polygon(std::array<Point, 4>::const_iterator begin, std::array<Point, 4>::const_iterator end)
    : Geometry::Polyline(begin, end)
{
    _points.emplace_back(_points.front());
}

Geometry::Polygon::Polygon(const std::initializer_list<Geometry::Point> &points)
    : Geometry::Polyline(points)
{
    assert(size() >= 3);
    if (_points.back() != _points.front())
    {
        _points.emplace_back(_points.front());
    }
}

Geometry::Polygon::Polygon(const Geometry::Polyline &polyline)
    : Geometry::Polyline(polyline)
{
    assert(size() >= 3);
    if (_points.back() != _points.front())
    {
        _points.emplace_back(_points.front());
    }
}

Geometry::Polygon::Polygon(const Geometry::AABBRect &rect)
    : Geometry::Polyline(rect.cbegin(), rect.cend())
{

}

Geometry::Polygon &Geometry::Polygon::operator=(const Geometry::Polygon &polygon)
{
    if (this != &polygon)
    {
        Geometry::Polyline::operator=(polygon);
    }
    return *this;
}

Geometry::Polygon &Geometry::Polygon::operator=(const Rectangle &rect)
{
    _points.clear();
    for (const Geometry::Point &point : rect)
    {
        _points.emplace_back(point);
    }
    _points.emplace_back(_points.front());
    return *this;
}

Geometry::Polygon *Geometry::Polygon::clone() const
{
    return new Geometry::Polygon(*this);
}

Geometry::Type Geometry::Polygon::type() const
{
    return Geometry::Type::POLYGON;
}

void Geometry::Polygon::reorder_points(const bool cw)
{
    if (size() < 4)
    {
        return;
    }
    
    double result = 0;
    for (size_t i = 0, count = size() - 1; i < count; ++i)
    {
        result += (_points[i].x * _points[i + 1].y - _points[i + 1].x * _points[i].y);
    }
    if (cw)
    {
        if (result > 0)
        {
            std::reverse(_points.begin(), _points.end());
        }
    }
    else
    {
        if (result < 0)
        {
            std::reverse(_points.begin(), _points.end());
        }
    }
}

bool Geometry::Polygon::is_cw() const
{
    if (size() < 4)
    {
        return false;
    }

    double result = 0;
    for (size_t i = 0, count = size() - 1; i < count; ++i)
    {
        result += (_points[i].x * _points[i + 1].y - _points[i + 1].x * _points[i].y);
    }
    return result < 0;
}

void Geometry::Polygon::append(const Geometry::Point &point)
{
    if (size() < 2)
    {
        Geometry::Polyline::append(point);
    }
    else
    {
        if (_points.front() == _points.back())
        {
            Geometry::Polyline::insert(size() - 1, point);
        }
        else
        {
            _points.emplace_back(point);
            _points.emplace_back(_points.front());
        }
    }
}

void Geometry::Polygon::append(const Geometry::Polyline &polyline)
{
    if (empty())
    {
        Geometry::Polyline::append(polyline);
        if (_points.front() != _points.back())
        {
            _points.emplace_back(_points.front());
        }
    }
    else
    {
        if (_points.front() == _points.back())
        {
            Geometry::Polyline::insert(size() - 1, polyline);
        }
        else
        {
            Geometry::Polyline::append(polyline);
            _points.emplace_back(_points.front());
        }
    }
}

void Geometry::Polygon::append(std::vector<Geometry::Point>::const_iterator begin, std::vector<Geometry::Point>::const_iterator end)
{
    if (empty())
    {
        Geometry::Polyline::append(begin, end);
        if (_points.front() != _points.back())
        {
            _points.emplace_back(_points.front());
        }
    }
    else
    {
        if (_points.front() == _points.back())
        {
            Geometry::Polyline::insert(size() - 1, begin, end);
        }
        else
        {
            _points.insert(_points.end(), begin, end);
            _points.emplace_back(_points.front());
        }
    }
}

void Geometry::Polygon::insert(const size_t index, const Geometry::Point &point)
{
    Geometry::Polyline::insert(index, point);
    if (index == 0)
    {
        _points.back() = _points.front();
    }
}

void Geometry::Polygon::insert(const size_t index, const Geometry::Polyline &polyline)
{
    Geometry::Polyline::insert(index, polyline);
    if (index == 0)
    {
        _points.back() = _points.front();
    }
}

void Geometry::Polygon::insert(const size_t index, std::vector<Geometry::Point>::const_iterator begin, std::vector<Geometry::Point>::const_iterator end)
{
    Geometry::Polyline::insert(index, begin, end);
    if (index == 0)
    {
        _points.back() = _points.front();
    }
}

void Geometry::Polygon::remove(const size_t index)
{
    Geometry::Polyline::remove(index);
    if (index == 0)
    {
        _points.back() = _points.front();
    }
    else if (index == size())
    {
        _points.front() = _points.back();
    }
}

void Geometry::Polygon::remove(const size_t index, const size_t count)
{
    Geometry::Polyline::remove(index, count);
    if (size() > 2)
    {
        if (index == 0)
        {
            _points.back() = _points.front();
        }
        else if (index + count >= size())
        {
            _points.front() = _points.back();
        }
    }
}

Geometry::Point Geometry::Polygon::pop(const size_t index)
{
    Geometry::Point point = Geometry::Polyline::pop(index);
    if (index == 0)
    {
        _points.back() = _points.front();
    }
    else if (index == size())
    {
        _points.front() = _points.back();
    }
    return point;
}

Geometry::Polygon Geometry::Polygon::operator+(const Geometry::Point &point) const
{
    std::vector<Geometry::Point> temp(_points);
    for (Geometry::Point &p : temp)
    {
        p += point;
    }
    return Geometry::Polygon(temp.cbegin(), temp.cend());
}

Geometry::Polygon Geometry::Polygon::operator-(const Geometry::Point &point) const
{
    std::vector<Geometry::Point> temp(_points);
    for (Geometry::Point &p : temp)
    {
        p -= point;
    }
    return Geometry::Polygon(temp.cbegin(), temp.cend());
}

double Geometry::Polygon::area() const
{
    if (size() < 4)
    {
        return 0;
    }
    double result = 0;
    for (size_t i = 0, count = size() - 1; i < count; ++i)
    {
        result += (_points[i].x * _points[i + 1].y - _points[i + 1].x * _points[i].y);
    }
    return std::abs(result) / 2.0;
}

size_t Geometry::Polygon::next_point_index(const size_t index) const
{
    if (index < _points.size() - 1)
    {
        return index + 1;
    }
    else
    {
        return 1;
    }
}

const Geometry::Point &Geometry::Polygon::next_point(const size_t index) const
{
    if (index < _points.size() - 1)
    {
        return _points[index + 1];
    }
    else
    {
        return _points[1];
    }
}

Geometry::Point &Geometry::Polygon::next_point(const size_t index)
{
    if (index < _points.size() - 1)
    {
        return _points[index + 1];
    }
    else
    {
        return _points[1];
    }
}

size_t Geometry::Polygon::last_point_index(const size_t index) const
{
    if (index > 0)
    {
        return index - 1;
    }
    else
    {
        return _points.size() - 2;
    }
}

const Geometry::Point &Geometry::Polygon::last_point(const size_t index) const
{
    if (index > 0)
    {
        return _points[index - 1];
    }
    else
    {
        return _points[_points.size() - 2];
    }
}

Geometry::Point &Geometry::Polygon::last_point(const size_t index)
{
    if (index > 0)
    {
        return _points[index - 1];
    }
    else
    {
        return _points[_points.size() - 2];
    }
}

size_t Geometry::Polygon::index(const double x, const double y) const
{
    for (size_t i = 0, count = _points.size() - 1; i < count; ++i)
    {
        if (_points[i].x == x && _points[i].y == y)
        {
            return i;
        }
    }
    return SIZE_MAX;
}

size_t Geometry::Polygon::index(const Geometry::Point &point) const
{
    for (size_t i = 0, count = _points.size() - 1; i < count; ++i)
    {
        if (_points[i] == point)
        {
            return i;
        }
    }
    return SIZE_MAX;
}