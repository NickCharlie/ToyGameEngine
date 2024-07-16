#include "Math/Collision/Algorithm.hpp"
#include "Math/Geometry/Algorithm.hpp"


using namespace ToyGameEngine::Math;

void Collision::gjk_furthest_point(const Geometry::Polygon &polygon, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result)
{
    result = polygon.front();
    Geometry::Point point;
    Geometry::foot_point(start, end, polygon.front(), point, true);
    const Geometry::Vector vec = end - start;
    double value, max_value = vec * (point - start);
    for (size_t i = 1, count = polygon.size() - 1; i < count; ++i)
    {
        Geometry::foot_point(start, end, polygon[i], point, true);
        value = vec * (point - start);
        if (value > max_value)
        {
            max_value = value;
            result = polygon[i];
        }
    }
}

void Collision::gjk_furthest_point(const Geometry::Polyline &polyline, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result)
{
    result = polyline.front();
    Geometry::Point point;
    Geometry::foot_point(start, end, polyline.front(), point, true);
    const Geometry::Vector vec = end - start;
    double value, max_value = vec * (point - start);
    for (size_t i = 1, count = polyline.size() - 1; i < count; ++i)
    {
        Geometry::foot_point(start, end, polyline[i], point, true);
        value = vec * (point - start);
        if (value > max_value)
        {
            max_value = value;
            result = polyline[i];
        }
    }
}

void Collision::gjk_furthest_point(const Geometry::Bezier &bezier, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result)
{
    return Collision::gjk_furthest_point(bezier.shape(), start, end, result);
}

void Collision::gjk_furthest_point(const Geometry::Rectangle &rectangle, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result)
{
    result = rectangle[0];
    Geometry::Point point;
    Geometry::foot_point(start, end, rectangle[0], point, true);
    const Geometry::Vector vec = end - start;
    double value, max_value = vec * (point - start);
    for (size_t i = 1; i < 4; ++i)
    {
        Geometry::foot_point(start, end, rectangle[i], point, true);
        value = vec * (point - start);
        if (value > max_value)
        {
            max_value = value;
            result = rectangle[i];
        }
    }
}

void Collision::gjk_furthest_point(const Geometry::Triangle &triangle, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result)
{
    result = triangle[0];
    Geometry::Point point;
    Geometry::foot_point(start, end, triangle[0], point, true);
    const Geometry::Vector vec = end - start;
    double value, max_value = vec * (point - start);
    for (size_t i = 1; i < 3; ++i)
    {
        Geometry::foot_point(start, end, triangle[i], point, true);
        value = vec * (point - start);
        if (value > max_value)
        {
            max_value = value;
            result = triangle[i];
        }
    }
}

void Collision::gjk_furthest_point(const Geometry::Circle &circle, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result)
{
    result = circle;
    result += ((end - start).normalize() * circle.radius);
}

void Collision::gjk_furthest_point(const Geometry::Line &line, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result)
{
    Geometry::Point point0, point1;
    Geometry::foot_point(start, end, line.front(), point0, true);
    Geometry::foot_point(start, end, line.back(), point1, true);
    const Geometry::Vector vec = end - start;
    if (vec * (point0 - start) >= vec * (point1 - start))
    {
        result = line.front();
    }
    else
    {
        result = line.back();
    }
}

void Collision::gjk_furthest_point(const Geometry::Point &point, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result)
{
    result = point;
}


Geometry::Vector Collision::edge_direciton(const Geometry::Point &start, const Geometry::Point &end, const bool to_origin)
{
    Geometry::Vector vec = (end - start).vertical();
    if (to_origin)
    {
        if (vec * (start + start) > 0)
        {
            vec.x = -vec.x;
            vec.y = -vec.y;
        }
    }
    else
    {
        if (vec * (start + start) < 0)
        {
            vec.x = -vec.x;
            vec.y = -vec.y;
        }
    }
    return vec;
}


bool Collision::is_point_inside(const Geometry::Point &point, const Geometry::Polygon &polygon)
{
    for (size_t i = 2, count = polygon.size(); i < count; ++i)
    {
        if (Geometry::is_inside(point, polygon.front(), polygon[i - 1], polygon[i]))
        {
            return true;
        }
    }
    return false;
}


bool Collision::gjk(const Geometry::Circle &circle0, const Geometry::Circle &circle1)
{
    return (circle0.x - circle1.x) * (circle0.x - circle1.x) + (circle0.y - circle1.y) * (circle0.y - circle1.y)
        <= (circle0.radius + circle1.radius) * (circle0.radius + circle1.radius);
}

bool Collision::gjk(const Geometry::Circle &circle, const Geometry::Polygon &polygon)
{
    const double length = circle.radius * circle.radius;
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        if (Geometry::distance_square(circle, polygon[i - 1], polygon[i]) <= length)
        {
            return true;
        }
    }
    return false;
}

bool Collision::gjk(const Geometry::Circle &circle, const Geometry::Rectangle &rectangle)
{
    const double length = circle.radius * circle.radius;
    for (size_t i = 1; i < 4; ++i)
    {
        if (Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]) <= length)
        {
            return true;
        }
    }
    return Geometry::distance_square(circle, rectangle[0], rectangle[3]) <= length;
}

bool Collision::gjk(const Geometry::Circle &circle, const Geometry::AABBRect &rectangle)
{
    const double length = circle.radius * circle.radius;
    for (size_t i = 1; i < 4; ++i)
    {
        if (Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]) <= length)
        {
            return true;
        }
    }
    return Geometry::distance_square(circle, rectangle[0], rectangle[3]) <= length;
}

bool Collision::gjk(const Geometry::Circle &circle, const Geometry::Square &square)
{
    const double length = circle.radius * circle.radius;
    for (size_t i = 1; i < 4; ++i)
    {
        if (Geometry::distance_square(circle, square[i - 1], square[i]) <= length)
        {
            return true;
        }
    }
    return Geometry::distance_square(circle, square[0], square[3]) <= length;
}

