#include <cmath>
#include <array>
#include <algorithm>
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/Polygon.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Square.hpp"
#include "Math/Geometry/Line.hpp"
#include "Math/Geometry/Bezier.hpp"
#include "Math/Geometry/Circle.hpp"
#include "Math/Geometry/Triangle.hpp"
#include "Math/Geometry/EarCut/EarCut.hpp"


using namespace ToyGameEngine::Math;

Geometry::MarkedPoint::MarkedPoint()
{

}

Geometry::MarkedPoint::MarkedPoint(const double x_, const double y_, const bool original_, const int value_)
    : x(x_), y(y_), value(value_), original(original_)
{

}

bool Geometry::MarkedPoint::operator==(const Geometry::MarkedPoint &point) const
{
    return x == point.x && y == point.y;
}

bool Geometry::MarkedPoint::operator!=(const Geometry::MarkedPoint &point) const
{
    return x != point.x || y != point.y;
}


double Geometry::distance(const double x0, const double y0, const double x1, const double y1)
{
    return std::sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}

double Geometry::distance(const Geometry::Point &point0, const Geometry::Point &point1)
{
    return std::sqrt((point0.x - point1.x) * (point0.x - point1.x) + (point0.y - point1.y) * (point0.y - point1.y));
}

double Geometry::distance(const Geometry::Point &point, const Geometry::Line &line, const bool infinite)
{
    if (line.front().x == line.back().x)
    {
        if (infinite)
        {
            return std::abs(point.x - line.front().x);
        }
        else
        {
            if ((point.y >= line.front().y && point.y <= line.back().y) ||
                (point.y <= line.front().y && point.y >= line.back().y))
            {
                return std::abs(point.x - line.front().x);
            }
            else
            {
                return std::min(Geometry::distance(point, line.front()), Geometry::distance(point, line.back()));
            }
        }
    }
    else if (line.front().y == line.back().y)
    {
        if (infinite)
        {
            return std::abs(point.y - line.front().y);
        }
        else
        {
            if ((point.x >= line.front().x && point.x <= line.back().x) ||
                (point.x <= line.front().x && point.x >= line.back().x))
            {
                return std::abs(point.y - line.front().y);
            }
            else
            {
                return std::min(Geometry::distance(point, line.front()), Geometry::distance(point, line.back()));
            }
        }
    }
    
    const double a = line.back().y - line.front().y, 
                b = line.front().x - line.back().x,
                c = line.back().x * line.front().y - line.front().x * line.back().y;
    if (infinite)
    {
        return std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
    }
    else
    {
        const double k = ((point.x - line.front().x) * (line.back().x - line.front().x) +
            (point.y - line.front().y) * (line.back().y - line.front().y)) /
            (std::pow(line.back().x - line.front().x, 2) + std::pow(line.back().y - line.front().y, 2)); 
        const double x = line.front().x + k * (line.back().x - line.front().x);

        if ((x >= line.front().x && x <= line.back().x) || (x <= line.front().x && x >= line.back().x))
        {
            return std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
        }
        else
        {
            return std::min(Geometry::distance(point, line.front()), Geometry::distance(point, line.back()));
        }
    }
}

double Geometry::distance(const Geometry::Point &point, const Geometry::Point &start, const Geometry::Point &end, const bool infinite)
{
    if (start.x == end.x)
    {
        if (infinite)
        {
            return std::abs(point.x - start.x);
        }
        else
        {
            if ((point.y >= start.y && point.y <= end.y) ||
                (point.y <= start.y && point.y >= end.y))
            {
                return std::abs(point.x - start.x);
            }
            else
            {
                return std::min(Geometry::distance(point, start), Geometry::distance(point, end));
            }
        }
    }
    else if (start.y == end.y)
    {
        if (infinite)
        {
            return std::abs(point.y - start.y);
        }
        else
        {
            if ((point.x >= start.x && point.x <= end.x) ||
                (point.x <= start.x && point.x >= end.x))
            {
                return std::abs(point.y - start.y);
            }
            else
            {
                return std::min(Geometry::distance(point, start), Geometry::distance(point, end));
            }
        }
    }
    
    const double a = end.y - start.y, 
                b = start.x - end.x,
                c = end.x * start.y - start.x * end.y;
    if (infinite)
    {
        return std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
    }
    else
    {
        const double k = ((point.x - start.x) * (end.x - start.x) +
            (point.y - start.y) * (end.y - start.y)) /
            (std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2)); 
        const double x = start.x + k * (end.x - start.x);

        if ((x >= start.x && x <= end.x) || (x <= start.x && x >= end.x))
        {
            return std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
        }
        else
        {
            return std::min(Geometry::distance(point, start), Geometry::distance(point, end));
        }
    }
}

double Geometry::distance(const Geometry::Point &point, const Geometry::Polyline &polyline)
{
    double dis = DBL_MAX;
    for (size_t i = 1, count = polyline.size(); i < count; ++i)
    {
        dis = std::min(dis, Geometry::distance(point, polyline[i - 1], polyline[i]));
    }
    return dis;
}

double Geometry::distance(const Geometry::Point &point, const Geometry::Polygon &polygon)
{
    double dis = DBL_MAX;
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        dis = std::min(dis, Geometry::distance(point, polygon[i - 1], polygon[i]));
    }
    return dis;
}

double Geometry::distance(const Geometry::Point &point, const Geometry::Rectangle &rect)
{
    double dis = Geometry::distance(point, rect[0], rect[3]);
    dis = std::min(dis, Geometry::distance(point, rect[0], rect[1]));
    dis = std::min(dis, Geometry::distance(point, rect[1], rect[2]));
    dis = std::min(dis, Geometry::distance(point, rect[2], rect[3]));
    return dis;
}

double Geometry::distance(const Geometry::Point &start0, const Geometry::Point &end0, const Geometry::Point &start1, const Geometry::Point &end1)
{
    if (Geometry::is_parallel(start0, end0, start1, end1))
    {
        return Geometry::distance(start0, start1, end1, true);
    }
    else
    {
        double distance[5] = {Geometry::distance(start0, start1, end1, true), Geometry::distance(end0, start1, end1, true),
            Geometry::distance(start1, start0, end0, true), Geometry::distance(end1, start0, end0, true), DBL_MAX};
        for (int i = 0; i < 4; ++i)
        {
            if (distance[i] < distance[4])
            {
                distance[4] = distance[i];
            }
        }
        return distance[4];
    }
}

double Geometry::distance(const Geometry::Point &start0, const Geometry::Point &end0, const Geometry::Point &start1, const Geometry::Point &end1, Geometry::Point &point0, Geometry::Point &point1)
{
    if (Geometry::is_parallel(start0, end0, start1, end1))
    {
        if (Geometry::foot_point(start1, end1, start0, point1) && Geometry::foot_point(start1, end1, end0, point1))
        {
            point0 = (start0 + end0) / 2;
            Geometry::foot_point(start1, end1, point0, point1, true);
        }
        else if (Geometry::foot_point(start0, end0, start1, point0) && Geometry::foot_point(start0, end0, end1, point0))
        {
            point1 = (start1 + end1) / 2;
            Geometry::foot_point(start0, end0, point1, point0, true);
        }
        else
        {
            if (Geometry::foot_point(start1, end1, start0, point0))
            {
                if ((end0 - start0) * (end1 - start1) >= 0)
                {
                    point1 = (point0 + end1) / 2;
                }
                else
                {
                    point1 = (point0 + start1) / 2;
                }
                Geometry::foot_point(start0, end0, point1, point0, true);
            }
            else if (Geometry::foot_point(start1, end1, end0, point0))
            {
                if ((end0 - start0) * (end1 - start1) >= 0)
                {
                    point1 = (point0 + start1) / 2;
                }
                else
                {
                    point1 = (point0 + end1) / 2;
                }
                Geometry::foot_point(start0, end0, point1, point0, true);
            }
            else
            {
                double distance[5] = {Geometry::distance_square(start0, start1), Geometry::distance_square(start0, end1),
                    Geometry::distance_square(end0, start1), Geometry::distance(end0, end1), DBL_MAX};
                int index = 0;
                for (int i = 0; i < 4; ++i)
                {
                    if (distance[i] < distance[4])
                    {
                        index = i;
                        distance[4] = distance[i];
                    }
                }
                switch (index)
                {
                case 0:
                    point0 = start0;
                    point1 = start1;
                    break;
                case 1:
                    point0 = start0;
                    point1 = end1;
                    break;
                case 2:
                    point0 = end0;
                    point1 = start1;
                    break;
                case 3:
                    point0 = end0;
                    point1 = end1;
                    break;
                }
            }
        }
        return Geometry::distance(start0, start1, end1);
    }
    else
    {
        double distance[5] = {Geometry::distance(start0, start1, end1), Geometry::distance(end0, start1, end1),
            Geometry::distance(start1, start0, end0), Geometry::distance(end1, start0, end0), DBL_MAX};
        int index = 0;
        for (int i = 0; i < 4; ++i)
        {
            if (distance[i] < distance[4])
            {
                index = i;
                distance[4] = distance[i];
            }
        }

        switch (index)
        {
        case 0:
            point0 = start0;
            if (!Geometry::foot_point(start1, end1, start0, point1))
            {
                if (Geometry::distance_square(start0, start1) <= Geometry::distance_square(start0, end1))
                {
                    point1 = start1;
                }
                else
                {
                    point1 = end1;
                }
            }
            break;
        case 1:
            point0 = end0;
            if (!Geometry::foot_point(start1, end1, end0, point1))
            {
                if (Geometry::distance_square(end0, start1) <= Geometry::distance_square(end0, end1))
                {
                    point1 = start1;
                }
                else
                {
                    point1 = end1;
                }
            }
            break;
        case 2:
            point1 = start1;
            if (!Geometry::foot_point(start0, end0, start1, point0))
            {
                if (Geometry::distance_square(start1, start0) <= Geometry::distance_square(start1, end0))
                {
                    point0 = start0;
                }
                else
                {
                    point0 = end0;
                }
            }
            break;
        case 3:
            point1 = end1;
            if (Geometry::foot_point(start0, end0, end1, point0))
            {
                if (Geometry::distance_square(end1, start0) <= Geometry::distance_square(end1, end0))
                {
                    point0 = start0;
                }
                else
                {
                    point0 = end0;
                }
            }
            break;
        }
        return distance[4];
    }
}


double Geometry::distance_square(const double x0, const double y0, const double x1, const double y1)
{
    return (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
}

double Geometry::distance_square(const Geometry::Point &point0, const Geometry::Point &point1)
{
    return (point0.x - point1.x) * (point0.x - point1.x) + (point0.y - point1.y) * (point0.y - point1.y);
}

double Geometry::distance_square(const Geometry::Point &point, const Geometry::Line &line, const bool infinite)
{
    if (line.front().x == line.back().x)
    {
        if (infinite)
        {
            return std::pow(point.x - line.front().x, 2);
        }
        else
        {
            if ((point.y >= line.front().y && point.y <= line.back().y) ||
                (point.y <= line.front().y && point.y >= line.back().y))
            {
                return std::pow(point.x - line.front().x, 2);
            }
            else
            {
                return std::min(Geometry::distance_square(point, line.front()), Geometry::distance_square(point, line.back()));
            }
        }
    }
    else if (line.front().y == line.back().y)
    {
        if (infinite)
        {
            return std::pow(point.y - line.front().y, 2);
        }
        else
        {
            if ((point.x >= line.front().x && point.x <= line.back().x) ||
                (point.x <= line.front().x && point.x >= line.back().x))
            {
                return std::pow(point.y - line.front().y, 2);
            }
            else
            {
                return std::min(Geometry::distance_square(point, line.front()), Geometry::distance_square(point, line.back()));
            }
        }
    }
    
    const double a = line.back().y - line.front().y, 
                b = line.front().x - line.back().x,
                c = line.back().x * line.front().y - line.front().x * line.back().y;
    if (infinite)
    {
        return std::pow(a * point.x + b * point.y + c, 2) / (a * a + b * b);
    }
    else
    {
        const double k = ((point.x - line.front().x) * (line.back().x - line.front().x) +
            (point.y - line.front().y) * (line.back().y - line.front().y)) /
            (std::pow(line.back().x - line.front().x, 2) + std::pow(line.back().y - line.front().y, 2)); 
        const double x = line.front().x + k * (line.back().x - line.front().x);

        if ((x >= line.front().x && x <= line.back().x) || (x <= line.front().x && x >= line.back().x))
        {
            return std::pow(a * point.x + b * point.y + c, 2) / (a * a + b * b);
        }
        else
        {
            return std::min(Geometry::distance_square(point, line.front()), Geometry::distance_square(point, line.back()));
        }
    }
}

double Geometry::distance_square(const Geometry::Point &point, const Geometry::Point &start, const Geometry::Point &end, const bool infinite)
{
    if (start.x == end.x)
    {
        if (infinite)
        {
            return std::pow(point.x - start.x, 2);
        }
        else
        {
            if ((point.y >= start.y && point.y <= end.y) ||
                (point.y <= start.y && point.y >= end.y))
            {
                return std::pow(point.x - start.x, 2);
            }
            else
            {
                return std::min(Geometry::distance_square(point, start), Geometry::distance_square(point, end));
            }
        }
    }
    else if (start.y == end.y)
    {
        if (infinite)
        {
            return std::pow(point.y - start.y, 2);
        }
        else
        {
            if ((point.x >= start.x && point.x <= end.x) ||
                (point.x <= start.x && point.x >= end.x))
            {
                return std::pow(point.y - start.y, 2);
            }
            else
            {
                return std::min(Geometry::distance_square(point, start), Geometry::distance_square(point, end));
            }
        }
    }
    
    const double a = end.y - start.y, 
                b = start.x - end.x,
                c = end.x * start.y - start.x * end.y;
    if (infinite)
    {
        return std::pow(a * point.x + b * point.y + c, 2) / (a * a + b * b);
    }
    else
    {
        const double k = ((point.x - start.x) * (end.x - start.x) +
            (point.y - start.y) * (end.y - start.y)) /
            (std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2)); 
        const double x = start.x + k * (end.x - start.x);

        if ((x >= start.x && x <= end.x) || (x <= start.x && x >= end.x))
        {
            return std::pow(a * point.x + b * point.y + c, 2) / (a * a + b * b);
        }
        else
        {
            return std::min(Geometry::distance_square(point, start), Geometry::distance_square(point, end));
        }
    }
}


bool Geometry::is_inside(const Geometry::Point &point, const Geometry::Line &line, const bool infinite)
{
    if (std::abs(Geometry::cross(line.back() - line.front(), point - line.front())) < Geometry::EPSILON)
    {
        return infinite || Geometry::distance(point, line.front()) + Geometry::distance(point, line.back()) < line.length() + Geometry::EPSILON;
    }
    else
    {
        return false;
    }
}

bool Geometry::is_inside(const Geometry::Point &point, const Geometry::Point &start, const Geometry::Point &end, const bool infinite)
{
    if (std::abs(Geometry::cross(end - start, point - start)) < Geometry::EPSILON)
    {
        return infinite || Geometry::distance(point, start) + Geometry::distance(point, end) < Geometry::distance(start, end) + Geometry::EPSILON;
    }
    else
    {
        return false;
    }
}

bool Geometry::is_inside(const Geometry::Point &point, const Geometry::Polyline &polyline)
{
    for (size_t i = 1, count = polyline.size(); i < count; ++i)
    {
        if (Geometry::is_inside(point, polyline[i-1], polyline[i]))
        {
            return true;
        }
    }
    return false;
}

bool Geometry::is_inside(const Geometry::Point &point, const Geometry::Polygon &polygon, const bool coincide)
{
    if (!polygon.empty() && Geometry::is_inside(point, polygon.bounding_rect(), coincide))
    {
        if (coincide)
        {
            for (size_t i = 1, len = polygon.size(); i < len; ++i)
            {
                if (Geometry::is_inside(point, polygon[i-1], polygon[i]))
                {
                    return true;
                }
            }
        }
        else
        {
            for (size_t i = 1, len = polygon.size(); i < len; ++i)
            {
                if (Geometry::is_inside(point, polygon[i-1], polygon[i]))
                {
                    return false;
                }
            }
        }

        double x = (-DBL_MAX);
        std::vector<Geometry::MarkedPoint> points;
        for (const Geometry::Point &p : polygon)
        {
            x = std::max(x, p.x);
            points.emplace_back(p.x, p.y);
        }
        // if (polygon.area() < 0)
        // {
        //     std::reverse(points.begin(), points.end());
        // }

        Geometry::Point temp, end(x + 80, point.y); // 找到交点并计算其几何数
        for (size_t i = 1, count = points.size(); i < count; ++i)
        {
            if (!Geometry::is_parallel(point, end, points[i], points[i - 1]) &&
                Geometry::is_intersected(point, end, points[i], points[i - 1], temp))
            {
                points.insert(points.begin() + i++, Geometry::MarkedPoint(temp.x, temp.y, false));
                ++count;
                if (Geometry::cross(temp, end, points[i], points[i - 1]) >= 0)
                {
                    points[i - 1].value = -1;
                }
                else
                {
                    points[i - 1].value = 1;
                }
            }
        }

        if (points.size() == polygon.size()) // 无交点
        {
            return false;
        }

        // 去除重复交点
        for (size_t count, j, i = points.size() - 1; i > 0; --i)
        {
            count = points[i].original ? 0 : 1;
            for (j = i; j > 0; --j)
            {
                if (std::abs(points[i].x - points[j - 1].x) > Geometry::EPSILON || 
                    std::abs(points[i].y - points[j - 1].y) > Geometry::EPSILON)
                {
                    break;
                }
                if (!points[j - 1].original)
                {
                    ++count;
                }
            }
            if (count < 2)
            {
                continue;
            }

            int value = 0;
            for (size_t k = i; k > j; --k)
            {
                if (!points[k].original)
                {
                    value += points[k].value;
                }
            }
            if (!points[j].original)
            {
                value += points[j].value;
            }
            if (value == 0)
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points[k].original)
                    {
                        points.erase(points.begin() + k);
                    }
                }
                if (!points[j].original)
                {
                    points.erase(points.begin() + j);
                }
            }
            else
            {
                bool flag = false;
                for (size_t k = i; k > j; --k)
                {
                    flag = (flag || points[k].original);
                    points.erase(points.begin() + k);
                }
                points[j].value = value;
                points[j].original = (flag || points[j].original);
            }
            i = j > 0 ? j : 1;
        }

        // 处理重边上的交点
        for (size_t i = 0, j = 1, count = points.size(); j < count; i = j)
        {
            while (i < count && points[i].value == 0)
            {
                ++i;
            }
            j = i + 1;
            while (j < count && points[j].value == 0)
            {
                ++j;
            }
            if (j >= count)
            {
                break;
            }
            if (polygon.index(points[i]) == SIZE_MAX || polygon.index(points[j]) == SIZE_MAX)
            {
                continue;
            }

            if (points[i].value > 0 && points[j].value > 0)
            {
                points.erase(points.begin() + j);
                --count;
            }
            else if (points[i].value < 0 && points[j].value < 0)
            {
                points.erase(points.begin() + i);
                --count;
            }
            else
            {
                points.erase(points.begin() + j--);
                points.erase(points.begin() + i);
                --count;
                --count;
            }
        }

        return std::count_if(points.begin(), points.end(), [](const Geometry::MarkedPoint &p) { return p.value != 0; }) % 2 == 1;
    }
    else
    {
        return false;
    }
}

