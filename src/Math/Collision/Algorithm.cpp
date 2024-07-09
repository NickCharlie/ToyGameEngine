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


bool Collision::gjk(const Geometry::Circle &circle0, const Geometry::Circle &circle1)
{
    return (circle0.x - circle1.x) * (circle0.x - circle1.x) + (circle0.y - circle1.y) + (circle0.y - circle1.y)
        <= (circle0.radius + circle1.radius) * (circle0.radius + circle1.radius);
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