bool Collision::gjk(const Geometry::Circle &circle, const Geometry::Triangle &triangle)
{
    return Geometry::distance_square(circle, triangle[0], triangle[1]) ||
        Geometry::distance_square(circle, triangle[1], triangle[2]) ||
        Geometry::distance_square(circle, triangle[0], triangle[2]);
}

bool Collision::gjk(const Geometry::Polygon &polygon, const Geometry::Circle &circle)
{
    const double length = circle.radius * circle.radius;
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        if (Geometry::distance_square(circle, polygon[i - 1], polygon[i]) <= length)
        {
            return true;
        }
    }
    return false;
}

bool Collision::gjk(const Geometry::Rectangle &rectangle, const Geometry::Circle &circle)
{
    const double length = circle.radius * circle.radius;
    for (size_t i = 1; i < 4; ++i)
    {
        if (Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]) <= length)
        {
            return true;
        }
    }
    return Geometry::distance_square(circle, rectangle[0], rectangle[3]) <= length;
}

bool Collision::gjk(const Geometry::AABBRect &rectangle, const Geometry::Circle &circle)
{
    const double length = circle.radius * circle.radius;
    for (size_t i = 1; i < 4; ++i)
    {
        if (Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]) <= length)
        {
            return true;
        }
    }
    return Geometry::distance_square(circle, rectangle[0], rectangle[3]) <= length;
}

bool Collision::gjk(const Geometry::Square &square, const Geometry::Circle &circle)
{
    const double length = circle.radius * circle.radius;
    for (size_t i = 1; i < 4; ++i)
    {
        if (Geometry::distance_square(circle, square[i - 1], square[i]) <= length)
        {
            return true;
        }
    }
    return Geometry::distance_square(circle, square[0], square[3]) <= length;
}

bool Collision::gjk(const Geometry::Triangle &triangle, const Geometry::Circle &circle)
{
    return Geometry::distance_square(circle, triangle[0], triangle[1]) ||
        Geometry::distance_square(circle, triangle[1], triangle[2]) ||
        Geometry::distance_square(circle, triangle[0], triangle[2]);
}

bool Collision::gjk(const Geometry::GeometryObject *points0, const Geometry::GeometryObject *points1)
{
    switch (points0->type())
    {
    case Geometry::Type::POLYGON:
        switch (points1->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::gjk(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Polygon *>(points1));
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::gjk(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1));
        case Geometry::Type::TRIANGLE:
            return Collision::gjk(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Triangle *>(points1));
        case Geometry::Type::CIRCLE:
            return Collision::gjk(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Circle *>(points1));
        case Geometry::Type::POLYLINE:
            return Collision::gjk(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Polyline *>(points1));
        case Geometry::Type::BEZIER:
            return Collision::gjk(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Bezier *>(points1));
        case Geometry::Type::LINE:
            return Collision::gjk(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Line *>(points1));
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points1),
                *static_cast<const Geometry::Polygon *>(points0), true);
        default:
            return false;
        }
    case Geometry::Type::RECTANGLE:
    case Geometry::Type::SQUARE:
    case Geometry::Type::AABBRECT:
        switch (points1->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::gjk(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1));
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::gjk(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1));
        case Geometry::Type::TRIANGLE:
            return Collision::gjk(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1));
        case Geometry::Type::CIRCLE:
            return Collision::gjk(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Circle *>(points1));
        case Geometry::Type::POLYLINE:
            return Collision::gjk(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1));
        case Geometry::Type::BEZIER:
            return Collision::gjk(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1));
        case Geometry::Type::LINE:
            return Collision::gjk(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Line *>(points1));
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points1),
                *static_cast<const Geometry::Rectangle *>(points0), true);
        default:
            return false;
        }
    case Geometry::Type::TRIANGLE:
        switch (points1->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::gjk(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1));
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::gjk(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1));
        case Geometry::Type::TRIANGLE:
            return Collision::gjk(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1));
        case Geometry::Type::CIRCLE:
            return Collision::gjk(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Circle *>(points1));
        case Geometry::Type::POLYLINE:
            return Collision::gjk(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1));
        case Geometry::Type::BEZIER:
            return Collision::gjk(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1));
        case Geometry::Type::LINE:
            return Collision::gjk(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Line *>(points1));
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points1),
                *static_cast<const Geometry::Triangle *>(points0), true);
        default:
            return false;
        }
    case Geometry::Type::CIRCLE:
        switch (points1->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::gjk(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1));
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::gjk(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1));
        case Geometry::Type::TRIANGLE:
            return Collision::gjk(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1));
        case Geometry::Type::CIRCLE:
            return Collision::gjk(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Circle *>(points1));
        case Geometry::Type::POLYLINE:
            return Collision::gjk(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1));
        case Geometry::Type::BEZIER:
            return Collision::gjk(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1));
        case Geometry::Type::LINE:
            return Collision::gjk(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Line *>(points1));
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points1),
                *static_cast<const Geometry::Circle *>(points0), true);
        default:
            return false;
        }
    case Geometry::Type::POLYLINE:
        switch (points1->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::gjk(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Polygon *>(points1));
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::gjk(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1));
        case Geometry::Type::TRIANGLE:
            return Collision::gjk(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Triangle *>(points1));
        case Geometry::Type::CIRCLE:
            return Collision::gjk(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Circle *>(points1));
        case Geometry::Type::POLYLINE:
            return Collision::gjk(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Polyline *>(points1));
        case Geometry::Type::BEZIER:
            return Collision::gjk(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Bezier *>(points1));
        case Geometry::Type::LINE:
            return Collision::gjk(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Line *>(points1));
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points1),
                *static_cast<const Geometry::Polyline *>(points0));
        default:
            return false;
        }
    case Geometry::Type::BEZIER:
        switch (points1->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::gjk(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Polygon *>(points1));
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::gjk(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1));
        case Geometry::Type::TRIANGLE:
            return Collision::gjk(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Triangle *>(points1));
        case Geometry::Type::CIRCLE:
            return Collision::gjk(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Circle *>(points1));
        case Geometry::Type::POLYLINE:
            return Collision::gjk(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Polyline *>(points1));
        case Geometry::Type::BEZIER:
            return Collision::gjk(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Bezier *>(points1));
        case Geometry::Type::LINE:
            return Collision::gjk(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Line *>(points1));
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points1),
                static_cast<const Geometry::Bezier *>(points0)->shape());
        default:
            return false;
        }
    case Geometry::Type::LINE:
        switch (points1->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::gjk(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Polygon *>(points1));
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::gjk(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1));
        case Geometry::Type::TRIANGLE:
            return Collision::gjk(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Triangle *>(points1));
        case Geometry::Type::CIRCLE:
            return Collision::gjk(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Circle *>(points1));
        case Geometry::Type::POLYLINE:
            return Collision::gjk(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Polyline *>(points1));
        case Geometry::Type::BEZIER:
            return Collision::gjk(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Bezier *>(points1));
        case Geometry::Type::LINE:
            return Collision::gjk(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Line *>(points1));
        case Geometry::Type::POINT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points1),
                *static_cast<const Geometry::Line *>(points0));
        default:
            return false;
        }
    case Geometry::Type::POINT:
        switch (points1->type())
        {
        case Geometry::Type::POLYGON:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), true);
        case Geometry::Type::RECTANGLE:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), true);
        case Geometry::Type::SQUARE:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points0),
                *static_cast<const Geometry::Square *>(points1), true);
        case Geometry::Type::AABBRECT:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points0),
                *static_cast<const Geometry::AABBRect *>(points1), true);
        case Geometry::Type::TRIANGLE:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), true);
        case Geometry::Type::CIRCLE:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points0),
                *static_cast<const Geometry::Circle *>(points1), true);
        case Geometry::Type::POLYLINE:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points0),
                *static_cast<const Geometry::Polyline *>(points1));
        case Geometry::Type::BEZIER:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points0),
                static_cast<const Geometry::Bezier *>(points1)->shape());
        case Geometry::Type::LINE:
            return Geometry::is_inside(*static_cast<const Geometry::Point *>(points0),
                *static_cast<const Geometry::Line *>(points1));
        case Geometry::Type::POINT:
            return *static_cast<const Geometry::Point *>(points0) ==
                *static_cast<const Geometry::Point *>(points1);
        default:
            return false;
        }
    default:
        return false;
    }
}