bool Geometry::is_inside(const Geometry::Point &point, const Geometry::Rectangle &rect, const bool coincide)
{
    if (!rect.empty() && Geometry::is_inside(point, rect.bounding_rect(), coincide))
    {
        if (coincide)
        {
            for (size_t i = 1; i < 4; ++i)
            {
                if (Geometry::is_inside(point, rect[i-1], rect[i]))
                {
                    return true;
                }
            }
            if (Geometry::is_inside(point, rect[0], rect[3]))
            {
                return true;
            }
        }
        else
        {
            for (size_t i = 1; i < 4; ++i)
            {
                if (Geometry::is_inside(point, rect[i-1], rect[i]))
                {
                    return false;
                }
            }
            if (Geometry::is_inside(point, rect[0], rect[3]))
            {
                return false;
            }
        }

        double x = (-DBL_MAX);
        std::vector<Geometry::MarkedPoint> points;
        for (const Geometry::Point &p : rect)
        {
            x = std::max(x, p.x);
            points.emplace_back(p.x, p.y);
        }

        Geometry::Point temp, end(x + 80, point.y); // 找到交点并计算其几何数
        for (size_t i = 1, count = points.size(); i < count; ++i)
        {
            if (!Geometry::is_parallel(point, end, points[i], points[i - 1]) &&
                Geometry::is_intersected(point, end, points[i], points[i - 1], temp))
            {
                points.insert(points.begin() + i++, Geometry::MarkedPoint(temp.x, temp.y, false));
                ++count;
                if (Geometry::cross(temp, end, points[i], points[i - 1]) >= 0)
                {
                    points[i - 1].value = -1;
                }
                else
                {
                    points[i - 1].value = 1;
                }
            }
        }

        if (points.size() == 4) // 无交点
        {
            return false;
        }

        // 去除重复交点
        for (size_t count, j, i = points.size() - 1; i > 0; --i)
        {
            count = points[i].original ? 0 : 1;
            for (j = i; j > 0; --j)
            {
                if (std::abs(points[i].x - points[j - 1].x) > Geometry::EPSILON || 
                    std::abs(points[i].y - points[j - 1].y) > Geometry::EPSILON)
                {
                    break;
                }
                if (!points[j - 1].original)
                {
                    ++count;
                }
            }
            if (count < 2)
            {
                continue;
            }

            int value = 0;
            for (size_t k = i; k > j; --k)
            {
                if (!points[k].original)
                {
                    value += points[k].value;
                }
            }
            if (!points[j].original)
            {
                value += points[j].value;
            }
            if (value == 0)
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points[k].original)
                    {
                        points.erase(points.begin() + k);
                    }
                }
                if (!points[j].original)
                {
                    points.erase(points.begin() + j);
                }
            }
            else
            {
                bool flag = false;
                for (size_t k = i; k > j; --k)
                {
                    flag = (flag || points[k].original);
                    points.erase(points.begin() + k);
                }
                points[j].value = value;
                points[j].original = (flag || points[j].original);
            }
            i = j > 0 ? j : 1;
        }

        // 处理重边上的交点
        for (size_t i = 0, j = 1, count = points.size(); j < count; i = j)
        {
            while (i < count && points[i].value == 0)
            {
                ++i;
            }
            j = i + 1;
            while (j < count && points[j].value == 0)
            {
                ++j;
            }
            if (j >= count)
            {
                break;
            }
            if (rect.index(points[i]) == SIZE_MAX || rect.index(points[j]) == SIZE_MAX)
            {
                continue;
            }

            if (points[i].value > 0 && points[j].value > 0)
            {
                points.erase(points.begin() + j);
                --count;
            }
            else if (points[i].value < 0 && points[j].value < 0)
            {
                points.erase(points.begin() + i);
                --count;
            }
            else
            {
                points.erase(points.begin() + j--);
                points.erase(points.begin() + i);
                --count;
                --count;
            }
        }

        return std::count_if(points.begin(), points.end(), [](const Geometry::MarkedPoint &p) { return p.value != 0; }) % 2 == 1;
    }
    else
    {
        return false;
    }
}

bool Geometry::is_inside(const Geometry::Point &point, const Geometry::Square &square, const bool coincide)
{
    if (Geometry::is_inside(point, Geometry::Circle(square.center(), square.outer_circle_radius())))
    {
        if (Geometry::is_inside(point, Geometry::Circle(square.center(), square.inner_cicle_radius()), coincide))
        {
            return true;
        }
        
        double x = (-DBL_MAX);
        std::vector<Geometry::MarkedPoint> points;
        for (const Geometry::Point &p : square)
        {
            x = std::max(x, p.x);
            points.emplace_back(p.x, p.y);
        }

        Geometry::Point temp, end(x + 80, point.y); // 找到交点并计算其几何数
        for (size_t i = 1, count = points.size(); i < count; ++i)
        {
            if (!Geometry::is_parallel(point, end, points[i], points[i - 1]) &&
                Geometry::is_intersected(point, end, points[i], points[i - 1], temp))
            {
                points.insert(points.begin() + i++, Geometry::MarkedPoint(temp.x, temp.y, false));
                ++count;
                if (Geometry::cross(temp, end, points[i], points[i - 1]) >= 0)
                {
                    points[i - 1].value = -1;
                }
                else
                {
                    points[i - 1].value = 1;
                }
            }
        }

        if (points.size() == 4) // 无交点
        {
            return false;
        }

        // 去除重复交点
        for (size_t count, j, i = points.size() - 1; i > 0; --i)
        {
            count = points[i].original ? 0 : 1;
            for (j = i; j > 0; --j)
            {
                if (std::abs(points[i].x - points[j - 1].x) > Geometry::EPSILON || 
                    std::abs(points[i].y - points[j - 1].y) > Geometry::EPSILON)
                {
                    break;
                }
                if (!points[j - 1].original)
                {
                    ++count;
                }
            }
            if (count < 2)
            {
                continue;
            }

            int value = 0;
            for (size_t k = i; k > j; --k)
            {
                if (!points[k].original)
                {
                    value += points[k].value;
                }
            }
            if (!points[j].original)
            {
                value += points[j].value;
            }
            if (value == 0)
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points[k].original)
                    {
                        points.erase(points.begin() + k);
                    }
                }
                if (!points[j].original)
                {
                    points.erase(points.begin() + j);
                }
            }
            else
            {
                bool flag = false;
                for (size_t k = i; k > j; --k)
                {
                    flag = (flag || points[k].original);
                    points.erase(points.begin() + k);
                }
                points[j].value = value;
                points[j].original = (flag || points[j].original);
            }
            i = j > 0 ? j : 1;
        }

        // 处理重边上的交点
        for (size_t i = 0, j = 1, count = points.size(); j < count; i = j)
        {
            while (i < count && points[i].value == 0)
            {
                ++i;
            }
            j = i + 1;
            while (j < count && points[j].value == 0)
            {
                ++j;
            }
            if (j >= count)
            {
                break;
            }
            if (square.index(points[i]) == SIZE_MAX || square.index(points[j]) == SIZE_MAX)
            {
                continue;
            }

            if (points[i].value > 0 && points[j].value > 0)
            {
                points.erase(points.begin() + j);
                --count;
            }
            else if (points[i].value < 0 && points[j].value < 0)
            {
                points.erase(points.begin() + i);
                --count;
            }
            else
            {
                points.erase(points.begin() + j--);
                points.erase(points.begin() + i);
                --count;
                --count;
            }
        }

        return std::count_if(points.begin(), points.end(), [](const Geometry::MarkedPoint &p) { return p.value != 0; }) % 2 == 1;
    }
    else
    {
        return false;
    }
}

bool Geometry::is_inside(const Geometry::Point &point, const Geometry::AABBRect &rect, const bool coincide)
{
    if (rect.empty())
    {
        return false;
    }
    const double x = point.x, y = point.y;
    if (coincide)
    {
        return rect.left() <= x && x <= rect.right() && rect.bottom() <= y && y <= rect.top();
    }
    else
    {
        return rect.left() < x && x < rect.right() && rect.bottom() < y && y < rect.top();
    }
}

bool Geometry::is_inside(const Geometry::Point &point, const Geometry::Circle &circle, const bool coincide)
{
    if (circle.empty())
    {
        return false;
    }
    if (coincide)
    {
        return (point.x - circle.x) * (point.x - circle.x) * (point.y - circle.y) * (point.y - circle.y)
            <= circle.radius * circle.radius;
    }
    else
    {
        return (point.x - circle.x) * (point.x - circle.x) * (point.y - circle.y) * (point.y - circle.y)
            < circle.radius * circle.radius;
    }
}

bool Geometry::is_inside(const Geometry::Point &point, const Geometry::Point &point0, const Geometry::Point &point1, const Geometry::Point &point2, const bool coincide)
{
    if (coincide)
    {
        const bool a = (point2.x - point.x) * (point0.y - point.y) >= (point0.x - point.x) * (point2.y - point.y);
        const bool b = (point0.x - point.x) * (point1.y - point.y) >= (point1.x - point.x) * (point0.y - point.y);
        const bool c = (point1.x - point.x) * (point2.y - point.y) >= (point2.x - point.x) * (point1.y - point.y);
        return a == b && b == c;
    }
    else
    {
        const bool a = (point2.x - point.x) * (point0.y - point.y) > (point0.x - point.x) * (point2.y - point.y);
        const bool b = (point0.x - point.x) * (point1.y - point.y) > (point1.x - point.x) * (point0.y - point.y);
        const bool c = (point1.x - point.x) * (point2.y - point.y) > (point2.x - point.x) * (point1.y - point.y);
        return a == b && b == c;
    }
}

bool Geometry::is_inside(const Geometry::Point &point, const Geometry::Triangle &triangle, const bool coincide)
{
    return Geometry::is_inside(point, triangle[0], triangle[1], triangle[2], coincide);
}

bool Geometry::is_inside(const Geometry::Point &start, const Geometry::Point &end, const Geometry::Triangle &triangle)
{
    return Geometry::is_inside(start, triangle) && Geometry::is_inside(end, triangle);
}

bool Geometry::is_inside(const Geometry::Triangle &triangle0, const Geometry::Triangle &triangle1)
{
    return Geometry::is_inside(triangle0[0], triangle1) && Geometry::is_inside(triangle0[1], triangle1) && Geometry::is_inside(triangle0[2], triangle1);
}


bool Geometry::is_parallel(const Geometry::Point &point0, const Geometry::Point &point1, const Geometry::Point &point2, const Geometry::Point &point3)
{
    if (point0.x == point1.x && point2.x == point3.x)
    {
        return true;
    }
    else
    {
        return ((point0.y - point1.y) * (point2.x - point3.x)) == ((point2.y - point3.y) * (point0.x - point1.x));
    }
}

bool Geometry::is_parallel(const Geometry::Line &line0, const Geometry::Line &line1)
{
    return Geometry::is_parallel(line0.front(), line0.back(), line1.front(), line1.back());
}


bool Geometry::is_coincide(const Geometry::Point &start0, const Geometry::Point &end0, const Geometry::Point &start1, const Geometry::Point &end1)
{
    if ((start0 == start1 && end0 == end1) || (start0 == end1 && end0 == start0))
    {
        return true;
    }

    if (start0.x == end0.x)
    {
        if (start1.x == end1.x && start0.x == start1.x)
        {
            const bool result0 = (start1.y < start0.y && start0.y < end1.y) || (end1.y < start0.y && start0.y < start1.y);
            const bool result1 = (start1.y < end0.y && end0.y < end1.y) || (end1.y < end0.y && end0.y < start1.y);
            const bool result2 = (start0.y < start1.y && start1.y < end0.y) || (end0.y < start1.y && start1.y < start0.y);
            const bool result3 = (start0.y < end1.y && end1.y < end0.y) || (end0.y < end1.y && end1.y < start0.y);
            return result0 || result1 || result2 || result3;
        }
        else
        {
            return false;
        }
    }
    else if (start0.y == end0.y)
    {
        if (start1.y == end1.y && start0.y == start1.y)
        {
            const bool result0 = (start1.x < start0.x && start0.x < end1.x) || (end1.x < start0.x && start0.x < start1.x);
            const bool result1 = (start1.x < end0.x && end0.x < end1.x) || (end1.x < end0.x && end0.x < start1.x);
            const bool result2 = (start0.x < start1.x && start1.x < end0.x) || (end0.x < start1.x && start1.x < start0.x);
            const bool result3 = (start0.x < end1.x && end1.x < end0.x) || (end0.x < end1.x && end1.x < start0.x);
            return result0 || result1 || result2 || result3;
        }
        else
        {
            return false;
        }
    }

    const double a0 = end0.y - start0.y, b0 = start0.x - end0.x, c0 = end0.x * start0.y - start0.x * end0.y;
    const double a1 = end1.y - start1.y, b1 = start1.x - end1.x, c1 = end1.x * start1.y - start1.x * end1.y;
    if (std::abs(a0 * b1 - a1 * b0) < Geometry::EPSILON && std::abs(a0 * c1 - a1 * c0) < Geometry::EPSILON && std::abs(b0 * c1 - b1 * c0) < Geometry::EPSILON)
    {
        return Geometry::distance((start0 + end0) / 2, (start1 + end1) / 2) * 2 < Geometry::distance(start0, end0) + Geometry::distance(start1, end1);
    }
    else
    {
        return false;
    }
}

bool Geometry::is_coincide(const Geometry::Point &start, const Geometry::Point &end, const Geometry::Polygon &polygon)
{
    const size_t index0 = polygon.index(start.x, start.y), index1 = polygon.index(end.x, end.y);
    if (std::max(index0, index1) - std::min(index0, index1) == 1)
    {
        return true;
    }

    if (index0 < SIZE_MAX)
    {
        return Geometry::is_coincide(start, end, start, polygon.last_point(index0)) || Geometry::is_coincide(start, end, start, polygon.next_point(index0));
    }
    else if (index1 < SIZE_MAX)
    {
        return Geometry::is_coincide(start, end, end, polygon.last_point(index1)) || Geometry::is_coincide(start, end, end, polygon.next_point(index1));
    }
    else
    {
        for (size_t i = 1, count = polygon.size(); i < count; ++i)
        {
            if (Geometry::is_coincide(start, end, polygon[i - 1], polygon[i]))
            {
                return true;
            }
        }
        return false;
    }
}


bool Geometry::is_part(const Geometry::Point &start0, const Geometry::Point &end0, const Geometry::Point &start1, const Geometry::Point &end1)
{
    if (Geometry::is_coincide(start0, end0, start1, end1))
    {
        if (start0.x == end0.x)
        {
            const double top0 = std::max(start0.y, end0.y), bottom0 = std::min(start0.y, end0.y);
            const double top1 = std::max(start1.y, end1.y), bottom1 = std::min(start1.y, end1.y);
            return bottom1 <= bottom0 && bottom0 <= top1 && bottom1 <= top0 && top0 <= top1;
        }
        else
        {
            const double left0 = std::min(start0.x, end0.x), right0 = std::max(start0.x, end0.x);
            const double left1 = std::min(start1.x, end1.x), right1 = std::max(start1.x, end1.x);
            return left1 <= left0 && left0 <= right0 && left1 <= right0 && right0 <= right1;
        }
    }
    else
    {
        return false;
    }
}

bool Geometry::is_part(const Geometry::Line &line0, const Geometry::Line &line1)
{
    return Geometry::is_part(line0.front(), line0.back(), line1.front(), line1.back());
}