double Collision::epa(const Geometry::Circle &circle0, const Geometry::Circle &circle1, Geometry::Vector &vec)
{
    vec.clear();
    const double length = Geometry::distance(circle0, circle1);
    if (length < circle0.radius + circle1.radius)
    {
        vec = (circle1 - circle0).normalize() * (circle0.radius + circle1.radius - length);
        return circle0.radius + circle1.radius - length;
    }
    else if (length == circle0.radius + circle1.radius)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

double Collision::epa(const Geometry::Circle &circle, const Geometry::Polygon &polygon, Geometry::Vector &vec)
{
    double length = DBL_MAX, distance = 0;
    size_t index = 1;
    vec.clear();
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        distance = Geometry::distance_square(circle, polygon[i - 1], polygon[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    Geometry::Point point;
    if (Collision::is_point_inside(circle, polygon))
    {
        if (Geometry::foot_point(polygon[index - 1], polygon[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, vec, circle, point);
            vec = point - vec;
        }
        else
        {
            if (Geometry::distance_square(circle, polygon[index - 1]) <= Geometry::distance_square(circle, polygon[index]))
            {
                Collision::gjk_furthest_point(circle, polygon[index - 1], circle, point);
                vec = point - polygon[index - 1];
            }
            else
            {
                Collision::gjk_furthest_point(circle, polygon[index], circle, point);
                vec = point - polygon[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(polygon[index - 1], polygon[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, circle, vec, point);
            vec = point - vec;
        }
        else
        {
            if (Geometry::distance_square(circle, polygon[index - 1]) <= Geometry::distance_square(circle, polygon[index]))
            {
                Collision::gjk_furthest_point(circle, circle, polygon[index - 1], point);
                vec = point - polygon[index - 1];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, polygon[index], point);
                vec = point - polygon[index];
            }
        }
    }
    return vec.length();
}

double Collision::epa(const Geometry::Circle &circle, const Geometry::Rectangle &rectangle, Geometry::Vector &vec)
{
    double length = Geometry::distance_square(circle, rectangle[0], rectangle[3]), distance = 0;
    size_t index = 0;
    vec.clear();
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    Geometry::Point point;
    if (Geometry::is_inside(circle, rectangle))
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, vec, circle, point);
            vec = point - vec;
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, rectangle[index > 0 ? index - 1 : 3], circle, point);
                vec = point - rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, rectangle[index], circle, point);
                vec = point - rectangle[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, circle, vec, point);
            vec = point - vec;
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index > 0 ? index - 1 : 3], point);
                vec = point - rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index], point);
                vec = point - rectangle[index];
            }
        }
    }
    return vec.length();
}

double Collision::epa(const Geometry::Circle &circle, const Geometry::AABBRect &rectangle, Geometry::Vector &vec)
{
    double length = Geometry::distance_square(circle, rectangle[0], rectangle[3]), distance = 0;
    size_t index = 0;
    vec.clear();
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    Geometry::Point point;
    if (Geometry::is_inside(circle, rectangle))
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, vec, circle, point);
            vec = point - vec;
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, rectangle[index > 0 ? index - 1 : 3], circle, point);
                vec = point - rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, rectangle[index], circle, point);
                vec = point - rectangle[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, circle, vec, point);
            vec = point - vec;
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index > 0 ? index - 1 : 3], point);
                vec = point - rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index], point);
                vec = point - rectangle[index];
            }
        }
    }
    return vec.length();
}