bool Geometry::is_intersected(const Geometry::Point &point0, const Geometry::Point &point1, const Geometry::Point &point2, const Geometry::Point &point3, Geometry::Point &output, const bool infinite)
{
    if (point0 == point2 || point0 == point3)
    {
        output = point0;
        return true;
    }
    else if (point1 == point2 || point1 == point3)
    {
        output = point1;
        return true;
    }

    if (!infinite)
    {
        const double left0 = std::min(point0.x, point1.x), left1 = std::min(point2.x, point3.x);
        const double right0 = std::max(point0.x, point1.x), right1 = std::max(point2.x, point3.x);
        const double top0 = std::max(point0.y, point1.y), top1 = std::max(point2.y, point3.y);
        const double bottom0 = std::min(point0.y, point1.y), bottom1 = std::min(point2.y, point3.y);
        if (left0 > right1 || right0 < left1 || top0 < bottom1 || bottom0 > top1)
        {
            return false;
        }
    }

    const double a0 = point1.y - point0.y, 
                b0 = point0.x - point1.x,
                c0 = point1.x * point0.y - point0.x * point1.y;
    const double a1 = point3.y - point2.y,
                b1 = point2.x - point3.x,
                c1 = point3.x * point2.y - point2.x * point3.y;
    if (std::abs(a0 * b1 - a1 * b0) < Geometry::EPSILON)
    {
        if (std::abs(a0 * c1 - a1 * c0) > Geometry::EPSILON || std::abs(b0 * c1 - b1 * c0) > Geometry::EPSILON)
        {
            return false;
        }
        if (infinite)
        {
            return true;
        }
        else
        {
            const double a = Geometry::distance((point0 + point1) / 2, (point2 + point3) / 2) * 2;
            const double b = Geometry::distance(point0, point1) + Geometry::distance(point2, point3);
            if (a < b)
            {
                return true;
            }
            else if (a == b)
            {
                if (Geometry::distance(point0, point2) < Geometry::EPSILON ||
                    Geometry::distance(point0, point3) < Geometry::EPSILON)
                {
                    output = point0;
                }
                else
                {
                    output = point1;
                }
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    output.x = (c1 * b0 - c0 * b1) / (a0 * b1 - a1 * b0), output.y = (c0 * a1 - c1 * a0) / (a0 * b1 - a1 * b0);

    if (Geometry::is_inside(point0, point2, point3))
    {
        output = point0;
    }
    else if (Geometry::is_inside(point1, point2, point3))
    {
        output = point1;
    }
    else if (Geometry::is_inside(point2, point0, point1))
    {
        output = point2;
    }
    else if (Geometry::is_inside(point3, point0, point1))
    {
        output = point3;
    }

    if (point0.x == point1.x)
    {
        output.x = point0.x;
    }
    else if (point2.x == point3.x)
    {
        output.x = point2.x;
    }

    if (point0.y == point1.y)
    {
        output.y = point0.y;
    }
    else if (point2.y == point3.y)
    {
        output.y = point2.y;
    }

    if (infinite)
    {
        return true;
    }
    else
    {
        const double left = std::max(std::min(point0.x, point1.x), std::min(point2.x, point3.x));
        const double right = std::min(std::max(point0.x, point1.x), std::max(point2.x, point3.x));
        const double top = std::min(std::max(point0.y, point1.y), std::max(point2.y, point3.y));
        const double bottom = std::max(std::min(point0.y, point1.y), std::min(point2.y, point3.y));

        return left - 5e-14 <= output.x && output.x <= right + 5e-14
            && bottom - 5e-14 <= output.y && output.y <= top + 5e-14;
    }
}

bool Geometry::is_intersected(const Geometry::Line &line0, const Geometry::Line &line1, Geometry::Point &output, const bool infinite)
{
    return Geometry::is_intersected(line0.front(), line0.back(), line1.front(), line1.back(), output, infinite);
}

bool Geometry::is_intersected(const Geometry::Point &start, const Geometry::Point &end, const Geometry::Polyline &polyline, const bool infinite)
{
    if (polyline.empty() || (!infinite && !Geometry::is_intersected(polyline.bounding_rect(), start, end)))
    {
        return false;
    }

    Geometry::Point point;
    for (size_t i = 1, count = polyline.size(); i < count; ++i)
    {
        if (Geometry::is_intersected(start, end, polyline[i - 1], polyline[i], point, infinite))
        {
            return true;
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Point &start, const Geometry::Point &end, const Geometry::Polygon &polygon, const bool infinite, const bool inside)
{
    if (polygon.empty() || (!infinite && !Geometry::is_intersected(polygon.bounding_rect(), start, end)))
    {
        return false;
    }

    Geometry::Point point;
    if (infinite)
    {
        for (size_t i = 1, count = polygon.size(); i < count; ++i)
        {
            if (Geometry::is_intersected(start, end, polygon[i - 1], polygon[i], point, true))
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        for (size_t i = 1, count = polygon.size(); i < count; ++i)
        {
            if (Geometry::is_intersected(start, end, polygon[i - 1], polygon[i], point))
            {
                return true;
            }
        }
        if (inside)
        {
            return Geometry::is_inside(start, polygon) || Geometry::is_inside(end, polygon);
        }
        else
        {
            return false;
        }
    }
}

bool Geometry::is_intersected(const Geometry::Point &start, const Geometry::Point &end, const Geometry::Rectangle &rect, const bool infinite, const bool inside)
{
    if (rect.empty() || (!infinite && !Geometry::is_intersected(rect.bounding_rect(), start, end)))
    {
        return false;
    }

    Geometry::Point point;
    if (infinite)
    {
        for (size_t i = 1; i < 4; ++i)
        {
            if (Geometry::is_intersected(start, end, rect[i - 1], rect[i], point, true))
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        for (size_t i = 1; i < 4; ++i)
        {
            if (Geometry::is_intersected(start, end, rect[i - 1], rect[i], point))
            {
                return true;
            }
        }
        if (inside)
        {
            return Geometry::is_inside(start, rect) || Geometry::is_inside(end, rect);
        }
        else
        {
            return false;
        }
    }
}

bool Geometry::is_intersected(const Geometry::AABBRect &rect0, const Geometry::AABBRect &rect1, const bool inside)
{
    if (rect0.empty() || rect1.empty())
    {
        return false;
    }
    
    if (rect0.right() < rect1.left() || rect0.left() > rect1.right() || rect0.bottom() > rect1.top() || rect0.top() < rect1.bottom())
    {
        return false;
    }
    
    if (inside)
    {
        return true;
    }
    else
    {
        return !((rect0.top() < rect1.top() && rect0.right() < rect1.right() && rect0.bottom() > rect1.bottom() && rect0.left() > rect1.left())
            || (rect1.top() < rect0.top() && rect1.right() < rect0.right() && rect1.bottom() > rect0.bottom() && rect1.left() > rect0.left()));
    }
}

bool Geometry::is_intersected(const Geometry::Polyline &polyline0, const Geometry::Polyline &polyline1)
{
    if (polyline0.empty() || polyline1.empty() || !Geometry::is_intersected(polyline0.bounding_rect(), polyline1.bounding_rect()))
    {
        return false;
    }
    Geometry::Point point;
    for (size_t i = 1, count0 = polyline0.size(); i < count0; ++i)
    {
        for (size_t j = 1, count1 = polyline1.size(); j < count1; ++j)
        {
            if (Geometry::is_intersected(polyline0[i-1], polyline0[i], polyline1[j-1], polyline1[j], point))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Polyline &polyline, const Geometry::Polygon &polygon, const bool inside)
{
    if (polyline.empty() || polygon.empty() || !Geometry::is_intersected(polygon.bounding_rect(), polyline.bounding_rect()))
    {
        return false;
    }

    Geometry::Point point;
    for (size_t i = 1, count0 = polyline.size(); i < count0; ++i)
    {
        for (size_t j = 1, count1 = polygon.size(); j < count1; ++j)
        {
            if (Geometry::is_intersected(polyline[i-1], polyline[i], polygon[j-1], polygon[j], point))
            {
                return true;
            }
            else if (inside && Geometry::is_inside(polyline[i-1], polygon))
            {
                return true;
            }
        }
    }
    if (inside)
    {
        return Geometry::is_inside(polyline.back(), polygon);
    }
    else
    {
        return false;
    }
}

bool Geometry::is_intersected(const Geometry::Polyline &polyline, const Geometry::Rectangle &rect, const bool inside)
{
    if (polyline.empty() || rect.empty() || !Geometry::is_intersected(rect.bounding_rect(), polyline.bounding_rect()))
    {
        return false;
    }

    Geometry::Point point;
    for (size_t i = 1, count0 = polyline.size(); i < count0; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (Geometry::is_intersected(polyline[i-1], polyline[i], rect.last_point(j), rect[j], point))
            {
                return true;
            }
            else if (inside && Geometry::is_inside(polyline[i-1], rect))
            {
                return true;
            }
        }
    }
    if (inside)
    {
        return Geometry::is_inside(polyline.back(), rect);
    }
    else
    {
        return false;
    }
}

bool Geometry::is_intersected(const Geometry::Polyline &polyline, const Geometry::Triangle &triangle, const bool inside)
{
    if (polyline.empty() || triangle.empty())
    {
        return false;
    }

    if (inside)
    {
        for (const Geometry::Point &point : polyline)
        {
            if (Geometry::is_inside(point, triangle, true))
            {
                return true;
            }
        }
    }

    Geometry::Point point;
    for (size_t i = 1, count = polyline.size(); i < count; ++i)
    {
        if (Geometry::is_intersected(triangle[0], triangle[1], polyline[i - 1], polyline[i], point) ||
            Geometry::is_intersected(triangle[1], triangle[2], polyline[i - 1], polyline[i], point) ||
            Geometry::is_intersected(triangle[0], triangle[2], polyline[i - 1], polyline[i], point))
        {
            return true;
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Polyline &polyline, const Geometry::Circle &circle)
{
    for (size_t i = 0, count = polyline.size(); i < count; ++i)
    {
        if (Geometry::distance(circle, polyline[i - 1], polyline[i]) < circle.radius)
        {
            return true;
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Polygon &polygon0, const Geometry::Polygon &polygon1, const bool inside)
{
    if (polygon0.empty() || polygon1.empty() || !Geometry::is_intersected(polygon0.bounding_rect(), polygon1.bounding_rect()))
    {
        return false;
    }
    Geometry::Point point;
    for (size_t i = 1, count0 = polygon0.size(); i < count0; ++i)
    {
        for (size_t j = 1, count1 = polygon1.size(); j < count1; ++j)
        {
            if (Geometry::is_intersected(polygon0[i-1], polygon0[i], polygon1[j-1], polygon1[j], point))
            {
                return true;
            }
        }
    }
    if (inside)
    {
        for (const Geometry::Point &point : polygon0)
        {
            if (Geometry::is_inside(point, polygon1, true))
            {
                return true;
            }
        }
        for (const Geometry::Point &point : polygon1)
        {
            if (Geometry::is_inside(point, polygon0, true))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Polygon &polygon, const Geometry::Rectangle &rect, const bool inside)
{
    if (polygon.empty() || rect.empty() || !Geometry::is_intersected(polygon.bounding_rect(), rect.bounding_rect()))
    {
        return false;
    }

    Geometry::Point point;
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (Geometry::is_intersected(polygon[i-1], polygon[i], rect.last_point(j), rect[j], point))
            {
                return true;
            }
        }
    }
    if (inside)
    {
        for (const Geometry::Point &point : polygon)
        {
            if (Geometry::is_inside(point, rect, true))
            {
                return true;
            }
        }
        for (const Geometry::Point &point : rect)
        {
            if (Geometry::is_inside(point, polygon, true))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Polygon &polygon, const Geometry::Triangle &triangle, const bool inside)
{
    if (polygon.empty() || triangle.empty())
    {
        return false;
    }

    if (inside)
    {
        for (const Geometry::Point & point : polygon)
        {
            if (Geometry::is_inside(point, triangle, true))
            {
                return true;
            }
        }
    }

    if (Geometry::is_intersected(triangle[0], triangle[1], polygon, false, inside) ||
        Geometry::is_intersected(triangle[1], triangle[2], polygon, false, inside) ||
        Geometry::is_intersected(triangle[0], triangle[2], polygon, false, inside))
    {
        return true;
    }

    if (inside)
    {
        if (Geometry::is_inside(triangle[0], polygon, true) ||
            Geometry::is_inside(triangle[1], polygon, true) ||
            Geometry::is_inside(triangle[2], polygon, true))
        {
            return true;
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Polygon &polygon, const Geometry::Circle &circle, const bool inside)
{
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        if (Geometry::distance(circle, polygon[i - 1], polygon[i]) < circle.radius)
        {
            return true;
        }
    }

    if (!inside)
    {
        return false;
    }

    return Geometry::is_inside(circle, polygon, true) || std::any_of(polygon.begin(), polygon.end(), 
        [&](const Geometry::Point &point) { return Geometry::is_inside(point, circle, true); });
}

bool Geometry::is_intersected(const Geometry::Circle &circle0, const Geometry::Circle &circle1, const bool inside)
{
    if (inside)
    {
        return Geometry::distance(circle0, circle1) <= circle0.radius + circle1.radius;
    }
    else
    {
        const double distance = Geometry::distance(circle0, circle1);
        return distance <= circle0.radius + circle1.radius && distance >= std::abs(circle0.radius - circle1.radius);
    }
}

bool Geometry::is_intersected(const Geometry::Circle &circle, const Geometry::Triangle &triangle)
{
    if (circle.empty() || triangle.empty())
    {
        return false;
    }

    return Geometry::is_inside(circle, triangle, true) ||
        Geometry::distance_square(circle, triangle[0], triangle[1]) <= circle.radius * circle.radius ||
        Geometry::distance_square(circle, triangle[1], triangle[2]) <= circle.radius * circle.radius ||
        Geometry::distance_square(circle, triangle[0], triangle[2]) <= circle.radius * circle.radius;
}

bool Geometry::is_intersected(const Geometry::Rectangle &rect0, const Geometry::Rectangle &rect1, const bool inside)
{
    if (rect0.empty() || rect1.empty() || !Geometry::is_intersected(rect0.bounding_rect(), rect1.bounding_rect()))
    {
        return false;
    }

    Geometry::Point point;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (Geometry::is_intersected(rect0.last_point(i), rect0[i], rect1.last_point(j), rect1[j], point))
            {
                return true;
            }
        }
    }
    if (inside)
    {
        for (const Geometry::Point &point : rect0)
        {
            if (Geometry::is_inside(point, rect1, true))
            {
                return true;
            }
        }
        for (const Geometry::Point &point : rect1)
        {
            if (Geometry::is_inside(point, rect0, true))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Rectangle &rect, const Geometry::Circle &circle, const bool inside)
{
    if (circle.empty() || rect.empty() || !Geometry::is_intersected(rect.bounding_rect(), circle.bounding_rect()))
    {
        return false;
    }

    if (inside)
    {
        for (const Geometry::Point &point : rect)
        {
            if (Geometry::is_inside(point, circle))
            {
                return true;
            }
        }
    }
    if (Geometry::distance(circle, rect) <= circle.radius)
    {
        return true;
    }
    return inside && Geometry::is_inside(circle, rect);
}

bool Geometry::is_intersected(const Geometry::Rectangle &rect, const Geometry::Triangle &triangle, const bool inside)
{
    if (rect.empty() || triangle.empty())
    {
        return false;
    }

    if (inside)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            if (Geometry::is_inside(rect[i], triangle, true))
            {
                return true;
            }
        }
        for (size_t i = 0; i < 3; ++i)
        {
            if (Geometry::is_inside(triangle[i], rect, true))
            {
                return true;
            }
        }
    }

    Geometry::Point point;
    for (size_t i = 1; i < 4; ++i)
    {
        if (Geometry::is_intersected(triangle[0], triangle[1], rect[i - 1], rect[i], point) ||
           Geometry::is_intersected(triangle[1], triangle[2], rect[i - 1], rect[i], point) ||
           Geometry::is_intersected(triangle[0], triangle[2], rect[i - 1], rect[i], point))
        {
            return true;
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Square &square0, const Geometry::Square &square1, const bool inside)
{
    if (square0.empty() || square1.empty() || !Geometry::is_intersected(Geometry::Circle(square0.center(), square0.outer_circle_radius()),
        Geometry::Circle(square1.center(), square1.outer_circle_radius())))
    {
        return false;
    }

    Geometry::Point point;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (Geometry::is_intersected(square0.last_point(i), square0[i], square1.last_point(j), square1[j], point))
            {
                return true;
            }
        }
    }

    if (inside)
    {
        for (const Geometry::Point &point : square0)
        {
            if (Geometry::is_inside(point, square1, true))
            {
                return true;
            }
        }
        for (const Geometry::Point &point : square1)
        {
            if (Geometry::is_inside(point, square0, true))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Square &square, const Geometry::Circle &circle, const bool inside)
{
    if (square.empty() || circle.empty() || !Geometry::is_intersected(circle,
        Geometry::Circle(square.center(), square.outer_circle_radius())))
    {
        return false;
    }

    if (inside)
    {
        for (const Geometry::Point &point : square)
        {
            if (Geometry::is_inside(point, circle))
            {
                return true;
            }
        }
    }
    if (Geometry::distance(circle, square) <= circle.radius)
    {
        return true;
    }
    return inside && Geometry::is_inside(circle, square);
}

bool Geometry::is_intersected(const Geometry::Triangle &triangle0, const Geometry::Triangle &triangle1, const bool inside)
{
    if (triangle0.empty() || triangle1.empty())
    {
        return false;
    }

    if (inside)
    {
        if (Geometry::is_inside(triangle0[0], triangle1, true) || Geometry::is_inside(triangle0[1], triangle1, true) ||
            Geometry::is_inside(triangle0[2], triangle1, true) || Geometry::is_inside(triangle1[0], triangle0, true) ||
            Geometry::is_inside(triangle1[1], triangle0, true) || Geometry::is_inside(triangle1[2], triangle0, true))
        {
            return true;
        }
    }

    Geometry::Point point;
    for (size_t i = 1; i < 4; ++i)
    {
        for (size_t j = 1; j < 4; ++j)
        {
            if (Geometry::is_intersected(triangle0[i - 1], triangle0[i % 3], triangle1[j - 1], triangle1[j % 3], point))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::AABBRect &rect, const Geometry::Point &point0, const Geometry::Point &point1)
{
    if (Geometry::is_inside(point0, rect) || Geometry::is_inside(point1, rect))
    {
        return true;
    }

    const double x_max = std::max(point0.x, point1.x);
    const double x_min = std::min(point0.x, point1.x);
    const double y_max = std::max(point0.y, point1.y);
    const double y_min = std::min(point0.y, point1.y);

    if (x_max < rect.left() || x_min > rect.right() || y_max < rect.bottom() || y_min > rect.top())
    {
        return false;
    }
    else
    {
        if ((x_min >= rect.left() && x_max <= rect.right()) || (y_min >= rect.bottom() && y_max <= rect.top()))
        {
            return true;
        }
        else
        {
            const double dx = point1.x - point0.x;
            const double dy = point1.y - point0.y;
            const bool b0 = (rect[0].x - point0.x) * dy >= (rect[0].y - point0.y) * dx;
            const bool b1 = (rect[1].x - point0.x) * dy >= (rect[1].y - point0.y) * dx;
            const bool b2 = (rect[2].x - point0.x) * dy >= (rect[2].y - point0.y) * dx;
            const bool b3 = (rect[3].x - point0.x) * dy >= (rect[3].y - point0.y) * dx;
            return !(b0 == b1 && b1 == b2 && b2 == b3);
        }
    }
}

bool Geometry::is_intersected(const Geometry::AABBRect &rect, const Geometry::Line &line)
{
    return Geometry::is_intersected(rect, line.front(), line.back());
}

bool Geometry::is_intersected(const Geometry::AABBRect &rect, const Geometry::Polyline &polyline)
{
    if (polyline.empty() || !Geometry::is_intersected(rect, polyline.bounding_rect()))
    {
        return false;
    }
    
    for (size_t i = 1, count = polyline.size(); i < count; ++i)
    {
        if (Geometry::is_intersected(rect, polyline[i - 1], polyline[i]))
        {
            return true;
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::AABBRect &rect, const Geometry::Polygon &polygon)
{
    if (polygon.empty() || !Geometry::is_intersected(rect, polygon.bounding_rect()))
    {
        return false;
    }
    
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        if (Geometry::is_intersected(rect, polygon[i - 1], polygon[i]))
        {
            return true;
        }
    }
    for (size_t i = 0; i < 4; ++i)
    {
        if (Geometry::is_inside(rect[i], polygon))
        {
            return true;
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::AABBRect &rect, const Geometry::Circle &circle)
{
    if (circle.empty() || !Geometry::is_intersected(rect, circle.bounding_rect()))
    {
        return false;
    }

    if (Geometry::is_inside(circle, rect, true))
    {
        return true;
    }
    for (const Geometry::Point &point : rect)
    {
        if (Geometry::is_inside(point, circle, true))
        {
            return true;
        }
    }
    for (size_t i = 1; i < 5; ++i)
    {
        if (Geometry::distance(circle, rect[i-1], rect[i]) <= circle.radius)
        {
            return true;
        }
    }
    return false;
}

bool Geometry::is_intersected(const Geometry::Point &start, const Geometry::Point &end, const Geometry::Triangle &triangle, Geometry::Point &output0, Geometry::Point &output1)
{
    if (Geometry::is_inside(start, end, triangle) || !Geometry::is_intersected(triangle.bounding_rect(), start, end))
    {
        return false;
    }

    return (Geometry::is_intersected(start, end, triangle[0], triangle[1], output0) ||
        Geometry::is_intersected(start, end, triangle[1], triangle[2], output0) ||
        Geometry::is_intersected(start, end, triangle[0], triangle[2], output0)) ||
        (Geometry::is_intersected(start, end, triangle[0], triangle[2], output1) ||
        Geometry::is_intersected(start, end, triangle[1], triangle[2], output1) ||
        Geometry::is_intersected(start, end, triangle[0], triangle[1], output1));
}

bool Geometry::is_intersected(const Geometry::Line &line, const Geometry::Triangle &triangle, Geometry::Point &output0, Geometry::Point &output1)
{
    return Geometry::is_intersected(line.front(), line.back(), triangle, output0, output1);
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::Polyline &polyline0, const Geometry::Polyline &polyline1)
{
    Geometry::Point point;
    for (size_t i = 1, count0 = polyline0.size(); i < count0; ++i)
    {
        for (size_t j = 1, count1 = polyline1.size(); j < count1; ++j)
        {
            if (Geometry::is_intersected(polyline0[i-1], polyline0[i], polyline1[j-1], polyline1[j], point))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::Polyline &polyline, const Geometry::Polygon &polygon, const bool inside)
{
    Geometry::Point point;
    for (size_t i = 1, count0 = polyline.size(); i < count0; ++i)
    {
        for (size_t j = 1, count1 = polygon.size(); j < count1; ++j)
        {
            if (Geometry::is_intersected(polyline[i-1], polyline[i], polygon[j-1], polygon[j], point))
            {
                return true;
            }
            else if (inside && Geometry::is_inside(polyline[i-1], polygon))
            {
                return true;
            }
        }
    }
    if (inside)
    {
        return Geometry::is_inside(polyline.back(), polygon);
    }
    else
    {
        return false;
    }
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::Polyline &polyline, const Geometry::Rectangle &rect, const bool inside)
{
    Geometry::Point point;
    for (size_t i = 1, count0 = polyline.size(); i < count0; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (Geometry::is_intersected(polyline[i-1], polyline[i], rect.last_point(j), rect[j], point))
            {
                return true;
            }
            else if (inside && Geometry::is_inside(polyline[i-1], rect))
            {
                return true;
            }
        }
    }
    if (inside)
    {
        return Geometry::is_inside(polyline.back(), rect);
    }
    else
    {
        return false;
    }
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::Polygon &polygon0, const Geometry::Polygon &polygon1, const bool inside)
{
    Geometry::Point point;
    for (size_t i = 1, count0 = polygon0.size(); i < count0; ++i)
    {
        for (size_t j = 1, count1 = polygon1.size(); j < count1; ++j)
        {
            if (Geometry::is_intersected(polygon0[i-1], polygon0[i], polygon1[j-1], polygon1[j], point))
            {
                return true;
            }
        }
    }
    if (inside)
    {
        for (const Geometry::Point &point : polygon0)
        {
            if (Geometry::is_inside(point, polygon1, true))
            {
                return true;
            }
        }
        for (const Geometry::Point &point : polygon1)
        {
            if (Geometry::is_inside(point, polygon0, true))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::Polygon &polygon, const Geometry::Rectangle &rect, const bool inside)
{
    Geometry::Point point;
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (Geometry::is_intersected(polygon[i-1], polygon[i], rect.last_point(j), rect[j], point))
            {
                return true;
            }
        }
    }
    if (inside)
    {
        for (const Geometry::Point &point : polygon)
        {
            if (Geometry::is_inside(point, rect, true))
            {
                return true;
            }
        }
        for (const Geometry::Point &point : rect)
        {
            if (Geometry::is_inside(point, polygon, true))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::Rectangle &rect0, const Geometry::Rectangle &rect1, const bool inside)
{
    Geometry::Point point;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (Geometry::is_intersected(rect0.last_point(i), rect0[i], rect1.last_point(j), rect1[j], point))
            {
                return true;
            }
        }
    }
    if (inside)
    {
        for (const Geometry::Point &point : rect0)
        {
            if (Geometry::is_inside(point, rect1, true))
            {
                return true;
            }
        }
        for (const Geometry::Point &point : rect1)
        {
            if (Geometry::is_inside(point, rect0, true))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::Rectangle &rect, const Geometry::Circle &circle, const bool inside)
{
    if (inside)
    {
        for (const Geometry::Point &point : rect)
        {
            if (Geometry::is_inside(point, circle))
            {
                return true;
            }
        }
    }
    if (Geometry::distance(circle, rect) <= circle.radius)
    {
        return true;
    }
    return inside && Geometry::is_inside(circle, rect);
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::Square &square0, const Geometry::Square &square1, const bool inside)
{
    Geometry::Point point;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (Geometry::is_intersected(square0.last_point(i), square0[i], square1.last_point(j), square1[j], point))
            {
                return true;
            }
        }
    }

    if (inside)
    {
        for (const Geometry::Point &point : square0)
        {
            if (Geometry::is_inside(point, square1, true))
            {
                return true;
            }
        }
        for (const Geometry::Point &point : square1)
        {
            if (Geometry::is_inside(point, square0, true))
            {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::Square &square, const Geometry::Circle &circle, const bool inside)
{
    if (inside)
    {
        for (const Geometry::Point &point : square)
        {
            if (Geometry::is_inside(point, circle))
            {
                return true;
            }
        }
    }
    if (Geometry::distance(circle, square) <= circle.radius)
    {
        return true;
    }
    return inside && Geometry::is_inside(circle, square);
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::AABBRect &rect, const Geometry::Polyline &polyline)
{
    for (size_t i = 1, count = polyline.size(); i < count; ++i)
    {
        if (Geometry::is_intersected(rect, polyline[i - 1], polyline[i]))
        {
            return true;
        }
    }
    return false;
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::AABBRect &rect, const Geometry::Polygon &polygon)
{
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        if (Geometry::is_intersected(rect, polygon[i - 1], polygon[i]))
        {
            return true;
        }
    }
    for (size_t i = 0; i < 4; ++i)
    {
        if (Geometry::is_inside(rect[i], polygon))
        {
            return true;
        }
    }
    return false;
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::GeometryObject *object0, const Geometry::GeometryObject *object1, const bool infinite, const bool inside)
{
    switch (object0->type())
    {
    case Geometry::Type::POLYGON:
        switch (object1->type())
        {
        case Geometry::Type::POLYGON:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polygon *>(object0),
                *static_cast<const Geometry::Polygon *>(object1), inside);
        case Geometry::Type::RECTANGLE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polygon *>(object0),
                *static_cast<const Geometry::Rectangle *>(object1), inside);
        case Geometry::Type::AABBRECT:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::AABBRect *>(object1),
                *static_cast<const Geometry::Polygon *>(object0), inside);
        case Geometry::Type::SQUARE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polygon *>(object0),
                *static_cast<const Geometry::Square *>(object1), inside);
        case Geometry::Type::POLYLINE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polyline *>(object1),
                *static_cast<const Geometry::Polygon *>(object0), inside);
        case Geometry::Type::BEZIER:
            return Geometry::NoAABBTest::is_intersected(static_cast<const Geometry::Bezier *>(object1)->shape(),
                *static_cast<const Geometry::Polygon *>(object0), inside);
        case Geometry::Type::CIRCLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Polygon *>(object0),
                *static_cast<const Geometry::Circle *>(object1), inside);
        case Geometry::Type::TRIANGLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Polygon *>(object0),
                *static_cast<const Geometry::Triangle *>(object1), inside);
        case Geometry::Type::LINE:
            return Geometry::is_intersected(static_cast<const Geometry::Line *>(object1)->front(),
                static_cast<const Geometry::Line *>(object1)->back(),
                *static_cast<const Geometry::Polygon *>(object0), infinite, inside);
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(object1),
                *static_cast<const Geometry::Polygon *>(object0), true);
        default:
            return false;
        }
    case Geometry::Type::RECTANGLE:
        switch (object1->type())
        {
        case Geometry::Type::POLYGON:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polygon *>(object1),
                *static_cast<const Geometry::Rectangle *>(object0), inside);
        case Geometry::Type::RECTANGLE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Rectangle *>(object0),
                *static_cast<const Geometry::Rectangle *>(object1), inside);
        case Geometry::Type::AABBRECT:
            return Geometry::is_intersected(*static_cast<const Geometry::AABBRect *>(object1),
                *static_cast<const Geometry::Rectangle *>(object0), inside);
        case Geometry::Type::SQUARE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Rectangle *>(object0),
                *static_cast<const Geometry::Square *>(object1), inside);
        case Geometry::Type::POLYLINE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polyline *>(object1),
                *static_cast<const Geometry::Rectangle *>(object0), inside);
        case Geometry::Type::BEZIER:
            return Geometry::NoAABBTest::is_intersected(static_cast<const Geometry::Bezier *>(object1)->shape(),
                *static_cast<const Geometry::Rectangle *>(object0), inside);
        case Geometry::Type::CIRCLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Rectangle *>(object0),
                *static_cast<const Geometry::Circle *>(object1), inside);
        case Geometry::Type::TRIANGLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Rectangle *>(object0),
                *static_cast<const Geometry::Triangle *>(object1), inside);
        case Geometry::Type::LINE:
            return Geometry::is_intersected(*static_cast<const Geometry::AABBRect *>(object0),
                *static_cast<const Geometry::Line *>(object1));
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(object1),
                *static_cast<const Geometry::AABBRect *>(object0), true);
        default:
            return false;
        }
    case Geometry::Type::AABBRECT:
        switch (object1->type())
        {
        case Geometry::Type::POLYGON:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::AABBRect *>(object0),
                *static_cast<const Geometry::Polygon *>(object1));
        case Geometry::Type::RECTANGLE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::AABBRect *>(object0),
                *static_cast<const Geometry::Rectangle *>(object1), inside);
        case Geometry::Type::AABBRECT:
            return Geometry::is_intersected(*static_cast<const Geometry::AABBRect *>(object0),
                *static_cast<const Geometry::AABBRect *>(object1), inside);
        case Geometry::Type::SQUARE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::AABBRect *>(object0),
                *static_cast<const Geometry::Square *>(object1), inside);
        case Geometry::Type::POLYLINE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::AABBRect *>(object0),
                *static_cast<const Geometry::Polyline *>(object1));
        case Geometry::Type::BEZIER:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::AABBRect *>(object0),
                static_cast<const Geometry::Bezier *>(object1)->shape());
        case Geometry::Type::CIRCLE:
            return Geometry::is_intersected(*static_cast<const Geometry::AABBRect *>(object0),
                *static_cast<const Geometry::Circle *>(object1));
        case Geometry::Type::TRIANGLE:
            return Geometry::is_intersected(*static_cast<const Geometry::AABBRect *>(object0),
                *static_cast<const Geometry::Triangle *>(object1), inside);
        case Geometry::Type::LINE:
            return Geometry::is_intersected(*static_cast<const Geometry::AABBRect *>(object0),
                *static_cast<const Geometry::Line *>(object1));
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(object1),
                *static_cast<const Geometry::AABBRect *>(object0), true);
        default:
            return false;
        }
    case Geometry::Type::SQUARE:
        switch (object1->type())
        {
        case Geometry::Type::POLYGON:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polygon *>(object1),
                *static_cast<const Geometry::Square *>(object0), inside);
        case Geometry::Type::RECTANGLE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Square *>(object0),
                *static_cast<const Geometry::Rectangle *>(object1), inside);
        case Geometry::Type::AABBRECT:
            return Geometry::is_intersected(*static_cast<const Geometry::AABBRect *>(object1),
                *static_cast<const Geometry::Square *>(object0), inside);
        case Geometry::Type::SQUARE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Square *>(object0),
                *static_cast<const Geometry::Square *>(object1), inside);
        case Geometry::Type::POLYLINE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polyline *>(object1),
                *static_cast<const Geometry::Square *>(object0), inside);
        case Geometry::Type::BEZIER:
            return Geometry::NoAABBTest::is_intersected(static_cast<const Geometry::Bezier *>(object1)->shape(),
                *static_cast<const Geometry::Square *>(object0), inside);
        case Geometry::Type::CIRCLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Square *>(object0),
                *static_cast<const Geometry::Circle *>(object1), inside);
        case Geometry::Type::TRIANGLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Square *>(object0),
                *static_cast<const Geometry::Triangle *>(object1), inside);
        case Geometry::Type::LINE:
            return Geometry::is_intersected(static_cast<const Geometry::Line *>(object1)->front(),
                static_cast<const Geometry::Line *>(object1)->back(),
                *static_cast<const Geometry::Square *>(object0), infinite, inside);
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(object1),
                *static_cast<const Geometry::Square *>(object0), true);
        default:
            return false;
        }
    case Geometry::Type::POLYLINE:
        switch (object1->type())
        {
        case Geometry::Type::POLYGON:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polyline *>(object0),
                *static_cast<const Geometry::Polygon *>(object1), inside);
        case Geometry::Type::RECTANGLE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polyline *>(object0),
                *static_cast<const Geometry::Rectangle *>(object1), inside);
        case Geometry::Type::AABBRECT:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::AABBRect *>(object1),
                *static_cast<const Geometry::Polyline *>(object0));
        case Geometry::Type::SQUARE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polyline *>(object0),
                *static_cast<const Geometry::Square *>(object1), inside);
        case Geometry::Type::POLYLINE:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polyline *>(object0),
                *static_cast<const Geometry::Polyline *>(object1));
        case Geometry::Type::BEZIER:
            return Geometry::NoAABBTest::is_intersected(*static_cast<const Geometry::Polyline *>(object0),
                static_cast<const Geometry::Bezier *>(object1)->shape());
        case Geometry::Type::CIRCLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Polyline *>(object0),
                *static_cast<const Geometry::Circle *>(object1));
        case Geometry::Type::TRIANGLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Polyline *>(object0),
                *static_cast<const Geometry::Triangle *>(object1), inside);
        case Geometry::Type::LINE:
            return Geometry::is_intersected(static_cast<const Geometry::Line *>(object1)->front(),
                static_cast<const Geometry::Line *>(object1)->back(),
                *static_cast<const Geometry::Polyline *>(object0), infinite);
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(object1),
                *static_cast<const Geometry::Polyline *>(object0));
        default:
            return false;
        }
    case Geometry::Type::CIRCLE:
        switch (object1->type())
        {
        case Geometry::Type::POLYGON:
            return Geometry::is_intersected(*static_cast<const Geometry::Polygon *>(object1),
                *static_cast<const Geometry::Circle *>(object0), inside);
        case Geometry::Type::RECTANGLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Rectangle *>(object1),
                *static_cast<const Geometry::Circle *>(object0), inside);
        case Geometry::Type::AABBRECT:
            return Geometry::is_intersected(*static_cast<const Geometry::AABBRect *>(object1),
                *static_cast<const Geometry::Circle *>(object0));
        case Geometry::Type::SQUARE:
            return Geometry::is_intersected(*static_cast<const Geometry::Square *>(object1),
                *static_cast<const Geometry::Circle *>(object0), inside);
        case Geometry::Type::POLYLINE:
            return Geometry::is_intersected(*static_cast<const Geometry::Polyline *>(object1),
                *static_cast<const Geometry::Circle *>(object0));
        case Geometry::Type::BEZIER:
            return Geometry::is_intersected(static_cast<const Geometry::Bezier *>(object1)->shape(),
                *static_cast<const Geometry::Circle *>(object0));
        case Geometry::Type::CIRCLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Circle *>(object0),
                *static_cast<const Geometry::Circle *>(object1), inside);
        case Geometry::Type::TRIANGLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Circle *>(object0),
                *static_cast<const Geometry::Triangle *>(object1));
        case Geometry::Type::LINE:
            return Geometry::distance(*static_cast<const Geometry::Circle *>(object0),
                *static_cast<const Geometry::Line *>(object1), infinite) <= static_cast<const Geometry::Circle *>(object0)->radius;
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(object1),
                *static_cast<const Geometry::Circle *>(object0), true);
        default:
            return false;
        }
    case Geometry::Type::TRIANGLE:
        switch (object1->type())
        {
        case Geometry::Type::POLYGON:
            return Geometry::is_intersected(*static_cast<const Geometry::Polygon *>(object1),
                *static_cast<const Geometry::Triangle *>(object0), inside);
        case Geometry::Type::RECTANGLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Rectangle *>(object1),
                *static_cast<const Geometry::Triangle *>(object0), inside);
        case Geometry::Type::AABBRECT:
            return Geometry::is_intersected(*static_cast<const Geometry::AABBRect *>(object1),
                *static_cast<const Geometry::Triangle *>(object0), inside);
        case Geometry::Type::SQUARE:
            return Geometry::is_intersected(*static_cast<const Geometry::Square *>(object1),
                *static_cast<const Geometry::Triangle *>(object0), inside);
        case Geometry::Type::POLYLINE:
            return Geometry::is_intersected(*static_cast<const Geometry::Polyline *>(object1),
                *static_cast<const Geometry::Triangle *>(object0), inside);
        case Geometry::Type::BEZIER:
            return Geometry::is_intersected(static_cast<const Geometry::Bezier *>(object1)->shape(),
                *static_cast<const Geometry::Triangle *>(object0), inside);
        case Geometry::Type::CIRCLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Circle *>(object1),
                *static_cast<const Geometry::Triangle *>(object0));
        case Geometry::Type::TRIANGLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Triangle *>(object0),
                *static_cast<const Geometry::Triangle *>(object1), inside);
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(object1),
                *static_cast<const Geometry::Triangle *>(object0), true);
        default:
            return false;
        }
    case Geometry::Type::LINE:
        switch (object1->type())
        {
        case Geometry::Type::POLYGON:
            return Geometry::is_intersected(static_cast<const Geometry::Line *>(object0)->front(),
                static_cast<const Geometry::Line *>(object0)->back(),
                *static_cast<const Geometry::Polygon *>(object1), infinite, inside);
        case Geometry::Type::RECTANGLE:
            return Geometry::is_intersected(static_cast<const Geometry::Line *>(object0)->front(),
                static_cast<const Geometry::Line *>(object0)->back(),
                *static_cast<const Geometry::Rectangle *>(object1), infinite, inside);
        case Geometry::Type::AABBRECT:
            return Geometry::is_intersected(*static_cast<const Geometry::AABBRect *>(object1),
                static_cast<const Geometry::Line *>(object0)->front(),
                static_cast<const Geometry::Line *>(object0)->back());
        case Geometry::Type::SQUARE:
            return Geometry::is_intersected(static_cast<const Geometry::Line *>(object0)->front(),
                static_cast<const Geometry::Line *>(object0)->back(),
                *static_cast<const Geometry::Square *>(object1), infinite, inside);
        case Geometry::Type::POLYLINE:
            return Geometry::is_intersected(static_cast<const Geometry::Line *>(object0)->front(),
                static_cast<const Geometry::Line *>(object0)->back(),
                *static_cast<const Geometry::Polyline *>(object1), infinite);
        case Geometry::Type::BEZIER:
            return Geometry::is_intersected(static_cast<const Geometry::Line *>(object0)->front(),
                static_cast<const Geometry::Line *>(object0)->back(),
                static_cast<const Geometry::Bezier *>(object1)->shape(), infinite);
        case Geometry::Type::CIRCLE:
            return Geometry::distance(*static_cast<const Geometry::Circle *>(object1),
                *static_cast<const Geometry::Line *>(object0), infinite) <= static_cast<const Geometry::Circle *>(object1)->radius;
        case Geometry::Type::TRIANGLE:
            return Geometry::is_intersected(*static_cast<const Geometry::Triangle *>(object0),
                *static_cast<const Geometry::Triangle *>(object1), inside);
        case Geometry::Type::LINE:
            {
                Geometry::Point point;
                return Geometry::is_intersected(*static_cast<const Geometry::Line *>(object0),
                    *static_cast<const Geometry::Line *>(object1), point, infinite);
            }
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(object1),
                *static_cast<const Geometry::Line *>(object0), infinite);
        default:
            return false;
        }
    default:
        return false;
    }
}

bool Geometry::NoAABBTest::is_intersected(const Geometry::AABBRect &rect, const Geometry::GeometryObject *object, const bool infinite, const bool inside)
{
    switch (object->type())
    {
    case Geometry::Type::POLYGON:
        return Geometry::NoAABBTest::is_intersected(rect,
            *static_cast<const Geometry::Polygon *>(object), inside);
    case Geometry::Type::RECTANGLE:
        return Geometry::NoAABBTest::is_intersected(rect,
            *static_cast<const Geometry::Rectangle *>(object), inside);
    case Geometry::Type::AABBRECT:
        return Geometry::is_intersected(rect,
            *static_cast<const Geometry::AABBRect *>(object), inside);
    case Geometry::Type::SQUARE:
        return Geometry::NoAABBTest::is_intersected(rect,
            *static_cast<const Geometry::Square *>(object), inside);
    case Geometry::Type::POLYLINE:
        return Geometry::NoAABBTest::is_intersected(rect,
            *static_cast<const Geometry::Polyline *>(object), inside);
    case Geometry::Type::BEZIER:
        return Geometry::NoAABBTest::is_intersected(rect,
            static_cast<const Geometry::Bezier *>(object)->shape(), inside);
    case Geometry::Type::CIRCLE:
        return Geometry::is_intersected(rect,
            *static_cast<const Geometry::Circle *>(object), inside);
    case Geometry::Type::TRIANGLE:
        return Geometry::is_intersected(rect,
            *static_cast<const Geometry::Triangle *>(object), inside);
    case Geometry::Type::LINE:
        return Geometry::is_intersected(rect,
            *static_cast<const Geometry::Line *>(object));
    case Geometry::Type::POINT:
        return Geometry::is_inside(*static_cast<const Geometry::Point *>(object), rect, true);
    default:
        return false;
    }
}

bool Geometry::is_intersected(const Geometry::GeometryObject *object0, const Geometry::GeometryObject *object1, const bool infinite, const bool inside)
{
    if (!Geometry::is_intersected(object0->bounding_rect(), object1->bounding_rect()))
    {
        return false;
    }

    return Geometry::NoAABBTest::is_intersected(object0, object1, infinite, inside);
}

bool Geometry::is_intersected(const Geometry::AABBRect &rect, const Geometry::GeometryObject *object, const bool infinite, const bool inside)
{
    if (!Geometry::is_intersected(rect, object->bounding_rect()))
    {
        return false;
    }

    return Geometry::NoAABBTest::is_intersected(rect, object, infinite, inside);
}


bool Geometry::is_on_left(const Geometry::Point &point, const Geometry::Point &start, const Geometry::Point &end)
{
    return (end.x - start.x) * (point.y - start.y) - (end.y - start.y) * (point.x - end.x) > 0;
}



bool Geometry::is_Rectangle(const Geometry::Polygon &polygon)
{
    Geometry::Polygon points(polygon);
    if (polygon.size() > 5)
    {
        for (size_t i = 2, count = polygon.size(); i < count; ++i)
        {
            if (Geometry::is_inside(points[i - 1], points[i - 2], points[i]))
            {
                points.remove(--i);
                --count;
            }
        }
    }
    if (polygon.size() != 5)
    {
        return false;
    }

    if (Geometry::distance(points[0], points[1]) == Geometry::distance(points[2], points[3]) &&
        Geometry::distance(points[1], points[2]) == Geometry::distance(points[0], points[3]))
    {
        const Geometry::Point vec0 = points[0] - points[1], vec1 = points[2] - points[1];
        return std::abs(vec0.x * vec1.x + vec0.y * vec1.y) == 0;
    }
    else
    {
        return false;
    }
}


double Geometry::cross(const double x0, const double y0, const double x1, const double y1)
{
    return x0 * y1 - x1 * y0;
}

double Geometry::cross(const Geometry::Vector &vec0, const Geometry::Vector &vec1)
{
    return vec0.x * vec1.y - vec1.x * vec0.y;
}

double Geometry::cross(const Geometry::Point &start0, const Geometry::Point &end0, const Geometry::Point &start1, const Geometry::Point &end1)
{
    return Geometry::cross(end0 - start0, end1 - start1);
}

bool Geometry::foot_point(const Geometry::Point &start, const Geometry::Point &end, const Geometry::Point &point, Geometry::Point &foot, const bool infinite)
{
    if (start.x == end.x)
    {
        foot.x = start.x;
        foot.y = point.y;
        if (infinite)
        {
            return true;
        }
        else
        {
            return foot.y >= std::min(start.y, end.y) && foot.y <= std::max(start.y, end.y);
        }
    }
    else
    {
        const double k = (end.y - start.y) / (end.x - start.x);
        const double b = start.y -  k * start.x;
        foot.x = (point.x - k * b + k * point.y) / (1 + k * k);
        foot.y = (k * point.x + k * k * point.y + b) / (1 + k * k);
        if (infinite)
        {
            return true;
        }
        else
        {
            return foot.x >= std::min(start.x, end.x) && foot.x <= std::max(start.x, end.x);
        }
    }
}

bool Geometry::foot_point(const Geometry::Line &line, const Geometry::Point &point, Geometry::Point &foot, const bool infinite)
{
    return Geometry::foot_point(line.front(), line.back(), point, foot, infinite);
}


double Geometry::angle(const Geometry::Point &start, const Geometry::Point &end)
{
    const Geometry::Point vec = start - end;
    if (vec.y > 0)
    {
        return std::acos(vec.x / vec.length());
    }
    else
    {
        return -std::acos(vec.x / vec.length());
    }
}

double Geometry::angle(const Geometry::Point &point0, const Geometry::Point &point1, const Geometry::Point &point2)
{
    const Geometry::Point vec0 = point0 - point1, vec1 = point2 - point1;
    if (vec0.cross(vec1) > 0)
    {
        return std::acos(vec0 * vec1 / (vec0.length() * vec1.length()));
    }
    else
    {
        return -std::acos(vec0 * vec1 / (vec0.length() * vec1.length()));
    }
}

double Geometry::angle(const Geometry::Point &start0, const Geometry::Point &end0, const Geometry::Point &start1, const Geometry::Point &end1)
{
    const Geometry::Point vec0 = end0 - start0, vec1 = end1 - start1;
    if (vec0.cross(vec1) > 0)
    {
        return std::acos(vec0 * vec1 / (vec0.length() * vec1.length()));
    }
    else
    {
        return -std::acos(vec0 * vec1 / (vec0.length() * vec1.length()));
    }
}

double Geometry::angle(const Geometry::Line &line0, const Geometry::Line &line1)
{
    const Geometry::Point vec0 = line0.back() - line0.front(), vec1 = line1.back() - line1.front();
    if (vec0.cross(vec1) > 0)
    {
        return std::acos(vec0 * vec1 / (vec0.length() * vec1.length()));
    }
    else
    {
        return -std::acos(vec0 * vec1 / (vec0.length() * vec1.length()));
    }
}


double Geometry::rad_to_PI(double value)
{
    if (std::abs(value) > 2 * Geometry::PI)
    {
        value -= (std::round(value / (Geometry::PI * 2)) * 2 * Geometry::PI);
    }
    if (value < -Geometry::PI)
    {
        return value + 2 * Geometry::PI;
    }
    else if (value > Geometry::PI)
    {
        return value - 2 * Geometry::PI;
    }
    else
    {
        return value;
    }
}

double Geometry::rad_to_2PI(double value)
{
    if (std::abs(value) > 2 * Geometry::PI)
    {
        value -= (std::round(value / (Geometry::PI * 2)) * 2 * Geometry::PI);
    }
    if (value < 0)
    {
        value += (2 * Geometry::PI);
    }
    return value;
}

double Geometry::rad_to_degree(double value)
{
    return value * 180 / Geometry::PI;
}


double Geometry::degree_to_180(double value)
{
    if (std::abs(value) > 360)
    {
        value -= (std::round(value / 360) * 360);
    }
    if (value < -180)
    {
        return value + 360;
    }
    else if (value > 180)
    {
        return value - 360;
    }
    else
    {
        return value;
    }
}