double Collision::epa(const Geometry::Circle &circle, const Geometry::Square &square, Geometry::Vector &vec)
{
    double length = Geometry::distance_square(circle, square[0], square[3]), distance = 0;
    size_t index = 0;
    vec.clear();
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, square[i - 1], square[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    Geometry::Point point;
    if (Geometry::is_inside(circle, square))
    {
        if (Geometry::foot_point(square[index > 0 ? index - 1 : 3], square[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, vec, circle, point);
            vec = point - vec;
        }
        else
        {
            if (Geometry::distance_square(circle, square[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, square[index]))
            {
                Collision::gjk_furthest_point(circle, square[index > 0 ? index - 1 : 3], circle, point);
                vec = point - square[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, square[index], circle, point);
                vec = point - square[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(square[index > 0 ? index - 1 : 3], square[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, circle, vec, point);
            vec = point - vec;
        }
        else
        {
            if (Geometry::distance_square(circle, square[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, square[index]))
            {
                Collision::gjk_furthest_point(circle, circle, square[index > 0 ? index - 1 : 3], point);
                vec = point - square[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, square[index], point);
                vec = point - square[index];
            }
        }
    }
    return vec.length();
}

double Collision::epa(const Geometry::Circle &circle, const Geometry::Triangle &triangle, Geometry::Vector &vec)
{
    double length = Geometry::distance_square(circle, triangle[0], triangle[2]), distance = 0;
    size_t index = 0;
    vec.clear();
    for (size_t i = 1; i < 3; ++i)
    {
        distance = Geometry::distance_square(circle, triangle[i - 1], triangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    Geometry::Point point;
    if (Geometry::is_inside(circle, triangle))
    {
        if (Geometry::foot_point(triangle[index > 0 ? index - 1 : 2], triangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, vec, circle, point);
            vec = point - vec;
        }
        else
        {
            if (Geometry::distance_square(circle, triangle[index > 0 ? index - 1 : 2])
                <= Geometry::distance_square(circle, triangle[index]))
            {
                Collision::gjk_furthest_point(circle, triangle[index > 0 ? index - 1 : 2], circle, point);
                vec = point - triangle[index > 0 ? index - 1 : 2];
            }
            else
            {
                Collision::gjk_furthest_point(circle, triangle[index], circle, point);
                vec = point - triangle[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(triangle[index > 0 ? index - 1 : 2], triangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, circle, vec, point);
            vec = point - vec;
        }
        else
        {
            if (Geometry::distance_square(circle, triangle[index > 0 ? index - 1 : 2])
                <= Geometry::distance_square(circle, triangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, triangle[index > 0 ? index - 1 : 2], point);
                vec = point - triangle[index > 0 ? index - 1 : 2];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, triangle[index], point);
                vec = point - triangle[index];
            }
        }
    }
    return vec.length();
}

double Collision::epa(const Geometry::Polygon &polygon, const Geometry::Circle &circle, Geometry::Vector &vec)
{
    double length = DBL_MAX, distance = 0;
    size_t index = 1;
    vec.clear();
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        distance = Geometry::distance_square(circle, polygon[i - 1], polygon[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    Geometry::Point point;
    if (Collision::is_point_inside(circle, polygon))
    {
        if (Geometry::foot_point(polygon[index - 1], polygon[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, vec, circle, point);
            vec -= point;
        }
        else
        {
            if (Geometry::distance_square(circle, polygon[index - 1]) <= Geometry::distance_square(circle, polygon[index]))
            {
                Collision::gjk_furthest_point(circle, polygon[index - 1], circle, point);
                vec = polygon[index - 1] - point;
            }
            else
            {
                Collision::gjk_furthest_point(circle, polygon[index], circle, point);
                vec = polygon[index] - point;
            }
        }
    }
    else
    {
        if (Geometry::foot_point(polygon[index - 1], polygon[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, circle, vec, point);
            vec -= point;
        }
        else
        {
            if (Geometry::distance_square(circle, polygon[index - 1]) <= Geometry::distance_square(circle, polygon[index]))
            {
                Collision::gjk_furthest_point(circle, circle, polygon[index - 1], point);
                vec = polygon[index - 1] - point;
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, polygon[index], point);
                vec = polygon[index] - point;
            }
        }
    }
    return vec.length();
}

double Collision::epa(const Geometry::Rectangle &rectangle, const Geometry::Circle &circle, Geometry::Vector &vec)
{
    double length = Geometry::distance_square(circle, rectangle[0], rectangle[3]), distance = 0;
    size_t index = 0;
    vec.clear();
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    Geometry::Point point;
    if (Geometry::is_inside(circle, rectangle))
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, vec, circle, point);
            vec -= point;
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, rectangle[index > 0 ? index - 1 : 3], circle, point);
                vec = rectangle[index > 0 ? index - 1 : 3] - point;
            }
            else
            {
                Collision::gjk_furthest_point(circle, rectangle[index], circle, point);
                vec = rectangle[index] - point;
            }
        }
    }
    else
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, circle, vec, point);
            vec -= point;
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index > 0 ? index - 1 : 3], point);
                vec = rectangle[index > 0 ? index - 1 : 3] - point;
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index], point);
                vec = rectangle[index] - point;
            }
        }
    }
    return vec.length();
}

double Collision::epa(const Geometry::AABBRect &rectangle, const Geometry::Circle &circle, Geometry::Vector &vec)
{
    double length = Geometry::distance_square(circle, rectangle[0], rectangle[3]), distance = 0;
    size_t index = 0;
    vec.clear();
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    Geometry::Point point;
    if (Geometry::is_inside(circle, rectangle))
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, vec, circle, point);
            vec -= point;
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, rectangle[index > 0 ? index - 1 : 3], circle, point);
                vec = rectangle[index > 0 ? index - 1 : 3] - point;
            }
            else
            {
                Collision::gjk_furthest_point(circle, rectangle[index], circle, point);
                vec = rectangle[index] - point;
            }
        }
    }
    else
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, circle, vec, point);
            vec -= point;
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index > 0 ? index - 1 : 3], point);
                vec = rectangle[index > 0 ? index - 1 : 3] - point;
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index], point);
                vec = rectangle[index] - point;
            }
        }
    }
    return vec.length();
}