double Geometry::degree_to_360(double value)
{
    if (std::abs(value) > 360)
    {
        value -= (std::round(value / 360) * 360);
    }
    if (value < 0)
    {
        value += 360;
    }
    return value;
}

double Geometry::degree_to_rad(double value)
{
    return value * Geometry::PI / 180;
}


bool Geometry::angle_to_arc(const Geometry::Point &point0, const Geometry::Point &point1, const Geometry::Point &point2, const double radius, Geometry::Polyline &arc)
{
    if (radius <= 0)
    {
        return false;
    }

    arc.clear();
    const double len = radius / std::tan(std::abs(Geometry::angle(point0, point1, point2)) / 2);
    if ((point1 - point0).length() >= len && (point2 - point1).length() >= len)
    {
        double c = std::atan(len / radius) * radius;
        const Geometry::Vector vec0 = (point0 - point1).normalize() * len;
        const Geometry::Vector vec1 = (point2 - point1).normalize() * len;
        const Geometry::Point center = point1 + (vec0 + vec1);
        Geometry::Point foot0, foot1;
        Geometry::foot_point(point0, point1, center, foot0, true);
        Geometry::foot_point(point2, point1, center, foot1, true);
        Geometry::Vector vec = (foot0 - center).normalize() * radius;
        double degree = std::asin(0.8 / radius) * 2;
        if (Geometry::angle(foot0, center, foot1) < 0)
        {
            degree = -degree;
        }
        while (c > 0)
        {
            arc.append(center + vec);
            vec.rotate(0, 0, degree);
            c -= 0.8;
        }
        return true;
    }
    else
    {
        return false;
    }
}


Geometry::Polygon Geometry::circle_to_polygon(const double x, const double y, const double r)
{
    double c = r * Geometry::PI;
    const double degree = std::asin(1 / r) * 2;
    Geometry::Vector vec(0, r);
    const Geometry::Point center(x, y);
    std::vector<Geometry::Point> points;
    while (c-- > 0)
    {
        points.emplace_back(center + vec);
        vec.rotate(0, 0, degree);
    }
    return Geometry::Polygon(points.cbegin(), points.cend());
}

Geometry::Polygon Geometry::circle_to_polygon(const Geometry::Circle &circle)
{
    return Geometry::circle_to_polygon(circle.x, circle.y, circle.radius);
}


bool Geometry::polygon_union(const Geometry::Polygon &polygon0, const Geometry::Polygon &polygon1, std::vector<Geometry::Polygon> &output)
{
    Geometry::Polygon polygon2(polygon0), polygon3(polygon1);
    polygon2.reorder_points(false);
    polygon3.reorder_points(false);
    std::vector<Geometry::MarkedPoint> points0, points1;
    for (const Geometry::Point &point : polygon2)
    {
        points0.emplace_back(point.x, point.y);
    }
    for (const Geometry::Point &point : polygon3)
    {
        points1.emplace_back(point.x, point.y);
    }

    Geometry::Point point, pre_point; // 找到交点并计算其几何数
    const Geometry::AABBRect rect(polygon1.bounding_rect());
    for (size_t i = 1, count0 = points0.size(); i < count0; ++i)
    {
        if (!Geometry::is_intersected(rect, points0[i - 1], points0[i])) // 粗筛
        {
            continue;
        }

        pre_point = points0[i - 1];
        for (size_t k = 1, j = 1, count1 = points1.size(); j < count1; ++j)
        {
            k = j - 1;
            while (!points1[k].active)
            {
                --k; // 跳过非活动交点
            }
            while (j < count1 && (points1[k] == points1[j] || !points1[j].active))
            {
                k = j;
                ++j;
                while (!points1[k].active)
                {
                    --k; // 跳过非活动交点
                }
            }
            if (j >= count1)
            {
                continue;
            }
            k = j - 1;
            while (!points1[k].active)
            {
                --k; // 跳过非活动交点
            }

            if (!Geometry::is_parallel(pre_point, points0[i], points1[k], points1[j]) &&
                Geometry::is_intersected(pre_point, points0[i], points1[k], points1[j], point))
            {
                points0.insert(points0.begin() + i++, Geometry::MarkedPoint(point.x, point.y, false));
                points1.insert(points1.begin() + j++, Geometry::MarkedPoint(point.x, point.y, false));
                ++count0;
                ++count1;
                if (Geometry::cross(pre_point, points0[i], points1[k], points1[j]) >= 0)
                {
                    points0[i - 1].value = 1;
                    points1[j - 1].value = -1;
                }
                else
                {
                    points0[i - 1].value = -1;
                    points1[j - 1].value = 1;
                }
            }
        }

        // 将本次循环添加的交点休眠,令下次循环polygon1处于无活动交点状态以排除干扰
        for (Geometry::MarkedPoint &p : points1)
        {
            if (!p.original)
            {
                p.active = false;
            }
        }
    }

    if (points0.size() == polygon0.size()) // 无交点
    {
        if (std::all_of(polygon0.begin(), polygon0.end(), [&](const Geometry::Point &point) { return Geometry::is_inside(point, polygon1, true); }))
        {
            output.emplace_back(polygon1); // 无交点,且polygon0的点都在polygon1内,则并集必然为polygon1
            return true;
        }
        else if (std::all_of(polygon1.begin(), polygon1.end(), [&](const Geometry::Point &point) { return Geometry::is_inside(point, polygon0, true); }))
        {
            output.emplace_back(polygon0); // 无交点,且polygon1的点都在polygon0内,则并集必然为polygon0
            return true;
        }
        else
        {
            return false;
        }
    }

    // 调整交点顺序,同一条边上的交点按照顺序排列
    std::vector<Geometry::MarkedPoint> points;
    for (size_t i = 1, j = 0, count = points0.size() - 1; i < count; ++i)
    {
        if (points0[i].original)
        {
            continue;
        }
        else
        {
            j = i;
        }
        while (j < count && !points0[j].original)
        {
            ++j;
        }
        if (j == i + 1)
        {
            ++i;
            continue;
        }

        points.assign(points0.begin() + i, j < count ? points0.begin() + j : points0.end());
        std::sort(points.begin(), points.end(), [&](const Geometry::MarkedPoint &p0, const Geometry::MarkedPoint &p1)
            { return Geometry::distance(p0, points0[i - 1]) < Geometry::distance(p1, points0[i - 1]); });
        for (size_t k = i, n = 0; k < j; ++k)
        {
            points0[k] = points[n++];
        }
        i = j;
    }
    for (size_t i = points0.size() - 1; i > 1;)
    {
        if (polygon0.front() == points0[i])
        {
            if (!points0[i].original)
            {
                points0.insert(points0.begin(), points0[i]);
                points0.erase(points0.begin() + i + 1);
            }
            else
            {
                --i;
            }
        }
        else
        {
            break;
        }
    }
    for (size_t i = 1, j = 0, count = points1.size() - 1; i < count; ++i)
    {
        if (points1[i].original)
        {
            continue;
        }
        else
        {
            j = i;
        }
        while (j < count && !points1[j].original)
        {
            ++j;
        }
        if (j == i + 1)
        {
            ++i;
            continue;
        }

        points.assign(points1.begin() + i, j < count ? points1.begin() + j : points1.end());
        std::sort(points.begin(), points.end(), [&](const Geometry::MarkedPoint &p0, const Geometry::MarkedPoint &p1)
            { return Geometry::distance(p0, points1[i - 1]) < Geometry::distance(p1, points1[i - 1]); });
        for (size_t k = i, n = 0; k < j; ++k)
        {
            points1[k] = points[n++];
        }
        i = j;
    }
    for (size_t i = points1.size() - 1; i > 1;)
    {
        if (polygon1.front() == points1[i])
        {
            if (!points1[i].original)
            {
                points1.insert(points1.begin(), points1[i]);
                points1.erase(points1.begin() + i + 1);
            }
            else
            {
                --i;
            }
        }
        else
        {
            break;
        }
    }

    // 去除重复交点
    int value;
    Geometry::Point point_a, point_b, point_c, point_d;
    bool flags[5];
    for (size_t count, j, i = points0.size() - 1; i > 0; --i)
    {
        count = points0[i].original ? 0 : 1;
        for (j = i; j > 0; --j)
        {
            if (std::abs(points0[i].x - points0[j - 1].x) > Geometry::EPSILON || std::abs(points0[i].y - points0[j - 1].y) > Geometry::EPSILON)
            {
                break;
            }
            if (!points0[j - 1].original)
            {
                ++count;
            }
        }
        if (count < 2)
        {
            continue;
        }

        value = 0;
        for (size_t k = i; k > j; --k)
        {
            if (!points0[k].original)
            {
                value += points0[k].value;
            }
        }
        if (!points0[j].original)
        {
            value += points0[j].value;
        }
        if (count < 4)
        {
            if (value == 0)
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points0[k].original)
                    {
                        points0.erase(points0.begin() + k);
                    }
                }
                if (!points0[j].original)
                {
                    points0.erase(points0.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points0[k].original);
                    points0.erase(points0.begin() + k);
                }
                points0[j].value = value;
                points0[j].original = (flags[0] || points0[j].original);
            }
        }
        else
        {
            point = points0[i];
            point_a = polygon0.last_point(polygon0.index(point.x, point.y));
            point_b = polygon0.next_point(polygon0.index(point.x, point.y));
            point_c = polygon1.last_point(polygon1.index(point.x, point.y));
            point_d = polygon1.next_point(polygon1.index(point.x, point.y));

            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_c - point) > 0;
            flags[4] = Geometry::cross(point_c - point, point_b - point) > 0;
            flags[0] = !(flags[2] == flags[3] && flags[3] == flags[4]);
            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_d - point) > 0;
            flags[4] = Geometry::cross(point_d - point, point_b - point) > 0;
            flags[1] = !(flags[2] == flags[3] && flags[3] == flags[4]);

            if (flags[0] && flags[1])
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points0[k].original)
                    {
                        points0.erase(points0.begin() + k);
                    }
                }
                if (!points0[j].original)
                {
                    points0.erase(points0.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points0[k].original);
                    points0.erase(points0.begin() + k);
                }
                points0[j].value = value;
                points0[j].original = (flags[0] || points0[j].original);
            }
        }
        i = j > 0 ? j : 1;
    }
    for (size_t count, j, i = points1.size() - 1; i > 0; --i)
    {
        count = points1[i].original ? 0 : 1;
        for (j = i; j > 0; --j)
        {
            if (std::abs(points1[i].x - points1[j - 1].x) > Geometry::EPSILON || 
                std::abs(points1[i].y - points1[j - 1].y) > Geometry::EPSILON)
            {
                break;
            }
            if (!points1[j - 1].original)
            {
                ++count;
            }
        }
        if (count < 2)
        {
            continue;
        }

        value = 0;
        for (size_t k = i; k > j; --k)
        {
            if (!points1[k].original)
            {
                value += points1[k].value;
            }
        }
        if (!points1[j].original)
        {
            value += points1[j].value;
        }
        if (count < 4)
        {
            if (value == 0)
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points1[k].original)
                    {
                        points1.erase(points1.begin() + k);
                    }
                }
                if (!points1[j].original)
                {
                    points1.erase(points1.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points1[k].original);
                    points1.erase(points1.begin() + k);
                }
                points1[j].value = value;
                points1[j].original = (flags[0] || points1[j].original);
            }
        }
        else
        {
            point = points1[i];
            point_a = polygon1.last_point(polygon1.index(point.x, point.y));
            point_b = polygon1.next_point(polygon1.index(point.x, point.y));
            point_c = polygon0.last_point(polygon0.index(point.x, point.y));
            point_d = polygon0.next_point(polygon0.index(point.x, point.y));

            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_c - point) > 0;
            flags[4] = Geometry::cross(point_c - point, point_b - point) > 0;
            flags[0] = !(flags[2] == flags[3] && flags[3] == flags[4]);
            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_d - point) > 0;
            flags[4] = Geometry::cross(point_d - point, point_b - point) > 0;
            flags[1] = !(flags[2] == flags[3] && flags[3] == flags[4]);

            if (flags[0] && flags[1])
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points1[k].original)
                    {
                        points1.erase(points1.begin() + k);
                    }
                }
                if (!points1[j].original)
                {
                    points1.erase(points1.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points1[k].original);
                    points1.erase(points1.begin() + k);
                }
                points1[j].value = value;
                points1[j].original = (flags[0] || points1[j].original);
            }
        }
        i = j > 0 ? j : 1;
    }

    if (std::count_if(points0.begin(), points0.end(), [](const Geometry::MarkedPoint &p) { return p.value < 0; }) == 0 ||
        std::count_if(points1.begin(), points1.end(), [](const Geometry::MarkedPoint &p) { return p.value < 0; }) == 0)
    {
        return false; // 交点都是出点,即两多边形只有一个点相交
    }

    // 处理重边上的交点
    std::vector<Geometry::MarkedPoint>::iterator it0, it1;
    for (size_t i = 0, j = 1, count0 = points0.size(), count1 = polygon3.size(); j < count0; i = j)
    {
        while (i < count0 && points0[i].value == 0)
        {
            ++i;
        }
        j = i + 1;
        while (j < count0 && points0[j].value == 0)
        {
            ++j;
        }
        if (j >= count0)
        {
            break;
        }
        if (!Geometry::is_coincide(points0[i], points0[j], polygon2))
        {
            continue;
        }

        it0 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
                { return !p.original && Geometry::distance(p, points0[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points0[j]) < Geometry::EPSILON; });
        if (it0 == points1.end() || it1 == points1.end() || it0->value * it1->value <= 0)
        {
            continue;
        }

        for (size_t k = 1; k < count1; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon3[k - 1], polygon3[k]))
            {
                continue;
            }

            if (it0->value < 0 && it1->value < 0)
            {
                points1.erase(it0);
                if (points0[i].value != 0)
                {
                    points0.erase(points0.begin() + i);
                    --count0;
                }
            }
            else if (it0->value > 0 && it1->value > 0)
            {
                points1.erase(it1);
                if (points0[j].value != 0)
                {
                    points0.erase(points0.begin() + j);
                    --count0;
                }
            }
            break;
        }
    }
    for (size_t i = points0.size() - 1, j = 0;;)
    {
        while (i > 0 && points0[i].value == 0)
        {
            --i;
        }
        if (i == 0)
        {
            break;
        }
        while (j < i && points0[j].value == 0)
        {
            ++j;
        }
        if (j >= i || !Geometry::is_coincide(points0[i], points0[j], polygon2))
        {
            break;
        }

        it0 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
                { return !p.original && Geometry::distance(p, points0[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points0[j]) < Geometry::EPSILON; });
        if (it0 == points1.end() || it1 == points1.end() || it0->value * it1->value <= 0)
        {
            break;
        }

        for (size_t k = 1, count1 = polygon3.size(); k < count1; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon3[k - 1], polygon3[k]))
            {
                continue;
            }

            if (it0->value < 0 && it1->value < 0)
            {
                points1.erase(it0);
                if (points0[i].value != 0)
                {
                    points0.erase(points0.begin() + i);
                }
            }
            else if (it0->value > 0 && it1->value > 0)
            {
                points1.erase(it1);
                if (points0[j].value != 0)
                {
                    points0.erase(points0.begin() + j);
                }
            }
            break;
        }
        break;
    }
    for (size_t i = 0, j = 1, count0 = polygon2.size(), count1 = points1.size(); j < count1; i = j)
    {
        while (i < count1 && points1[i].value == 0)
        {
            ++i;
        }
        j = i + 1;
        while (j < count1 && points1[j].value == 0)
        {
            ++j;
        }
        if (j >= count1)
        {
            break;
        }
        if (!Geometry::is_coincide(points1[i], points1[j], polygon3))
        {
            continue;
        }

        it0 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
                { return !p.original && Geometry::distance(p, points1[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points1[j]) < Geometry::EPSILON; });
        if (it0 == points0.end() || it1 == points0.end() || it0->value * it1->value <= 0)
        {
            continue;
        }

        for (size_t k = 1; k < count0; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon2[k - 1], polygon2[k]))
            {
                continue;
            }

            if (it0->value < 0 && it1->value < 0)
            {
                points0.erase(it0);
                if (points1[i].value != 0)
                {
                    points1.erase(points1.begin() + i);
                    --count1;
                }
            }
            else if (it0->value > 0 && it1->value > 0)
            {
                points0.erase(it1);
                if (points1[j].value != 0)
                {
                    points1.erase(points1.begin() + j);
                    --count1;
                }
            }
            break;
        }
    }
    for (size_t i = points1.size() - 1, j = 0;;)
    {
        while (i > 0 && points1[i].value == 0)
        {
            --i;
        }
        if (i == 0)
        {
            break;
        }
        while (j < i && points1[j].value == 0)
        {
            ++j;
        }
        if (j >= i || !Geometry::is_coincide(points1[i], points1[j], polygon3))
        {
            break;
        }

        it0 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points1[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points1[j]) < Geometry::EPSILON; });
        if (it0 == points0.end() || it1 == points0.end() || it0->value * it1->value <= 0)
        {
            break;
        }

        for (size_t k = 1, count0 = polygon2.size(); k < count0; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon2[k - 1], polygon2[k]))
            {
                continue;
            }

            if (it0->value < 0 && it1->value < 0)
            {
                points0.erase(it0);
                if (points1[i].value != 0)
                {
                    points1.erase(points1.begin() + i);
                }
            }
            else if (it0->value > 0 && it1->value > 0)
            {
                points0.erase(it1);
                if (points1[j].value != 0)
                {
                    points1.erase(points1.begin() + j);
                }
            }
            break;
        }
        break;
    }

    std::vector<Geometry::Point> result;
    size_t index0 = 0, index1 = 0;
    size_t count0 = points0.size(), count1 = points1.size();
    size_t count2 = count0 + count1;
    for (Geometry::MarkedPoint &p : points0)
    {
        p.active = true;
    }
    for (Geometry::MarkedPoint &p : points1)
    {
        p.active = true;
    }
    output.clear();

    while (count0 > 0 && count1 > 0)
    {
        output.emplace_back();

        index0 = index1 = 0;
        while (index0 < count0 && points0[index0].value < 1)
        {
            ++index0;
        }

        if (index0 >= count0)
        {
            output.pop_back();
            break;
        }

        while (result.size() < count2 && (result.size() < 4 || result.front() != result.back()))
        {
            while (result.size() < count2 && (result.size() < 4 || result.front() != result.back()))
            {
                if (points0[index0].value > -1)
                {
                    if (points0[index0].original)
                    {
                        points0[index0].active = false;
                    }
                    result.emplace_back(points0[index0++]);
                }
                else
                {
                    index1 = 0;
                    while (index1 < count1 && points1[index1] != points0[index0])
                    {
                        ++index1;
                    }
                    index1 %= count1;
                    result.emplace_back(points1[index1++]);
                    ++index0;
                    index0 %= count0;
                    index1 %= count1;
                    break;
                }
                index0 %= count0;
            }

            while (result.size() < count2 && (result.size() < 4 || result.front() != result.back()))
            {
                if (points1[index1].value > -1)
                {
                    if (points1[index1].original)
                    {
                        points1[index1].active = false;
                    }
                    result.emplace_back(points1[index1++]);
                }
                else
                {
                    index0 = 0;
                    while (index0 < count0 && points0[index0] != points1[index1])
                    {
                        ++index0;
                    }
                    index0 %= count0;
                    result.emplace_back(points0[index0++]);
                    ++index1;
                    index0 %= count0;
                    index1 %= count1;
                    break;
                }
                index1 %= count1;
            }
        }

        for (size_t i = result.size() - 1; i > 1; --i)
        {
            if (Geometry::is_inside(result[i - 1], result[i - 2], result[i]))
            {
                result.erase(result.begin() + i - 1);
            }
            else if (Geometry::distance(result[i - 2], result[i]) < Geometry::EPSILON)
            {
                result.erase(result.begin() + i--);
                result.erase(result.begin() + i);
            }
        }
        if (result.size() > 4)
        {
            if (Geometry::is_inside(result.front(), result[1], result[result.size() - 2]))
            {
                result.pop_back();
                std::swap(result.front(), result.back());
                result.pop_back();
            }
            else if (Geometry::distance(result[1], result[result.size() - 2]) < Geometry::EPSILON)
            {
                result.pop_back();
                result.pop_back();
                result.erase(result.begin());
            }
        }
        output.back().append(result.begin(), result.end());

        it0 = points0.begin();
        while (it0 != points0.end())
        {
            if (!it0->active || std::find(result.begin(), result.end(), *it0) != result.end())
            {
                it0 = points0.erase(it0);
            }
            else
            {
                ++it0;
            }
        }
        it1 = points1.begin();
        while (it1 != points1.end())
        {
            if (!it1->active || std::find(result.begin(), result.end(), *it1) != result.end())
            {
                it1 = points1.erase(it1);
            }
            else
            {
                ++it1;
            }
        }

        if (output.back().area() == 0)
        {
            output.pop_back();
        }

        if (std::count_if(points0.cbegin(), points0.cend(), [](const Geometry::MarkedPoint &p){ return p.value < 0; }) == 0 ||
            std::count_if(points1.cbegin(), points1.cend(), [](const Geometry::MarkedPoint &p){ return p.value < 0; }) == 0)
        {
            break;
        }

        count0 = points0.size();
        count1 = points1.size();
        count2 = count0 + count1;
        result.clear();
    }

    return !output.empty();
}