double Collision::epa(const Geometry::Square &square, const Geometry::Circle &circle, Geometry::Vector &vec)
{
    double length = Geometry::distance_square(circle, square[0], square[3]), distance = 0;
    size_t index = 0;
    vec.clear();
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, square[i - 1], square[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    Geometry::Point point;
    if (Geometry::is_inside(circle, square))
    {
        if (Geometry::foot_point(square[index > 0 ? index - 1 : 3], square[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, vec, circle, point);
            vec -= point;
        }
        else
        {
            if (Geometry::distance_square(circle, square[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, square[index]))
            {
                Collision::gjk_furthest_point(circle, square[index > 0 ? index - 1 : 3], circle, point);
                vec = square[index > 0 ? index - 1 : 3] - point;
            }
            else
            {
                Collision::gjk_furthest_point(circle, square[index], circle, point);
                vec = square[index] - point;
            }
        }
    }
    else
    {
        if (Geometry::foot_point(square[index > 0 ? index - 1 : 3], square[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, circle, vec, point);
            vec -= point;
        }
        else
        {
            if (Geometry::distance_square(circle, square[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, square[index]))
            {
                Collision::gjk_furthest_point(circle, circle, square[index > 0 ? index - 1 : 3], point);
                vec = square[index > 0 ? index - 1 : 3] - point;
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, square[index], point);
                vec = square[index] - point;
            }
        }
    }
    return vec.length();
}

double Collision::epa(const Geometry::Triangle &triangle, const Geometry::Circle &circle, Geometry::Vector &vec)
{
    double length = Geometry::distance_square(circle, triangle[0], triangle[2]), distance = 0;
    size_t index = 0;
    vec.clear();
    for (size_t i = 1; i < 3; ++i)
    {
        distance = Geometry::distance_square(circle, triangle[i - 1], triangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    Geometry::Point point;
    if (Geometry::is_inside(circle, triangle))
    {
        if (Geometry::foot_point(triangle[index > 0 ? index - 1 : 2], triangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, vec, circle, point);
            vec -= point;
        }
        else
        {
            if (Geometry::distance_square(circle, triangle[index > 0 ? index - 1 : 2])
                <= Geometry::distance_square(circle, triangle[index]))
            {
                Collision::gjk_furthest_point(circle, triangle[index > 0 ? index - 1 : 2], circle, point);
                vec = triangle[index > 0 ? index - 1 : 2] - point;
            }
            else
            {
                Collision::gjk_furthest_point(circle, triangle[index], circle, point);
                vec = triangle[index] - point;
            }
        }
    }
    else
    {
        if (Geometry::foot_point(triangle[index > 0 ? index - 1 : 2], triangle[index], circle, vec, false))
        {
            Collision::gjk_furthest_point(circle, circle, vec, point);
            vec -= point;
        }
        else
        {
            if (Geometry::distance_square(circle, triangle[index > 0 ? index - 1 : 2])
                <= Geometry::distance_square(circle, triangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, triangle[index > 0 ? index - 1 : 2], point);
                vec = triangle[index > 0 ? index - 1 : 2] - point;
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, triangle[index], point);
                vec = triangle[index] - point;
            }
        }
    }
    return vec.length();
}

double Collision::epa(const Geometry::GeometryObject *points0, const Geometry::GeometryObject *points1, Geometry::Vector &vec)
{
    switch (points0->type())
    {
    case Geometry::Type::POLYGON:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Circle *>(points1), vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Line *>(points1), vec);
        default:
            return -1;
        }
    case Geometry::Type::RECTANGLE:
    case Geometry::Type::SQUARE:
    case Geometry::Type::AABBRECT:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Circle *>(points1), vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Line *>(points1), vec);
        default:
            return -1;
        }
    case Geometry::Type::TRIANGLE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Circle *>(points1), vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Line *>(points1), vec);
        default:
            return -1;
        }
    case Geometry::Type::CIRCLE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Circle *>(points1), vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Line *>(points1), vec);
        default:
            return -1;
        }
    case Geometry::Type::POLYLINE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Circle *>(points1), vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Line *>(points1), vec);
        default:
            return -1;
        }
    case Geometry::Type::BEZIER:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Circle *>(points1), vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Line *>(points1), vec);
        default:
            return -1;
        }
    case Geometry::Type::LINE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Circle *>(points1), vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Line *>(points1), vec);
        default:
            return -1;
        }
    default:
        return -1;
    }
}