bool Geometry::polygon_intersection(const Geometry::Polygon &polygon0, const Geometry::Polygon &polygon1, std::vector<Geometry::Polygon> &output)
{
    Geometry::Polygon polygon2(polygon0), polygon3(polygon1);
    polygon2.reorder_points(false);
    polygon3.reorder_points(false);
    std::vector<Geometry::MarkedPoint> points0, points1;
    for (const Geometry::Point &point : polygon2)
    {
        points0.emplace_back(point.x, point.y);
    }
    for (const Geometry::Point &point : polygon3)
    {
        points1.emplace_back(point.x, point.y);
    }

    Geometry::Point point, pre_point; // 找到交点并计算其几何数
    const Geometry::AABBRect rect(polygon1.bounding_rect());
    for (size_t i = 1, count0 = points0.size(); i < count0; ++i)
    {
        if (!Geometry::is_intersected(rect, points0[i - 1], points0[i])) // 粗筛
        {
            continue;
        }

        pre_point = points0[i - 1];
        for (size_t k = 1, j = 1, count1 = points1.size(); j < count1; ++j)
        {
            k = j - 1;
            while (!points1[k].active)
            {
                --k; // 跳过非活动交点
            }
            while (j < count1 && (points1[k] == points1[j] || !points1[j].active))
            {
                k = j;
                ++j;
                while (!points1[k].active)
                {
                    --k; // 跳过非活动交点
                }
            }
            if (j >= count1)
            {
                continue;
            }
            k = j - 1;
            while (!points1[k].active)
            {
                --k; // 跳过非活动交点
            }
            if (!Geometry::is_parallel(pre_point, points0[i], points1[k], points1[j]) &&
                Geometry::is_intersected(pre_point, points0[i], points1[k], points1[j], point))
            {
                points0.insert(points0.begin() + i++, Geometry::MarkedPoint(point.x, point.y, false));
                points1.insert(points1.begin() + j++, Geometry::MarkedPoint(point.x, point.y, false));
                ++count0;
                ++count1;
                if (Geometry::cross(pre_point, points0[i], points1[k], points1[j]) >= 0)
                {
                    points0[i - 1].value = 1;
                    points1[j - 1].value = -1;
                }
                else
                {
                    points0[i - 1].value = -1;
                    points1[j - 1].value = 1;
                }
            }
        }

        // 将本次循环添加的交点休眠,令下次循环polygon1处于无活动交点状态以排除干扰
        for (Geometry::MarkedPoint &p : points1)
        {
            if (!p.original)
            {
                p.active = false;
            }
        }
    }

    if (points0.size() == polygon0.size()) // 无交点
    {
        if (std::all_of(polygon0.begin(), polygon0.end(), [&](const Geometry::Point &point) { return Geometry::is_inside(point, polygon1, true); }))
        {
            output.emplace_back(polygon0); // 无交点,且polygon0的点都在polygon1内,则交集必然为polygon0
            return true;
        }
        else if (std::all_of(polygon1.begin(), polygon1.end(), [&](const Geometry::Point &point) { return Geometry::is_inside(point, polygon0, true); }))
        {
            output.emplace_back(polygon1); // 无交点,且polygon1的点都在polygon0内,则交集必然为polygon1
            return true;
        }
        else
        {
            return false;
        }
    }

    // 调整交点顺序,同一条边上的交点按照顺序排列
    std::vector<Geometry::MarkedPoint> points;
    for (size_t i = 1, j = 0, count = points0.size() - 1; i < count; ++i)
    {
        if (points0[i].original)
        {
            continue;
        }
        else
        {
            j = i;
        }
        while (j < count && !points0[j].original)
        {
            ++j;
        }
        if (j == i + 1)
        {
            ++i;
            continue;
        }

        points.assign(points0.begin() + i, j < count ? points0.begin() + j : points0.end());
        std::sort(points.begin(), points.end(), [&](const Geometry::MarkedPoint &p0, const Geometry::MarkedPoint &p1)
            { return Geometry::distance(p0, points0[i - 1]) < Geometry::distance(p1, points0[i - 1]); });
        for (size_t k = i, n = 0; k < j; ++k)
        {
            points0[k] = points[n++];
        }
        i = j;
    }
    for (size_t i = 1, j = 0, count = points1.size() - 1; i < count; ++i)
    {
        if (points1[i].original)
        {
            continue;
        }
        else
        {
            j = i;
        }
        while (j < count && !points1[j].original)
        {
            ++j;
        }
        if (j == i + 1)
        {
            ++i;
            continue;
        }

        points.assign(points1.begin() + i, j < count ? points1.begin() + j : points1.end());
        std::sort(points.begin(), points.end(), [&](const Geometry::MarkedPoint &p0, const Geometry::MarkedPoint &p1)
            { return Geometry::distance(p0, points1[i - 1]) < Geometry::distance(p1, points1[i - 1]); });
        for (size_t k = i, n = 0; k < j; ++k)
        {
            points1[k] = points[n++];
        }
        i = j;
    }

    // 去除重复交点
    int value;
    Geometry::Point point_a, point_b, point_c, point_d;
    bool flags[5];
    for (size_t count, j, i = points0.size() - 1; i > 0; --i)
    {
        count = points0[i].original ? 0 : 1;
        for (j = i; j > 0; --j)
        {
            if (std::abs(points0[i].x - points0[j - 1].x) > Geometry::EPSILON ||
                std::abs(points0[i].y - points0[j - 1].y) > Geometry::EPSILON)
            {
                break;
            }
            if (!points0[j - 1].original)
            {
                ++count;
            }
        }
        if (count < 2)
        {
            continue;
        }

        value = 0;
        for (size_t k = i; k > j; --k)
        {
            if (!points0[k].original)
            {
                value += points0[k].value;
            }
        }
        if (!points0[j].original)
        {
            value += points0[j].value;
        }
        if (count < 4)
        {
            if (value == 0)
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points0[k].original)
                    {
                        points0.erase(points0.begin() + k);
                    }
                }
                if (!points0[j].original)
                {
                    points0.erase(points0.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points0[k].original);
                    points0.erase(points0.begin() + k);
                }
                points0[j].value = value;
                points0[j].original = (flags[0] || points0[j].original);
            }
        }
        else
        {
            point = points0[i];
            point_a = polygon0.last_point(polygon0.index(point.x, point.y));
            point_b = polygon0.next_point(polygon0.index(point.x, point.y));
            point_c = polygon1.last_point(polygon1.index(point.x, point.y));
            point_d = polygon1.next_point(polygon1.index(point.x, point.y));

            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_c - point) > 0;
            flags[4] = Geometry::cross(point_c - point, point_b - point) > 0;
            flags[0] = !(flags[2] == flags[3] && flags[3] == flags[4]);
            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_d - point) > 0;
            flags[4] = Geometry::cross(point_d - point, point_b - point) > 0;
            flags[1] = !(flags[2] == flags[3] && flags[3] == flags[4]);

            if (flags[0] && flags[1])
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points0[k].original)
                    {
                        points0.erase(points0.begin() + k);
                    }
                }
                if (!points0[j].original)
                {
                    points0.erase(points0.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points0[k].original);
                    points0.erase(points0.begin() + k);
                }
                points0[j].value = value;
                points0[j].original = (flags[0] || points0[j].original);
            }
        }
        i = j > 0 ? j : 1;
    }
    for (size_t count, j, i = points1.size() - 1; i > 0; --i)
    {
        count = points1[i].original ? 0 : 1;
        for (j = i; j > 0; --j)
        {
            if (std::abs(points1[i].x - points1[j - 1].x) > Geometry::EPSILON || 
                std::abs(points1[i].y - points1[j - 1].y) > Geometry::EPSILON)
            {
                break;
            }
            if (!points1[j - 1].original)
            {
                ++count;
            }
        }
        if (count < 2)
        {
            continue;
        }

        value = 0;
        for (size_t k = i; k > j; --k)
        {
            if (!points1[k].original)
            {
                value += points1[k].value;
            }
        }
        if (!points1[j].original)
        {
            value += points1[j].value;
        }
        if (count < 4)
        {
            if (value == 0)
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points1[k].original)
                    {
                        points1.erase(points1.begin() + k);
                    }
                }
                if (!points1[j].original)
                {
                    points1.erase(points1.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points1[k].original);
                    points1.erase(points1.begin() + k);
                }
                points1[j].value = value;
                points1[j].original = (flags[0] || points1[j].original);
            }
        }
        else
        {
            point = points1[i];
            point_a = polygon1.last_point(polygon1.index(point.x, point.y));
            point_b = polygon1.next_point(polygon1.index(point.x, point.y));
            point_c = polygon0.last_point(polygon0.index(point.x, point.y));
            point_d = polygon0.next_point(polygon0.index(point.x, point.y));

            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_c - point) > 0;
            flags[4] = Geometry::cross(point_c - point, point_b - point) > 0;
            flags[0] = !(flags[2] == flags[3] && flags[3] == flags[4]);
            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_d - point) > 0;
            flags[4] = Geometry::cross(point_d - point, point_b - point) > 0;
            flags[1] = !(flags[2] == flags[3] && flags[3] == flags[4]);

            if (flags[0] && flags[1])
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points1[k].original)
                    {
                        points1.erase(points1.begin() + k);
                    }
                }
                if (!points1[j].original)
                {
                    points1.erase(points1.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points1[k].original);
                    points1.erase(points1.begin() + k);
                }
                points1[j].value = value;
                points1[j].original = (flags[0] || points1[j].original);
            }
        }
        i = j > 0 ? j : 1;
    }

    if (std::count_if(points0.begin(), points0.end(), [](const Geometry::MarkedPoint &p) { return p.value < 0; }) == 0 ||
        std::count_if(points1.begin(), points1.end(), [](const Geometry::MarkedPoint &p) { return p.value < 0; }) == 0)
    {
        return false; // 交点都是出点,即两多边形只有一个点相交
    }

    // 处理重边上的交点
    std::vector<Geometry::MarkedPoint>::iterator it0, it1;
    for (size_t i = 0, j = 1, count0 = points0.size(), count1 = polygon3.size(); j < count0; i = j)
    {
        while (i < count0 && points0[i].value == 0)
        {
            ++i;
        }
        j = i + 1;
        while (j < count0 && points0[j].value == 0)
        {
            ++j;
        }
        if (j >= count0)
        {
            break;
        }
        if (!Geometry::is_coincide(points0[i], points0[j], polygon2))
        {
            continue;
        }

        it0 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
                { return !p.original && Geometry::distance(p, points0[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points0[j]) < Geometry::EPSILON; });
        if (it0 == points1.end() || it1 == points1.end() || it0->value * it1->value <= 0)
        {
            continue;
        }

        for (size_t k = 1; k < count1; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon3[k - 1], polygon3[k]))
            {
                continue;
            }

            if (it0->value > 0 && it1->value > 0)
            {
                points1.erase(it0);
                if (points0[i].value != 0)
                {
                    points0.erase(points0.begin() + i);
                    --count0;
                }
            }
            else if (it0->value < 0 && it1->value < 0)
            {
                points1.erase(it1);
                if (points0[j].value != 0)
                {
                    points0.erase(points0.begin() + j);
                    --count0;
                }
            }
            break;
        }
    }
    for (size_t i = points0.size() - 1, j = 0;;)
    {
        while (i > 0 && points0[i].value == 0)
        {
            --i;
        }
        if (i == 0)
        {
            break;
        }
        while (j < i && points0[j].value == 0)
        {
            ++j;
        }
        if (j >= i || !Geometry::is_coincide(points0[i], points0[j], polygon2))
        {
            break;
        }

        it0 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
                { return !p.original && Geometry::distance(p, points0[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points0[j]) < Geometry::EPSILON; });
        if (it0 == points1.end() || it1 == points1.end() || it0->value * it1->value <= 0)
        {
            break;
        }

        for (size_t k = 1, count1 = polygon3.size(); k < count1; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon3[k - 1], polygon3[k]))
            {
                continue;
            }

            if (it0->value > 0 && it1->value > 0)
            {
                points1.erase(it0);
                if (points0[i].value != 0)
                {
                    points0.erase(points0.begin() + i);
                }
            }
            else if (it0->value < 0 && it1->value < 0)
            {
                points1.erase(it1);
                if (points0[j].value != 0)
                {
                    points0.erase(points0.begin() + j);
                }
            }
            break;
        }
        break;
    }
    for (size_t i = 0, j = 1, count0 = polygon2.size(), count1 = points1.size(); j < count1; i = j)
    {
        while (i < count1 && points1[i].value == 0)
        {
            ++i;
        }
        j = i + 1;
        while (j < count1 && points1[j].value == 0)
        {
            ++j;
        }
        if (j >= count1)
        {
            break;
        }
        if (!Geometry::is_coincide(points1[i], points1[j], polygon3))
        {
            continue;
        }

        it0 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
                { return !p.original && Geometry::distance(p, points1[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points1[j]) < Geometry::EPSILON; });
        if (it0 == points0.end() || it1 == points0.end() || it0->value * it1->value <= 0)
        {
            continue;
        }

        for (size_t k = 1; k < count0; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon2[k - 1], polygon2[k]))
            {
                continue;
            }

            if (it0->value > 0 && it1->value > 0)
            {
                points0.erase(it0);
                if (points1[i].value != 0)
                {
                    points1.erase(points1.begin() + i);
                    --count1;
                }
            }
            else if (it0->value < 0 && it1->value < 0)
            {
                points0.erase(it1);
                if (points1[j].value != 0)
                {
                    points1.erase(points1.begin() + j);
                    --count1;
                }
            }
            break;
        }
    }
    for (size_t i = points1.size() - 1, j = 0;;)
    {
        while (i > 0 && points1[i].value == 0)
        {
            --i;
        }
        if (i == 0)
        {
            break;
        }
        while (j < i && points1[j].value == 0)
        {
            ++j;
        }
        if (j >= i || !Geometry::is_coincide(points1[i], points1[j], polygon3))
        {
            break;
        }

        it0 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points1[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points1[j]) < Geometry::EPSILON; });
        if (it0 == points0.end() || it1 == points0.end() || it0->value * it1->value <= 0)
        {
            break;
        }

        for (size_t k = 1, count0 = polygon2.size(); k < count0; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon2[k - 1], polygon2[k]))
            {
                continue;
            }

            if (it0->value > 0 && it1->value > 0)
            {
                points0.erase(it0);
                if (points1[i].value != 0)
                {
                    points1.erase(points1.begin() + i);
                }
            }
            else if (it0->value < 0 && it1->value < 0)
            {
                points0.erase(it1);
                if (points1[j].value != 0)
                {
                    points1.erase(points1.begin() + j);
                }
            }
            break;
        }
        break;
    }

    std::vector<Geometry::Point> result;
    size_t index0 = 0, index1 = 0;
    size_t count0 = points0.size(), count1 = points1.size();
    size_t count2 = count0 + count1;
    for (Geometry::MarkedPoint &p : points0)
    {
        p.active = true;
    }
    for (Geometry::MarkedPoint &p : points1)
    {
        p.active = true;
    }
    output.clear();

    while (count0 > 0 && count1 > 0)
    {
        output.emplace_back();

        index0 = index1 = 0;
        while (index0 < count0 && points0[index0].value < 1)
        {
            ++index0;
        }

        if (index0 >= count0)
        {
            output.pop_back();
            break;
        }

        while (result.size() < count2 && (result.size() < 4 || result.front() != result.back()))
        {
            while (result.size() < count2 && (result.size() < 4 || result.front() != result.back()))
            {
                if (points0[index0].value < 1)
                {
                    if (points0[index0].original)
                    {
                        points0[index0].active = false;
                    }
                    result.emplace_back(points0[index0++]);
                }
                else
                {
                    index1 = 0;
                    while (index1 < count1 && points1[index1] != points0[index0])
                    {
                        ++index1;
                    }
                    index1 %= count1;
                    result.emplace_back(points1[index1++]);
                    ++index0;
                    index0 %= count0;
                    index1 %= count1;
                    break;
                }
                index0 %= count0;
            }

            while (result.size() < count2 && (result.size() < 4 || result.front() != result.back()))
            {
                if (points1[index1].value < 1)
                {
                    if (points1[index1].original)
                    {
                        points1[index1].active = false;
                    }
                    result.emplace_back(points1[index1++]);
                }
                else
                {
                    index0 = 0;
                    while (index0 < count0 && points0[index0] != points1[index1])
                    {
                        ++index0;
                    }
                    index0 %= count0;
                    result.emplace_back(points0[index0++]);
                    ++index1;
                    index0 %= count0;
                    index1 %= count1;
                    break;
                }
                index1 %= count1;
            }
        }

        for (size_t i = result.size() - 1; i > 1; --i)
        {
            if (Geometry::is_inside(result[i - 1], result[i - 2], result[i]))
            {
                result.erase(result.begin() + i - 1);
            }
            else if (Geometry::distance(result[i - 2], result[i]) < Geometry::EPSILON)
            {
                result.erase(result.begin() + i--);
                result.erase(result.begin() + i);
            }
        }
        if (result.size() > 4)
        {
            if (Geometry::is_inside(result.front(), result[1], result[result.size() - 2]))
            {
                result.pop_back();
                std::swap(result.front(), result.back());
                result.pop_back();
            }
            else if (Geometry::distance(result[1], result[result.size() - 2]) < Geometry::EPSILON)
            {
                result.pop_back();
                result.pop_back();
                result.erase(result.begin());
            }
        }
        output.back().append(result.begin(), result.end());

        it0 = points0.begin();
        while (it0 != points0.end())
        {
            if (!it0->active || std::find(result.begin(), result.end(), *it0) != result.end())
            {
                it0 = points0.erase(it0);
            }
            else
            {
                ++it0;
            }
        }
        it1 = points1.begin();
        while (it1 != points1.end())
        {
            if (!it1->active || std::find(result.begin(), result.end(), *it1) != result.end())
            {
                it1 = points1.erase(it1);
            }
            else
            {
                ++it1;
            }
        }

        if (output.back().area() == 0)
        {
            output.pop_back();
        }

        if (std::count_if(points0.cbegin(), points0.cend(), [](const Geometry::MarkedPoint &p){ return p.value < 0; }) == 0 ||
            std::count_if(points1.cbegin(), points1.cend(), [](const Geometry::MarkedPoint &p){ return p.value < 0; }) == 0)
        {
            break;
        }

        count0 = points0.size();
        count1 = points1.size();
        count2 = count0 + count1;
        result.clear();
    }

    return !output.empty();
}