double Collision::epa(const Geometry::Circle &circle0, const Geometry::Circle &circle1, Geometry::Point &head, Geometry::Point &tail)
{
    head.clear(), tail.clear();
    const double length = Geometry::distance(circle0, circle1);
    if (length < circle0.radius + circle1.radius)
    {
        Geometry::Vector vec = (circle1 - circle0).normalize();
        head = circle0 + vec * (circle0.radius - circle1.radius + length);
        tail = circle0 + vec * (3 * circle0.radius + circle1.radius - length);
        return circle0.radius + circle1.radius - length;
    }
    else if (length == circle0.radius + circle1.radius)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

double Collision::epa(const Geometry::Circle &circle, const Geometry::Polygon &polygon, Geometry::Point &head, Geometry::Point &tail)
{
    double length = DBL_MAX, distance = 0;
    size_t index = 1;
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        distance = Geometry::distance_square(circle, polygon[i - 1], polygon[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    if (Collision::is_point_inside(circle, polygon))
    {
        if (Geometry::foot_point(polygon[index - 1], polygon[index], circle, tail, false))
        {
            Collision::gjk_furthest_point(circle, tail, circle, head);
        }
        else
        {
            if (Geometry::distance_square(circle, polygon[index - 1]) <= Geometry::distance_square(circle, polygon[index]))
            {
                Collision::gjk_furthest_point(circle, polygon[index - 1], circle, head);
                tail = polygon[index - 1];
            }
            else
            {
                Collision::gjk_furthest_point(circle, polygon[index], circle, head);
                tail = polygon[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(polygon[index - 1], polygon[index], circle, tail, false))
        {
            Collision::gjk_furthest_point(circle, circle, tail, head);
        }
        else
        {
            if (Geometry::distance_square(circle, polygon[index - 1]) <= Geometry::distance_square(circle, polygon[index]))
            {
                Collision::gjk_furthest_point(circle, circle, polygon[index - 1], head);
                tail = polygon[index - 1];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, polygon[index], head);
                tail = polygon[index];
            }
        }
    }
    return (tail - head).length();
}

double Collision::epa(const Geometry::Circle &circle, const Geometry::Rectangle &rectangle, Geometry::Point &head, Geometry::Point &tail)
{
    double length = Geometry::distance_square(circle, rectangle[0], rectangle[3]), distance = 0;
    size_t index = 0;
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    if (Geometry::is_inside(circle, rectangle))
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, tail, false))
        {
            Collision::gjk_furthest_point(circle, tail, circle, head);
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, rectangle[index > 0 ? index - 1 : 3], circle, head);
                tail = rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, rectangle[index], circle, head);
                tail = rectangle[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, tail, false))
        {
            Collision::gjk_furthest_point(circle, circle, tail, head);
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index > 0 ? index - 1 : 3], head);
                tail = rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index], head);
                tail = rectangle[index];
            }
        }
    }
    return (tail - head).length();
}

double Collision::epa(const Geometry::Circle &circle, const Geometry::AABBRect &rectangle, Geometry::Point &head, Geometry::Point &tail)
{
    double length = Geometry::distance_square(circle, rectangle[0], rectangle[3]), distance = 0;
    size_t index = 0;
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    if (Geometry::is_inside(circle, rectangle))
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, tail, false))
        {
            Collision::gjk_furthest_point(circle, tail, circle, head);
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, rectangle[index > 0 ? index - 1 : 3], circle, head);
                tail = rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, rectangle[index], circle, head);
                tail = rectangle[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, tail, false))
        {
            Collision::gjk_furthest_point(circle, circle, tail, head);
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index > 0 ? index - 1 : 3], head);
                tail = rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index], head);
                tail = rectangle[index];
            }
        }
    }
    return (tail - head).length();
}

double Collision::epa(const Geometry::Circle &circle, const Geometry::Square &square, Geometry::Point &head, Geometry::Point &tail)
{
    double length = Geometry::distance_square(circle, square[0], square[3]), distance = 0;
    size_t index = 0;
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, square[i - 1], square[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    if (Geometry::is_inside(circle, square))
    {
        if (Geometry::foot_point(square[index > 0 ? index - 1 : 3], square[index], circle, tail, false))
        {
            Collision::gjk_furthest_point(circle, tail, circle, head);
        }
        else
        {
            if (Geometry::distance_square(circle, square[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, square[index]))
            {
                Collision::gjk_furthest_point(circle, square[index > 0 ? index - 1 : 3], circle, head);
                tail = square[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, square[index], circle, head);
                tail = square[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(square[index > 0 ? index - 1 : 3], square[index], circle, tail, false))
        {
            Collision::gjk_furthest_point(circle, circle, tail, head);
        }
        else
        {
            if (Geometry::distance_square(circle, square[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, square[index]))
            {
                Collision::gjk_furthest_point(circle, circle, square[index > 0 ? index - 1 : 3], head);
                tail = square[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, square[index], head);
                tail = square[index];
            }
        }
    }
    return (tail - head).length();
}

double Collision::epa(const Geometry::Circle &circle, const Geometry::Triangle &triangle, Geometry::Point &head, Geometry::Point &tail)
{
    double length = Geometry::distance_square(circle, triangle[0], triangle[2]), distance = 0;
    size_t index = 0;
    for (size_t i = 1; i < 3; ++i)
    {
        distance = Geometry::distance_square(circle, triangle[i - 1], triangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    if (Geometry::is_inside(circle, triangle))
    {
        if (Geometry::foot_point(triangle[index > 0 ? index - 1 : 2], triangle[index], circle, tail, false))
        {
            Collision::gjk_furthest_point(circle, tail, circle, head);
        }
        else
        {
            if (Geometry::distance_square(circle, triangle[index > 0 ? index - 1 : 2])
                <= Geometry::distance_square(circle, triangle[index]))
            {
                Collision::gjk_furthest_point(circle, triangle[index > 0 ? index - 1 : 2], circle, head);
                tail = triangle[index > 0 ? index - 1 : 2];
            }
            else
            {
                Collision::gjk_furthest_point(circle, triangle[index], circle, head);
                tail = triangle[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(triangle[index > 0 ? index - 1 : 2], triangle[index], circle, tail, false))
        {
            Collision::gjk_furthest_point(circle, circle, tail, head);
        }
        else
        {
            if (Geometry::distance_square(circle, triangle[index > 0 ? index - 1 : 2])
                <= Geometry::distance_square(circle, triangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, triangle[index > 0 ? index - 1 : 2], head);
                tail = triangle[index > 0 ? index - 1 : 2];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, triangle[index], head);
                tail = triangle[index];
            }
        }
    }
    return (tail - head).length();
}

double Collision::epa(const Geometry::Polygon &polygon, const Geometry::Circle &circle, Geometry::Point &head, Geometry::Point &tail)
{
    double length = DBL_MAX, distance = 0;
    size_t index = 1;
    for (size_t i = 1, count = polygon.size(); i < count; ++i)
    {
        distance = Geometry::distance_square(circle, polygon[i - 1], polygon[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    if (Collision::is_point_inside(circle, polygon))
    {
        if (Geometry::foot_point(polygon[index - 1], polygon[index], circle, head, false))
        {
            Collision::gjk_furthest_point(circle, head, circle, tail);
        }
        else
        {
            if (Geometry::distance_square(circle, polygon[index - 1]) <= Geometry::distance_square(circle, polygon[index]))
            {
                Collision::gjk_furthest_point(circle, polygon[index - 1], circle, tail);
                head = polygon[index - 1];
            }
            else
            {
                Collision::gjk_furthest_point(circle, polygon[index], circle, tail);
                head = polygon[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(polygon[index - 1], polygon[index], circle, head, false))
        {
            Collision::gjk_furthest_point(circle, circle, head, tail);
        }
        else
        {
            if (Geometry::distance_square(circle, polygon[index - 1]) <= Geometry::distance_square(circle, polygon[index]))
            {
                Collision::gjk_furthest_point(circle, circle, polygon[index - 1], tail);
                head = polygon[index - 1];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, polygon[index], tail);
                head = polygon[index];
            }
        }
    }
    return (tail - head).length();
}

double Collision::epa(const Geometry::Rectangle &rectangle, const Geometry::Circle &circle, Geometry::Point &head, Geometry::Point &tail)
{
    double length = Geometry::distance_square(circle, rectangle[0], rectangle[3]), distance = 0;
    size_t index = 0;
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    if (Geometry::is_inside(circle, rectangle))
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, head, false))
        {
            Collision::gjk_furthest_point(circle, head, circle, tail);
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, rectangle[index > 0 ? index - 1 : 3], circle, tail);
                head = rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, rectangle[index], circle, tail);
                head = rectangle[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, head, false))
        {
            Collision::gjk_furthest_point(circle, circle, head, tail);
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index > 0 ? index - 1 : 3], tail);
                head = rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index], tail);
                head = rectangle[index];
            }
        }
    }
    return (tail - head).length();
}

double Collision::epa(const Geometry::AABBRect &rectangle, const Geometry::Circle &circle, Geometry::Point &head, Geometry::Point &tail)
{
    double length = Geometry::distance_square(circle, rectangle[0], rectangle[3]), distance = 0;
    size_t index = 0;
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, rectangle[i - 1], rectangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    if (Geometry::is_inside(circle, rectangle))
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, head, false))
        {
            Collision::gjk_furthest_point(circle, head, circle, tail);
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, rectangle[index > 0 ? index - 1 : 3], circle, tail);
                head = rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, rectangle[index], circle, tail);
                head = rectangle[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(rectangle[index > 0 ? index - 1 : 3], rectangle[index], circle, head, false))
        {
            Collision::gjk_furthest_point(circle, circle, head, tail);
        }
        else
        {
            if (Geometry::distance_square(circle, rectangle[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, rectangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index > 0 ? index - 1 : 3], tail);
                head = rectangle[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, rectangle[index], tail);
                head = rectangle[index];
            }
        }
    }
    return (tail - head).length();
}