bool Geometry::polygon_difference(const Geometry::Polygon &polygon0, const Geometry::Polygon &polygon1, std::vector<Geometry::Polygon> &output)
{
    Geometry::Polygon polygon2(polygon0), polygon3(polygon1);
    polygon2.reorder_points(true);
    polygon3.reorder_points(false);
    std::vector<Geometry::MarkedPoint> points0, points1;
    for (const Geometry::Point &point : polygon2)
    {
        points0.emplace_back(point.x, point.y);
    }
    for (const Geometry::Point &point : polygon3)
    {
        points1.emplace_back(point.x, point.y);
    }

    Geometry::Point point, pre_point; // 找到交点并计算其几何数
    const Geometry::AABBRect rect(polygon1.bounding_rect());
    for (size_t i = 1, count0 = points0.size(); i < count0; ++i)
    {
        if (!Geometry::is_intersected(rect, points0[i - 1], points0[i])) // 粗筛
        {
            continue;
        }

        pre_point = points0[i - 1];
        for (size_t k = 1, j = 1, count1 = points1.size(); j < count1; ++j)
        {
            k = j - 1;
            while (!points1[k].active)
            {
                --k; // 跳过非活动交点
            }
            while (j < count1 && (points1[k] == points1[j] || !points1[j].active))
            {
                k = j;
                ++j;
                while (!points1[k].active)
                {
                    --k; // 跳过非活动交点
                }
            }
            if (j >= count1)
            {
                continue;
            }
            k = j - 1;
            while (!points1[k].active)
            {
                --k; // 跳过非活动交点
            }
            if (!Geometry::is_parallel(pre_point, points0[i], points1[k], points1[j]) &&
                Geometry::is_intersected(pre_point, points0[i], points1[k], points1[j], point))
            {
                points0.insert(points0.begin() + i++, Geometry::MarkedPoint(point.x, point.y, false));
                points1.insert(points1.begin() + j++, Geometry::MarkedPoint(point.x, point.y, false));
                ++count0;
                ++count1;
                if (Geometry::cross(pre_point, points0[i], points1[k], points1[j]) >= 0)
                {
                    points0[i - 1].value = 1;
                    points1[j - 1].value = -1;
                }
                else
                {
                    points0[i - 1].value = -1;
                    points1[j - 1].value = 1;
                }
            }
        }

        // 将本次循环添加的交点休眠,令下次循环polygon1处于无活动交点状态以排除干扰
        for (Geometry::MarkedPoint &p : points1)
        {
            if (!p.original)
            {
                p.active = false;
            }
        }
    }

    if (points0.size() == polygon0.size()) // 无交点
    {
        return false;
    }

    // 调整交点顺序,同一条边上的交点按照顺序排列
    std::vector<Geometry::MarkedPoint> points;
    for (size_t i = 1, j = 0, count = points0.size() - 1; i < count; ++i)
    {
        if (points0[i].original)
        {
            continue;
        }
        else
        {
            j = i;
        }
        while (j < count && !points0[j].original)
        {
            ++j;
        }
        if (j == i + 1)
        {
            ++i;
            continue;
        }

        points.assign(points0.begin() + i, j < count ? points0.begin() + j : points0.end());
        std::sort(points.begin(), points.end(), [&](const Geometry::MarkedPoint &p0, const Geometry::MarkedPoint &p1)
            { return Geometry::distance(p0, points0[i - 1]) < Geometry::distance(p1, points0[i - 1]); });
        for (size_t k = i, n = 0; k < j; ++k)
        {
            points0[k] = points[n++];
        }
        i = j;
    }
    for (size_t i = points0.size() - 1; i > 1;)
    {
        if (polygon0.front() == points0[i])
        {
            if (!points0[i].original)
            {
                points0.insert(points0.begin(), points0[i]);
                points0.erase(points0.begin() + i + 1);
            }
            else
            {
                --i;
            }
        }
        else
        {
            break;
        }
    }
    for (size_t i = 1, j = 0, count = points1.size() - 1; i < count; ++i)
    {
        if (points1[i].original)
        {
            continue;
        }
        else
        {
            j = i;
        }
        while (j < count && !points1[j].original)
        {
            ++j;
        }
        if (j == i + 1)
        {
            ++i;
            continue;
        }

        points.assign(points1.begin() + i, j < count ? points1.begin() + j : points1.end());
        std::sort(points.begin(), points.end(), [&](const Geometry::MarkedPoint &p0, const Geometry::MarkedPoint &p1)
            { return Geometry::distance(p0, points1[i - 1]) < Geometry::distance(p1, points1[i - 1]); });
        for (size_t k = i, n = 0; k < j; ++k)
        {
            points1[k] = points[n++];
        }
        i = j;
    }
    for (size_t i = points1.size() - 1; i > 1;)
    {
        if (polygon1.front() == points1[i])
        {
            if (!points1[i].original)
            {
                points1.insert(points1.begin(), points1[i]);
                points1.erase(points1.begin() + i + 1);
            }
            else
            {
                --i;
            }
        }
        else
        {
            break;
        }
    }

    // 去除重复交点
    int value;
    Geometry::Point point_a, point_b, point_c, point_d;
    bool flags[5];
    for (size_t count, j, i = points0.size() - 1; i > 0; --i)
    {
        count = points0[i].original ? 0 : 1;
        for (j = i; j > 0; --j)
        {
            if (std::abs(points0[i].x - points0[j - 1].x) > Geometry::EPSILON ||
                std::abs(points0[i].y - points0[j - 1].y) > Geometry::EPSILON)
            {
                break;
            }
            if (!points0[j - 1].original)
            {
                ++count;
            }
        }
        if (count < 2)
        {
            continue;
        }

        value = 0;
        for (size_t k = i; k > j; --k)
        {
            if (!points0[k].original)
            {
                value += points0[k].value;
            }
        }
        if (!points0[j].original)
        {
            value += points0[j].value;
        }
        if (count < 4)
        {
            if (value == 0)
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points0[k].original)
                    {
                        points0.erase(points0.begin() + k);
                    }
                }
                if (!points0[j].original)
                {
                    points0.erase(points0.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points0[k].original);
                    points0.erase(points0.begin() + k);
                }
                points0[j].value = value;
                points0[j].original = (flags[0] || points0[j].original);
            }
        }
        else
        {
            point = points0[i];
            point_a = polygon0.last_point(polygon0.index(point.x, point.y));
            point_b = polygon0.next_point(polygon0.index(point.x, point.y));
            point_c = polygon1.last_point(polygon1.index(point.x, point.y));
            point_d = polygon1.next_point(polygon1.index(point.x, point.y));

            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_c - point) > 0;
            flags[4] = Geometry::cross(point_c - point, point_b - point) > 0;
            flags[0] = !(flags[2] == flags[3] && flags[3] == flags[4]);
            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_d - point) > 0;
            flags[4] = Geometry::cross(point_d - point, point_b - point) > 0;
            flags[1] = !(flags[2] == flags[3] && flags[3] == flags[4]);

            if (flags[0] && flags[1])
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points0[k].original)
                    {
                        points0.erase(points0.begin() + k);
                    }
                }
                if (!points0[j].original)
                {
                    points0.erase(points0.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points0[k].original);
                    points0.erase(points0.begin() + k);
                }
                points0[j].value = value;
                points0[j].original = (flags[0] || points0[j].original);
            }
        }
        i = j > 0 ? j : 1;
    }
    for (size_t count, j, i = points1.size() - 1; i > 0; --i)
    {
        count = points1[i].original ? 0 : 1;
        for (j = i; j > 0; --j)
        {
            if (std::abs(points1[i].x - points1[j - 1].x) > Geometry::EPSILON || 
                std::abs(points1[i].y - points1[j - 1].y) > Geometry::EPSILON)
            {
                break;
            }
            if (!points1[j - 1].original)
            {
                ++count;
            }
        }
        if (count < 2)
        {
            continue;
        }

        value = 0;
        for (size_t k = i; k > j; --k)
        {
            if (!points1[k].original)
            {
                value += points1[k].value;
            }
        }
        if (!points1[j].original)
        {
            value += points1[j].value;
        }
        if (count < 4)
        {
            if (value == 0)
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points1[k].original)
                    {
                        points1.erase(points1.begin() + k);
                    }
                }
                if (!points1[j].original)
                {
                    points1.erase(points1.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points1[k].original);
                    points1.erase(points1.begin() + k);
                }
                points1[j].value = value;
                points1[j].original = (flags[0] || points1[j].original);
            }
        }
        else
        {
            point = points1[i];
            point_a = polygon1.last_point(polygon1.index(point.x, point.y));
            point_b = polygon1.next_point(polygon1.index(point.x, point.y));
            point_c = polygon0.last_point(polygon0.index(point.x, point.y));
            point_d = polygon0.next_point(polygon0.index(point.x, point.y));

            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_c - point) > 0;
            flags[4] = Geometry::cross(point_c - point, point_b - point) > 0;
            flags[0] = !(flags[2] == flags[3] && flags[3] == flags[4]);
            flags[2] = Geometry::cross(point_a - point, point_b - point) > 0;
            flags[3] = Geometry::cross(point_a - point, point_d - point) > 0;
            flags[4] = Geometry::cross(point_d - point, point_b - point) > 0;
            flags[1] = !(flags[2] == flags[3] && flags[3] == flags[4]);

            if (flags[0] && flags[1])
            {
                for (size_t k = i; k > j; --k)
                {
                    if (!points1[k].original)
                    {
                        points1.erase(points1.begin() + k);
                    }
                }
                if (!points1[j].original)
                {
                    points1.erase(points1.begin() + j);
                }
            }
            else
            {
                flags[0] = false;
                for (size_t k = i; k > j; --k)
                {
                    flags[0] = (flags[0] || points1[k].original);
                    points1.erase(points1.begin() + k);
                }
                points1[j].value = value;
                points1[j].original = (flags[0] || points1[j].original);
            }
        }
        i = j > 0 ? j : 1;
    }

    if (std::count_if(points0.begin(), points0.end(), [](const Geometry::MarkedPoint &p) { return p.value < 0; }) == 0 || 
        std::count_if(points1.begin(), points1.end(), [](const Geometry::MarkedPoint &p) { return p.value < 0; }) == 0)
    {
        return false; // 交点都是出点,即两多边形只有一个点相交
    }

    // 处理重边上的交点
    std::vector<Geometry::MarkedPoint>::iterator it0, it1;
    for (size_t i = 0, j = 1, count0 = points0.size(), count1 = polygon3.size(); j < count0; i = j)
    {
        while (i < count0 && points0[i].value == 0)
        {
            ++i;
        }
        j = i + 1;
        while (j < count0 && points0[j].value == 0)
        {
            ++j;
        }
        if (j >= count0)
        {
            break;
        }
        if (!Geometry::is_coincide(points0[i], points0[j], polygon2))
        {
            continue;
        }

        it0 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
                { return !p.original && Geometry::distance(p, points0[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points0[j]) < Geometry::EPSILON; });
        if (it0 == points1.end() || it1 == points1.end() || it0->value * it1->value <= 0)
        {
            continue;
        }

        for (size_t k = 1; k < count1; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon3[k - 1], polygon3[k]))
            {
                continue;
            }

            if (it0->value < 0 && it1->value < 0)
            {
                points1.erase(it0);
                if (points0[i].value != 0)
                {
                    points0.erase(points0.begin() + i);
                    --count0;
                }
            }
            else if (it0->value > 0 && it1->value > 0)
            {
                points1.erase(it1);
                if (points0[j].value != 0)
                {
                    points0.erase(points0.begin() + j);
                    --count0;
                }
            }
            break;
        }
    }
    for (size_t i = points0.size() - 1, j = 0;;)
    {
        while (i > 0 && points0[i].value == 0)
        {
            --i;
        }
        if (i == 0)
        {
            break;
        }
        while (j < i && points0[j].value == 0)
        {
            ++j;
        }
        if (j >= i || !Geometry::is_coincide(points0[i], points0[j], polygon2))
        {
            break;
        }

        it0 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
                { return !p.original && Geometry::distance(p, points0[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points1.begin(), points1.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points0[j]) < Geometry::EPSILON; });
        if (it0 == points1.end() || it1 == points1.end() || it0->value * it1->value <= 0)
        {
            break;
        }

        for (size_t k = 1, count1 = polygon3.size(); k < count1; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon3[k - 1], polygon3[k]))
            {
                continue;
            }

            if (it0->value < 0 && it1->value < 0)
            {
                points1.erase(it0);
                if (points0[i].value != 0)
                {
                    points0.erase(points0.begin() + i);
                }
            }
            else if (it0->value > 0 && it1->value > 0)
            {
                points1.erase(it1);
                if (points0[j].value != 0)
                {
                    points0.erase(points0.begin() + j);
                }
            }
            break;
        }
        break;
    }
    for (size_t i = 0, j = 1, count0 = polygon2.size(), count1 = points1.size(); j < count1; i = j)
    {
        while (i < count1 && points1[i].value == 0)
        {
            ++i;
        }
        j = i + 1;
        while (j < count1 && points1[j].value == 0)
        {
            ++j;
        }
        if (j >= count1)
        {
            break;
        }
        if (!Geometry::is_coincide(points1[i], points1[j], polygon3))
        {
            continue;
        }

        it0 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
                { return !p.original && Geometry::distance(p, points1[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points1[j]) < Geometry::EPSILON; });
        if (it0 == points0.end() || it1 == points0.end() || it0->value * it1->value <= 0)
        {
            continue;
        }

        for (size_t k = 1; k < count0; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon2[k - 1], polygon2[k]))
            {
                continue;
            }

            if (it0->value < 0 && it1->value < 0)
            {
                points0.erase(it0);
                if (points1[i].value != 0)
                {
                    points1.erase(points1.begin() + i);
                    --count1;
                }
            }
            else if (it0->value > 0 && it1->value > 0)
            {
                points0.erase(it1);
                if (points1[j].value != 0)
                {
                    points1.erase(points1.begin() + j);
                    --count1;
                }
            }
            break;
        }
    }
    for (size_t i = points1.size() - 1, j = 0;;)
    {
        while (i > 0 && points1[i].value == 0)
        {
            --i;
        }
        if (i == 0)
        {
            break;
        }
        while (j < i && points1[j].value == 0)
        {
            ++j;
        }
        if (j >= i || !Geometry::is_coincide(points1[i], points1[j], polygon3))
        {
            break;
        }

        it0 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points1[i]) < Geometry::EPSILON; });
        it1 = std::find_if(points0.begin(), points0.end(), [&](const Geometry::MarkedPoint &p)
            { return !p.original && Geometry::distance(p, points1[j]) < Geometry::EPSILON; });
        if (it0 == points0.end() || it1 == points0.end() || it0->value * it1->value <= 0)
        {
            break;
        }

        for (size_t k = 1, count0 = polygon2.size(); k < count0; ++k)
        {
            if (!Geometry::is_part(*it0, *it1, polygon2[k - 1], polygon2[k]))
            {
                continue;
            }

            if (it0->value < 0 && it1->value < 0)
            {
                points0.erase(it0);
                if (points1[i].value != 0)
                {
                    points1.erase(points1.begin() + i);
                }
            }
            else if (it0->value > 0 && it1->value > 0)
            {
                points0.erase(it1);
                if (points1[j].value != 0)
                {
                    points1.erase(points1.begin() + j);
                }
            }
            break;
        }
        break;
    }

    std::vector<Geometry::Point> result;
    size_t index0 = 0, index1 = 0;
    size_t count0 = points0.size(), count1 = points1.size();
    size_t count2 = count0 + count1;
    for (Geometry::MarkedPoint &p : points0)
    {
        p.active = true;
    }
    for (Geometry::MarkedPoint &p : points1)
    {
        p.active = true;
    }
    output.clear();

    while (count0 > 0 && count1 > 0)
    {
        output.emplace_back();

        index0 = index1 = 0;
        while (index0 < count0 && points0[index0].value < 1)
        {
            ++index0;
        }

        if (index0 >= count0)
        {
            output.pop_back();
            break;
        }

        while (result.size() < count2 && (result.size() < 4 || result.front() != result.back()))
        {
            while (result.size() < count2 && (result.size() < 4 || result.front() != result.back()))
            {
                if (points0[index0].value > -1)
                {
                    if (points0[index0].original)
                    {
                        points0[index0].active = false;
                    }
                    result.emplace_back(points0[index0++]);
                }
                else
                {
                    index1 = 0;
                    while (index1 < count1 && points1[index1] != points0[index0])
                    {
                        ++index1;
                    }
                    index1 %= count1;
                    result.emplace_back(points1[index1++]);
                    ++index0;
                    index0 %= count0;
                    index1 %= count1;
                    break;
                }
                index0 %= count0;
            }

            while (result.size() < count2 && (result.size() < 4 || result.front() != result.back()))
            {
                if (points1[index1].value > -1)
                {
                    if (points1[index1].original)
                    {
                        points1[index1].active = false;
                    }
                    result.emplace_back(points1[index1++]);
                }
                else
                {
                    index0 = 0;
                    while (index0 < count0 && points0[index0] != points1[index1])
                    {
                        ++index0;
                    }
                    index0 %= count0;
                    result.emplace_back(points0[index0++]);
                    ++index1;
                    index0 %= count0;
                    index1 %= count1;
                    break;
                }
                index1 %= count1;
            }
        }

        for (size_t i = result.size() - 1; i > 1; --i)
        {
            if (Geometry::is_inside(result[i - 1], result[i - 2], result[i]))
            {
                result.erase(result.begin() + i - 1);
            }
            else if (Geometry::distance(result[i - 2], result[i]) < Geometry::EPSILON)
            {
                result.erase(result.begin() + i--);
                result.erase(result.begin() + i);
            }
        }
        if (result.size() > 4)
        {
            if (Geometry::is_inside(result.front(), result[1], result[result.size() - 2]))
            {
                result.pop_back();
                std::swap(result.front(), result.back());
                result.pop_back();
            }
            else if (Geometry::distance(result[1], result[result.size() - 2]) < Geometry::EPSILON)
            {
                result.pop_back();
                result.pop_back();
                result.erase(result.begin());
            }
        }
        output.back().append(result.begin(), result.end());

        it0 = points0.begin();
        while (it0 != points0.end())
        {
            if (!it0->active || std::find(result.begin(), result.end(), *it0) != result.end())
            {
                it0 = points0.erase(it0);
            }
            else
            {
                ++it0;
            }
        }
        it1 = points1.begin();
        while (it1 != points1.end())
        {
            if (!it1->active || std::find(result.begin(), result.end(), *it1) != result.end())
            {
                it1 = points1.erase(it1);
            }
            else
            {
                ++it1;
            }
        }

        if (output.back().area() == 0)
        {
            output.pop_back();
        }

        if (std::count_if(points0.cbegin(), points0.cend(), [](const Geometry::MarkedPoint &p){ return p.value < 0; }) == 0 ||
            std::count_if(points1.cbegin(), points1.cend(), [](const Geometry::MarkedPoint &p){ return p.value < 0; }) == 0)
        {
            break;
        }

        count0 = points0.size();
        count1 = points1.size();
        count2 = count0 + count1;
        result.clear();
    }

    return !output.empty();
}


std::vector<size_t> Geometry::ear_cut_to_indexs(const Geometry::Polygon &polygon)
{
    std::vector<std::vector<std::array<double, 2>>> points;
    points.emplace_back(std::vector<std::array<double, 2>>());
    for (const Geometry::Point &point : polygon)
    {
        points.front().emplace_back(std::array<double, 2>({point.x, point.y}));
    }
    return mapbox::earcut<size_t>(points);
}

std::vector<size_t> Geometry::ear_cut_to_indexs_test(const Geometry::Polygon &polygon)
{
    std::vector<size_t> indexs, ear_indexs;
    if (polygon.is_cw())
    {
        for (size_t i = 0, count = polygon.size() - 1; i < count; ++i)
        {
            indexs.push_back(count - i);
        }
    }
    else
    {
        for (size_t i = 0, count = polygon.size() - 1; i < count; ++i)
        {
            indexs.push_back(i);
        }
    }

    bool is_ear;
    while (indexs.size() > 3)
    {
        for (size_t pre, cur, nxt, i = 0, count = indexs.size(); i < count; ++i)
        {
            pre = i > 0 ? indexs[i - 1] : indexs[count - 1];
            cur = indexs[i];
            nxt = i < count - 1 ? indexs[i + 1] : indexs[0];
            if ((polygon[cur] - polygon[pre]).cross(polygon[nxt] - polygon[cur]) > 0)
            {
                is_ear = true;
                for (size_t index : indexs)
                {
                    if (index == pre || index == cur || index == nxt)
                    {
                        continue;
                    }
                    if (is_inside(polygon[index], polygon[pre], polygon[cur], polygon[nxt]))
                    {
                        is_ear = false;
                        break;
                    }
                }
                if (is_ear)
                {
                    ear_indexs.push_back(pre);
                    ear_indexs.push_back(cur);
                    ear_indexs.push_back(nxt);
                    indexs.erase(indexs.begin() + i--);
                    --count;
                }
            }
        }
    }

    ear_indexs.insert(ear_indexs.end(), indexs.begin(), indexs.end());
    return ear_indexs;
}

std::vector<Geometry::MarkedPoint> Geometry::ear_cut_to_coords(const Geometry::Polygon &polygon)
{
    std::vector<Geometry::MarkedPoint> result;
    for (size_t i : Geometry::ear_cut_to_indexs(polygon))
    {
        result.emplace_back(polygon[i].x, polygon[i].y);
    }
    return result;
}

std::vector<Geometry::Point> Geometry::ear_cut_to_points(const Geometry::Polygon &polygon)
{
    std::vector<Geometry::Point> result;
    for (size_t i : Geometry::ear_cut_to_indexs(polygon))
    {
        result.emplace_back(polygon[i]);
    }
    return result;
}

std::vector<Geometry::Triangle> Geometry::ear_cut_to_triangles(const Geometry::Polygon &polygon)
{
    std::vector<size_t> indexs;
    if (polygon.is_cw())
    {
        for (size_t i = 0, count = polygon.size() - 1; i < count; ++i)
        {
            indexs.push_back(count - i);
        }
    }
    else
    {
        for (size_t i = 0, count = polygon.size() - 1; i < count; ++i)
        {
            indexs.push_back(i);
        }
    }

    std::vector<Geometry::Triangle> triangles;
    bool is_ear, is_cut;
    while (indexs.size() > 3)
    {
        is_cut = false;
        for (size_t pre, cur, nxt, i = 0, count = indexs.size(); i < count; ++i)
        {
            pre = i > 0 ? indexs[i - 1] : indexs[count - 1];
            cur = indexs[i];
            nxt = i < count - 1 ? indexs[i + 1] : indexs[0];
            if ((polygon[cur] - polygon[pre]).cross(polygon[nxt] - polygon[cur]) > 0)
            {
                is_ear = true;
                for (size_t index : indexs)
                {
                    if (index == pre || index == cur || index == nxt)
                    {
                        continue;
                    }
                    if (is_inside(polygon[index], polygon[pre], polygon[cur], polygon[nxt]))
                    {
                        is_ear = false;
                        break;
                    }
                }
                if (is_ear)
                {
                    triangles.emplace_back(polygon[pre], polygon[cur], polygon[nxt]);
                    indexs.erase(indexs.begin() + i--);
                    --count;
                    is_cut = true;
                }
            }
        }

        if (!is_cut)
        {
            triangles.clear();
            break;
        }
    }

    if (indexs.size() == 3)
    {
        triangles.emplace_back(polygon[indexs[0]], polygon[indexs[1]], polygon[indexs[2]]);
    }
    
    return triangles;
}

bool Geometry::merge_ear_cut_triangles(const std::vector<Geometry::Triangle> &triangles, std::vector<Geometry::Polygon> &polygons)
{
    if (triangles.empty())
    {
        return false;
    }
    
    polygons.clear();
    const size_t triangles_count = triangles.size();
    size_t merged_count = 1, index = 0;
    int index0, index1, index2;
    std::vector<bool> merged(triangles_count, false), current_triangles(triangles_count, false);
    Geometry::Polygon points;
    bool flag;

    while (merged_count < triangles_count)
    {
        while (index < triangles_count && merged[index])
        {
            ++index;
        }
        if (index == triangles_count)
        {
            break;
        }

        points.append(triangles[index][0]);
        points.append(triangles[index][1]);
        points.append(triangles[index][2]);
        merged[index] = true;
        current_triangles.assign(triangles_count, false);
        current_triangles[index++] = true;

        flag = true;
        for (size_t i = index; i < triangles_count; ++i)
        {
            if (merged[i])
            {
                continue;
            }

            for (size_t j = 1, count = points.size(); j < count; ++j)
            {
                index0 = index1 = index2 = -1;
                if (points[j - 1] == triangles[i][0])
                {
                    index0 = 0;
                }
                else if (points[j - 1] == triangles[i][1])
                {
                    index0 = 1;
                }
                else if (points[j - 1] == triangles[i][2])
                {
                    index0 = 2;
                }

                if (points[j] == triangles[i][0])
                {
                    index1 = 0;
                }
                else if (points[j] == triangles[i][1])
                {
                    index1 = 1;
                }
                else if (points[j] == triangles[i][2])
                {
                    index1 = 2;
                }

                if (index0 == -1 || index1 == -1)
                {
                    continue;
                }
                index2 = 3 - index0 - index1;

                flag = true;
                for (size_t k = 0; k < triangles_count; ++k)
                {
                    if (current_triangles[k] && Geometry::is_inside(triangles[i][index2], triangles[k]))
                    {
                        flag = false;
                        break;
                    }
                }

                if (flag)
                {
                    points.insert(j, triangles[i][index2]);
                    ++merged_count;
                    merged[i] = true;
                    current_triangles[i] = true;
                    break;
                }
            }
        }
        
        index = 0;
        polygons.emplace_back(points);
        points.clear();
    }

    return !polygons.empty();
}


bool Geometry::offset(const Geometry::Polyline &input, Geometry::Polyline &result, const double distance)
{
    if (distance != 0)
    {
        Geometry::Polyline temp(input);
        result.clear();
        double area = 0;
        for (size_t i = 1, count = temp.size(); i < count; ++i)
        {
            area += (temp[i].x * (temp[i+1 != count ? i+1 : 0].y - temp[i-1].y));
        }
        area += (temp.front().x * (temp[1].y - temp.back().y));
        if (area > 0)
        {
            temp.flip();
        }
        Geometry::Point a, b;
        result.append(temp.front() + (temp[1] - temp[0]).vertical().normalize() * distance);
        for (size_t i = 1, end = temp.size() - 1; i < end; ++i)
        {
            a = (temp[i] - temp[i > 0 ? i - 1 : end]).vertical().normalize();
            b = (temp[i < end ? i + 1 : 0] - temp[i]).vertical().normalize();
            result.append(temp[i] + (a + b).normalize() * (distance / std::sqrt((1 + a * b) / 2)));
        }
        result.append(temp.back() + (temp.back() - temp[temp.size() - 2]).vertical().normalize() * distance);
        return true;
    }
    else
    {
        result = input;
        return true;
    }
}

bool Geometry::offset(const Geometry::Polygon &input, Geometry::Polygon &result, const double distance)
{
    if (distance == 0)
    {
        result = input;
        return true;
    }

    Geometry::Polygon temp(input);
    temp.reorder_points();
    result.clear();
    std::vector<Geometry::Point> points;
    Geometry::Point a, b;
    std::vector<bool> error_edges;
    if (distance > 0)
    {
        for (size_t i = 0, count = temp.size(); i < count; ++i)
        {
            a = (temp[i] - temp[i > 0 ? i - 1 : count - 2]).vertical().normalize();
            b = (temp[i < count - 1 ? i + 1 : 1] - temp[i]).vertical().normalize();
            points.emplace_back(temp[i] + (a + b).normalize() * (distance / std::sqrt((1 + a * b) / 2)));
        }
        result.append(points.cbegin(), points.cend());

        for (size_t i = 1, count = result.size(); i < count; ++i)
        {
            error_edges.push_back((temp[i] - temp[i - 1]) * (result[i] - result[i - 1]) < 0);
        }
        for (size_t i = 0, edge_count = error_edges.size(), point_count = temp.size(),
                count = result.size(), of = 0, j = 0; i < edge_count; ++i)
        {
            if (error_edges[i])
            {
                j = i - of++;
                if (error_edges[(i + 1) % edge_count])
                {
                    b = (temp.next_point(i) - temp[i]).vertical().normalize() * distance;
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    Geometry::is_intersected(result.last_point(j), result[j],
                        temp[i] + b, temp.next_point(i) + b, a, true);
                    if (!std::isinf(a.x) && !std::isinf(a.y))
                    {
                        result[j] = a;
                    }
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    Geometry::is_intersected(result.next_point(result.next_point_index(j)),
                        result.next_point(result.next_point_index(result.next_point_index(j))),
                        temp[i] + b, temp.next_point(i) + b, a, true);
                    if (!std::isinf(a.x) && !std::isinf(a.y))
                    {
                        result.next_point(result.next_point_index(j)) = a;
                    }
                    result.remove(result.next_point_index(j));
                    --count;
                    ++i;
                }
                else
                {
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    if (Geometry::is_intersected(result.last_point(j), result[j],
                        result.next_point(j), result.next_point(result.next_point_index(j)), a, true))
                    {
                        if (!std::isinf(a.x) && !std::isinf(a.y))
                        {
                            result[j] = a;
                        }
                        result.remove(result.next_point_index(j));
                        --count;
                    }
                    else
                    {
                        b = (temp[i] - temp.last_point(i)).vertical().normalize() * distance;
                        Geometry::is_intersected(result.next_point(result.next_point_index(j)),
                            result.next_point(result.next_point_index(result.next_point_index(j))),
                            temp[i] + b, temp.last_point(i) + b, a, true);
                        b = (temp.next_point(temp.next_point_index(i)) - temp.next_point(i)).vertical().normalize() * distance;
                        Geometry::is_intersected(result.last_point(j), result.last_point(result.last_point_index(j)),
                            temp.next_point(i) + b, temp.next_point(temp.next_point_index(i)) + b, b, true);

                        if ((temp.next_point(temp.next_point_index(i)) - temp.last_point(i)) * (a - b) < 0)
                        {
                            result.next_point(result.next_point_index(j)) = a;
                        }
                        else
                        {
                            result.last_point(j) = b;
                        }

                        size_t temp_index = result.next_point_index(j);
                        result.remove(temp_index);
                        --count;
                        if (temp_index > j)
                        {
                            result.remove(j % count--);
                        }
                        else
                        {
                            result.remove((j - 1) % count--);
                        }
                        ++of;
                    }
                }
            }
        }
    }
    else
    {
        for (size_t i = 0, count = temp.size(); i < count; ++i)
        {
            a = (temp[i] - temp[i > 0 ? i - 1 : count - 2]).vertical().normalize();
            b = (temp[i < count - 1 ? i + 1 : 1] - temp[i]).vertical().normalize();
            points.emplace_back(temp[i] + (a + b).normalize() * (distance / std::sqrt((1 + a * b) / 2)));
        }
        result.append(points.cbegin(), points.cend());

        for (size_t i = 1, count = result.size(); i < count; ++i)
        {
            error_edges.push_back((temp[i] - temp[i - 1]) * (result[i] - result[i - 1]) < 0);
        }
        for (size_t i = 0, edge_count = error_edges.size(), point_count = temp.size(),
                count = result.size(), of = 0, j = 0; i < edge_count; ++i)
        {
            if (error_edges[i])
            {
                j = i - of++;
                if (error_edges[(i + 1) % edge_count])
                {
                    b = (temp.next_point(i) - temp[i]).vertical().normalize() * distance;
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    Geometry::is_intersected(result.last_point(j), result[j],
                        temp[i] + b, temp.next_point(i) + b, a, true);
                    if (!std::isinf(a.x) && !std::isinf(a.y))
                    {
                        result[j] = a;
                    }
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    Geometry::is_intersected(result.next_point(result.next_point_index(j)),
                        result.next_point(result.next_point_index(result.next_point_index(j))),
                        temp[i] + b, temp.next_point(i) + b, a, true);
                    if (!std::isinf(a.x) && !std::isinf(a.y))
                    {
                        result.next_point(result.next_point_index(j)) = a;
                    }
                    result.remove(result.next_point_index(j));
                    --count;
                    ++i;
                }
                else
                {
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    if (Geometry::is_intersected(result.last_point(j), result[j],
                        result.next_point(j), result.next_point(result.next_point_index(j)), a, true))
                    {
                        if (!std::isinf(a.x) && !std::isinf(a.y))
                        {
                            result[j] = a;
                        }
                        result.remove(result.next_point_index(j));
                        --count;
                    }
                    else
                    {
                        b = (temp[i] - temp.last_point(i)).vertical().normalize() * distance;
                        Geometry::is_intersected(result.next_point(result.next_point_index(j)),
                            result.next_point(result.next_point_index(result.next_point_index(j))),
                            temp[i] + b, temp.last_point(i) + b, a, true);
                        b = (temp.next_point(temp.next_point_index(i)) - temp.next_point(i)).vertical().normalize() * distance;
                        Geometry::is_intersected(result.last_point(j), result.last_point(result.last_point_index(j)),
                            temp.next_point(i) + b, temp.next_point(temp.next_point_index(i)) + b, b, true);

                        if ((temp.next_point(temp.next_point_index(i)) - temp.last_point(i)) * (a - b) < 0)
                        {
                            result.next_point(result.next_point_index(j)) = a;
                        }
                        else
                        {
                            result.last_point(j) = b;
                        }

                        size_t temp_index = result.next_point_index(j);
                        result.remove(temp_index);
                        --count;
                        if (temp_index > j)
                        {
                            result.remove(j % count--);
                        }
                        else
                        {
                            result.remove((j - 1) % count--);
                        }
                        ++of;
                    }
                }
            }
        }
    }

    for (size_t i = 0, count = result.size(); i < count; ++i)
    {
        if (std::isnan(result[i].x) || std::isnan(result[i].y) || std::isinf(result[i].x) || std::isinf(result[i].y))
        {
            result.remove(i--);
            --count;
        }
    }
    result.back() = result.front();

    for (size_t i = 0, count = result.size() - 1; i < count; ++i)
    {
        if (Geometry::is_inside(result[i], result[i + 1], result.next_point(i + 1))
            && Geometry::is_inside(result[i + 1], result[i], result.last_point(i)))
        {
            result.remove(i + 1);
            result.remove(i--);
            --count;
            --count;
        }
    }
    for (size_t i = 0, count = result.size(); i < count; ++i)
    {
        if (Geometry::is_inside(result[i], result.last_point(i), result.next_point(i)))
        {
            result.remove(i--);
            --count;
        }
    }

    return true;
}

bool Geometry::offset_test(const Geometry::Polygon &input, Geometry::Polygon &result, const double distance)
{
    if (distance == 0)
    {
        result = input;
        return true;
    }

    Geometry::Polygon temp(input);
    temp.reorder_points();
    result.clear();
    std::vector<Geometry::Point> points;
    Geometry::Point a, b;
    std::vector<bool> error_edges;
    if (distance > 0)
    {
        for (size_t i = 0, count = temp.size(); i < count; ++i)
        {
            a = (temp[i] - temp[i > 0 ? i - 1 : count - 2]).vertical().normalize();
            b = (temp[i < count - 1 ? i + 1 : 1] - temp[i]).vertical().normalize();
            points.emplace_back(temp[i] + (a + b).normalize() * (distance / std::sqrt((1 + a * b) / 2)));
        }
        result.append(points.cbegin(), points.cend());

        for (size_t i = 1, count = result.size(); i < count; ++i)
        {
            error_edges.push_back((temp[i] - temp[i - 1]) * (result[i] - result[i - 1]) < 0);
        }
        for (size_t i = 0, edge_count = error_edges.size(), point_count = temp.size(),
                count = result.size(), of = 0, j = 0; i < edge_count; ++i)
        {
            if (error_edges[i])
            {
                j = i - of++;
                if (error_edges[(i + 1) % edge_count])
                {
                    b = (temp.next_point(i) - temp[i]).vertical().normalize() * distance;
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    Geometry::is_intersected(result.last_point(j), result[j],
                        temp[i] + b, temp.next_point(i) + b, a, true);
                    if (!std::isinf(a.x) && !std::isinf(a.y))
                    {
                        result[j] = a;
                    }
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    Geometry::is_intersected(result.next_point(result.next_point_index(j)),
                        result.next_point(result.next_point_index(result.next_point_index(j))),
                        temp[i] + b, temp.next_point(i) + b, a, true);
                    if (!std::isinf(a.x) && !std::isinf(a.y))
                    {
                        result.next_point(result.next_point_index(j)) = a;
                    }
                    result.remove(result.next_point_index(j));
                    --count;
                    ++i;
                }
                else
                {
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    if (Geometry::is_intersected(result.last_point(j), result[j],
                        result.next_point(j), result.next_point(result.next_point_index(j)), a, true))
                    {
                        if (!std::isinf(a.x) && !std::isinf(a.y))
                        {
                            result[j] = a;
                        }
                        result.remove(result.next_point_index(j));
                        --count;
                    }
                    else
                    {
                        b = (temp[i] - temp.last_point(i)).vertical().normalize() * distance;
                        Geometry::is_intersected(result.next_point(result.next_point_index(j)),
                            result.next_point(result.next_point_index(result.next_point_index(j))),
                            temp[i] + b, temp.last_point(i) + b, a, true);
                        b = (temp.next_point(temp.next_point_index(i)) - temp.next_point(i)).vertical().normalize() * distance;
                        Geometry::is_intersected(result.last_point(j), result.last_point(result.last_point_index(j)),
                            temp.next_point(i) + b, temp.next_point(temp.next_point_index(i)) + b, b, true);

                        if ((temp.next_point(temp.next_point_index(i)) - temp.last_point(i)) * (a - b) < 0)
                        {
                            result.next_point(result.next_point_index(j)) = a;
                        }
                        else
                        {
                            result.last_point(j) = b;
                        }

                        size_t temp_index = result.next_point_index(j);
                        result.remove(temp_index);
                        --count;
                        if (temp_index > j)
                        {
                            result.remove(j % count--);
                        }
                        else
                        {
                            result.remove((j - 1) % count--);
                        }
                        ++of;
                    }
                }
            }
        }
    }
    else
    {
        for (size_t i = 0, count = temp.size(); i < count; ++i)
        {
            a = (temp[i] - temp[i > 0 ? i - 1 : count - 2]).vertical().normalize();
            b = (temp[i < count - 1 ? i + 1 : 1] - temp[i]).vertical().normalize();
            points.emplace_back(temp[i] + (a + b).normalize() * (distance / std::sqrt((1 + a * b) / 2)));
        }
        result.append(points.cbegin(), points.cend());

        for (size_t i = 1, count = result.size(); i < count; ++i)
        {
            error_edges.push_back((temp[i] - temp[i - 1]) * (result[i] - result[i - 1]) < 0);
        }
        for (size_t i = 0, edge_count = error_edges.size(), point_count = temp.size(),
                count = result.size(), of = 0, j = 0; i < edge_count; ++i)
        {
            if (error_edges[i])
            {
                j = i - of++;
                if (error_edges[(i + 1) % edge_count])
                {
                    b = (temp.next_point(i) - temp[i]).vertical().normalize() * distance;
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    Geometry::is_intersected(result.last_point(j), result[j],
                        temp[i] + b, temp.next_point(i) + b, a, true);
                    if (!std::isinf(a.x) && !std::isinf(a.y))
                    {
                        result[j] = a;
                    }
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    Geometry::is_intersected(result.next_point(result.next_point_index(j)),
                        result.next_point(result.next_point_index(result.next_point_index(j))),
                        temp[i] + b, temp.next_point(i) + b, a, true);
                    if (!std::isinf(a.x) && !std::isinf(a.y))
                    {
                        result.next_point(result.next_point_index(j)) = a;
                    }
                    result.remove(result.next_point_index(j));
                    --count;
                    ++i;
                }
                else
                {
                    a.x = a.y = std::numeric_limits<double>::infinity();
                    if (Geometry::is_intersected(result.last_point(j), result[j],
                        result.next_point(j), result.next_point(result.next_point_index(j)), a, true))
                    {
                        if (!std::isinf(a.x) && !std::isinf(a.y))
                        {
                            result[j] = a;
                        }
                        result.remove(result.next_point_index(j));
                        --count;
                    }
                    else
                    {
                        b = (temp[i] - temp.last_point(i)).vertical().normalize() * distance;
                        Geometry::is_intersected(result.next_point(result.next_point_index(j)),
                            result.next_point(result.next_point_index(result.next_point_index(j))),
                            temp[i] + b, temp.last_point(i) + b, a, true);
                        b = (temp.next_point(temp.next_point_index(i)) - temp.next_point(i)).vertical().normalize() * distance;
                        Geometry::is_intersected(result.last_point(j), result.last_point(result.last_point_index(j)),
                            temp.next_point(i) + b, temp.next_point(temp.next_point_index(i)) + b, b, true);

                        if ((temp.next_point(temp.next_point_index(i)) - temp.last_point(i)) * (a - b) < 0)
                        {
                            result.next_point(result.next_point_index(j)) = a;
                        }
                        else
                        {
                            result.last_point(j) = b;
                        }

                        size_t temp_index = result.next_point_index(j);
                        result.remove(temp_index);
                        --count;
                        if (temp_index > j)
                        {
                            result.remove(j % count--);
                        }
                        else
                        {
                            result.remove((j - 1) % count--);
                        }
                        ++of;
                    }
                }
            }
        }
    }

    for (size_t i = 0, count = result.size(); i < count; ++i)
    {
        if (std::isnan(result[i].x) || std::isnan(result[i].y) || std::isinf(result[i].x) || std::isinf(result[i].y))
        {
            result.remove(i--);
            --count;
        }
    }
    result.back() = result.front();

    std::vector<Geometry::Polygon> polygons;
    if (result.is_self_intersected() && Geometry::merge_ear_cut_triangles(Geometry::ear_cut_to_triangles(result), polygons))
    {
        std::sort(polygons.begin(), polygons.end(), [](const Geometry::Polygon &a, const Geometry::Polygon &b)
            { return a.area() < b.area(); });
        temp = polygons.back();
        polygons.pop_back();
        bool flag;
        std::vector<Geometry::Polygon> polygons2;
        while (!polygons.empty())
        {
            flag = true;
            for (size_t i = 0, count = polygons.size(); i < count; ++i)
            {
                if (Geometry::polygon_union(temp, polygons[i], polygons2))
                {
                    if (polygons2.size() > 1)
                    {
                        temp = *std::max_element(polygons2.begin(), polygons2.end(), 
                            [](const Geometry::Polygon &a, const Geometry::Polygon &b) { return a.area() < b.area(); });
                    }
                    else
                    {
                        temp = polygons2.front();
                    }
                    polygons.erase(polygons.begin() + i);
                    polygons2.clear();
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                break;
            }
        }

        if (!temp.is_self_intersected())
        {
            result = temp;
        }
    }

    for (size_t i = 0, count = result.size() - 1; i < count; ++i)
    {
        if (Geometry::is_inside(result[i], result[i + 1], result.next_point(i + 1))
            && Geometry::is_inside(result[i + 1], result[i], result.last_point(i)))
        {
            result.remove(i + 1);
            result.remove(i--);
            --count;
            --count;
        }
    }
    for (size_t i = 0, count = result.size(); i < count; ++i)
    {
        if (Geometry::is_inside(result[i], result.last_point(i), result.next_point(i)))
        {
            result.remove(i--);
            --count;
        }
    }

    return true;
}

bool Geometry::offset(const Geometry::Circle &input, Geometry::Circle &result, const double distance)
{
    if (distance >= 0 || -distance < input.radius)
    {
        result.x = input.x;
        result.y = input.y;
        result.radius = input.radius + distance;
        return true;
    }
    else
    {
        return false;
    }
}

bool Geometry::offset(const Geometry::AABBRect &input, Geometry::AABBRect &result, const double distance)
{
    if (distance >= 0 || -distance * 2 < std::min(input.width(), input.height()))
    {
        result.set_top(input.top() + distance);
        result.set_right(input.right() + distance);
        result.set_bottom(input.bottom() + distance);
        result.set_left(input.left() + distance);
        return true;
    }
    else
    {
        return false;
    }
}