double Collision::epa(const Geometry::Square &square, const Geometry::Circle &circle, Geometry::Point &head, Geometry::Point &tail)
{
    double length = Geometry::distance_square(circle, square[0], square[3]), distance = 0;
    size_t index = 0;
    for (size_t i = 1; i < 4; ++i)
    {
        distance = Geometry::distance_square(circle, square[i - 1], square[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    if (Geometry::is_inside(circle, square))
    {
        if (Geometry::foot_point(square[index > 0 ? index - 1 : 3], square[index], circle, head, false))
        {
            Collision::gjk_furthest_point(circle, head, circle, tail);
        }
        else
        {
            if (Geometry::distance_square(circle, square[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, square[index]))
            {
                Collision::gjk_furthest_point(circle, square[index > 0 ? index - 1 : 3], circle, tail);
                head = square[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, square[index], circle, tail);
                head = square[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(square[index > 0 ? index - 1 : 3], square[index], circle, head, false))
        {
            Collision::gjk_furthest_point(circle, circle, head, tail);
        }
        else
        {
            if (Geometry::distance_square(circle, square[index > 0 ? index - 1 : 3])
                <= Geometry::distance_square(circle, square[index]))
            {
                Collision::gjk_furthest_point(circle, circle, square[index > 0 ? index - 1 : 3], tail);
                head = square[index > 0 ? index - 1 : 3];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, square[index], tail);
                head = square[index];
            }
        }
    }
    return (tail - head).length();
}

double Collision::epa(const Geometry::Triangle &triangle, const Geometry::Circle &circle, Geometry::Point &head, Geometry::Point &tail)
{
    double length = Geometry::distance_square(circle, triangle[0], triangle[2]), distance = 0;
    size_t index = 0;
    for (size_t i = 1; i < 3; ++i)
    {
        distance = Geometry::distance_square(circle, triangle[i - 1], triangle[i]);
        if (distance < length)
        {
            length = distance;
            index = i;
        }
    }
    if (length > circle.radius * circle.radius)
    {
        return -1;
    }
    else if (length == circle.radius * circle.radius)
    {
        return 0;
    }

    if (Geometry::is_inside(circle, triangle))
    {
        if (Geometry::foot_point(triangle[index > 0 ? index - 1 : 2], triangle[index], circle, head, false))
        {
            Collision::gjk_furthest_point(circle, head, circle, tail);
        }
        else
        {
            if (Geometry::distance_square(circle, triangle[index > 0 ? index - 1 : 2])
                <= Geometry::distance_square(circle, triangle[index]))
            {
                Collision::gjk_furthest_point(circle, triangle[index > 0 ? index - 1 : 2], circle, tail);
                head = triangle[index > 0 ? index - 1 : 2];
            }
            else
            {
                Collision::gjk_furthest_point(circle, triangle[index], circle, tail);
                head = triangle[index];
            }
        }
    }
    else
    {
        if (Geometry::foot_point(triangle[index > 0 ? index - 1 : 2], triangle[index], circle, head, false))
        {
            Collision::gjk_furthest_point(circle, circle, head, tail);
        }
        else
        {
            if (Geometry::distance_square(circle, triangle[index > 0 ? index - 1 : 2])
                <= Geometry::distance_square(circle, triangle[index]))
            {
                Collision::gjk_furthest_point(circle, circle, triangle[index > 0 ? index - 1 : 2], tail);
                head = triangle[index > 0 ? index - 1 : 2];
            }
            else
            {
                Collision::gjk_furthest_point(circle, circle, triangle[index], tail);
                head = triangle[index];
            }
        }
    }
    return (tail - head).length();
}

double Collision::epa(const Geometry::GeometryObject *points0, const Geometry::GeometryObject *points1, Geometry::Point &head, Geometry::Point &tail)
{
    switch (points0->type())
    {
    case Geometry::Type::POLYGON:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), head, tail);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), head, tail);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), head, tail);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Circle *>(points1), head, tail);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), head, tail);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), head, tail);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Line *>(points1), head, tail);
        default:
            return -1;
        }
    case Geometry::Type::RECTANGLE:
    case Geometry::Type::SQUARE:
    case Geometry::Type::AABBRECT:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), head, tail);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), head, tail);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), head, tail);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Circle *>(points1), head, tail);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), head, tail);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), head, tail);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Line *>(points1), head, tail);
        default:
            return -1;
        }
    case Geometry::Type::TRIANGLE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), head, tail);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), head, tail);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), head, tail);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Circle *>(points1), head, tail);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), head, tail);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), head, tail);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Line *>(points1), head, tail);
        default:
            return -1;
        }
    case Geometry::Type::CIRCLE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), head, tail);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), head, tail);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), head, tail);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Circle *>(points1), head, tail);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), head, tail);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), head, tail);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Line *>(points1), head, tail);
        default:
            return -1;
        }
    case Geometry::Type::POLYLINE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), head, tail);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), head, tail);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), head, tail);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Circle *>(points1), head, tail);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), head, tail);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), head, tail);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Line *>(points1), head, tail);
        default:
            return -1;
        }
    case Geometry::Type::BEZIER:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), head, tail);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), head, tail);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), head, tail);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Circle *>(points1), head, tail);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), head, tail);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), head, tail);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Line *>(points1), head, tail);
        default:
            return -1;
        }
    case Geometry::Type::LINE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), head, tail);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), head, tail);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), head, tail);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Circle *>(points1), head, tail);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), head, tail);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), head, tail);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Line *>(points1), head, tail);
        default:
            return -1;
        }
    default:
        return -1;
    }
}


double Collision::epa(const Geometry::Circle &circle0, const Geometry::Circle &circle1, const double tx, const double ty, Geometry::Vector &vec)
{
    return Collision::epa(circle0, circle1, vec);
}

double Collision::epa(const Geometry::GeometryObject *points0, const Geometry::GeometryObject *points1, const double tx, const double ty, Geometry::Vector &vec)
{
     switch (points0->type())
    {
    case Geometry::Type::POLYGON:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), tx, ty, vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), tx, ty, vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), tx, ty, vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Circle *>(points1), tx, ty, vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), tx, ty, vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), tx, ty, vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Polygon *>(points0),
                *static_cast<const Geometry::Line *>(points1), tx, ty, vec);
        default:
            return -1;
        }
    case Geometry::Type::RECTANGLE:
    case Geometry::Type::SQUARE:
    case Geometry::Type::AABBRECT:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), tx, ty, vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), tx, ty, vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), tx, ty, vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Circle *>(points1), tx, ty, vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), tx, ty, vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), tx, ty, vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Rectangle *>(points0),
                *static_cast<const Geometry::Line *>(points1), tx, ty, vec);
        default:
            return -1;
        }
    case Geometry::Type::TRIANGLE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), tx, ty, vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), tx, ty, vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), tx, ty, vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Circle *>(points1), tx, ty, vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), tx, ty, vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), tx, ty, vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Triangle *>(points0),
                *static_cast<const Geometry::Line *>(points1), tx, ty, vec);
        default:
            return -1;
        }
    case Geometry::Type::CIRCLE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), tx, ty, vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), tx, ty, vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), tx, ty, vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Circle *>(points1), vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), tx, ty, vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), tx, ty, vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Circle *>(points0),
                *static_cast<const Geometry::Line *>(points1), tx, ty, vec);
        default:
            return -1;
        }
    case Geometry::Type::POLYLINE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), tx, ty, vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), tx, ty, vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), tx, ty, vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Circle *>(points1), tx, ty, vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), tx, ty, vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), tx, ty, vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Polyline *>(points0),
                *static_cast<const Geometry::Line *>(points1), tx, ty, vec);
        default:
            return -1;
        }
    case Geometry::Type::BEZIER:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), tx, ty, vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), tx, ty, vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), tx, ty, vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Circle *>(points1), tx, ty, vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), tx, ty, vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), tx, ty, vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Bezier *>(points0),
                *static_cast<const Geometry::Line *>(points1), tx, ty, vec);
        default:
            return -1;
        }
    case Geometry::Type::LINE:
        switch (points0->type())
        {
        case Geometry::Type::POLYGON:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Polygon *>(points1), tx, ty, vec);
        case Geometry::Type::RECTANGLE:
        case Geometry::Type::SQUARE:
        case Geometry::Type::AABBRECT:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Rectangle *>(points1), tx, ty, vec);
        case Geometry::Type::TRIANGLE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Triangle *>(points1), tx, ty, vec);
        case Geometry::Type::CIRCLE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Circle *>(points1), tx, ty, vec);
        case Geometry::Type::POLYLINE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Polyline *>(points1), tx, ty, vec);
        case Geometry::Type::BEZIER:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Bezier *>(points1), tx, ty, vec);
        case Geometry::Type::LINE:
            return Collision::epa(*static_cast<const Geometry::Line *>(points0),
                *static_cast<const Geometry::Line *>(points1), tx, ty, vec);
        default:
            return -1;
        }
    default:
        return -1;
    }
}