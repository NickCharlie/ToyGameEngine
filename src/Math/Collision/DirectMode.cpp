#include <set>
#include "Math/Collision/DirectMode.hpp"
#include "Math/Collision/Algorithm.hpp"
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/AllGeometryObjects.hpp"


using namespace ToyGameEngine::Math;

Collision::DirectMode::DirectMode()
{

}

Collision::DirectMode::DirectMode(const std::vector<Geometry::GeometryObject *> &objects)
    : _objects(objects)
{

}

Collision::DirectMode::DirectMode(const std::initializer_list<Geometry::GeometryObject *> &objects)
    : _objects(objects.begin(), objects.end())
{

}

Collision::DirectMode::DirectMode(const std::vector<Geometry::GeometryObject *>::const_iterator &begin, const std::vector<Geometry::GeometryObject *>::const_iterator &end)
    : _objects(begin, end)
{

}

void Collision::DirectMode::build(const std::vector<Geometry::GeometryObject *> &objects)
{
    _objects.assign(objects.cbegin(), objects.cend());
}

void Collision::DirectMode::build(const std::vector<Geometry::GeometryObject *>::const_iterator &begin, const std::vector<Geometry::GeometryObject *>::const_iterator &end)
{
    _objects.assign(begin, end);
}

void Collision::DirectMode::build(const std::vector<Geometry::GeometryObject *> &objects, const std::vector<Geometry::AABBRect> &rects)
{
    _objects.assign(objects.cbegin(), objects.cend());
}

void Collision::DirectMode::append(Geometry::GeometryObject *object)
{
    if (std::find(_objects.begin(), _objects.end(), object) == _objects.end())
    {
        _objects.push_back(object);
    }
}

void Collision::DirectMode::remove(Geometry::GeometryObject *object)
{
    std::vector<Geometry::GeometryObject *>::const_iterator it = std::find(_objects.begin(), _objects.end(), object);
    if (it == _objects.end())
    {
        _objects.erase(it);
    }
}

void Collision::DirectMode::update(Geometry::GeometryObject *object)
{

}

void Collision::DirectMode::update()
{

}

bool Collision::DirectMode::has(Geometry::GeometryObject *object) const
{
    return std::find(_objects.begin(), _objects.end(), object) != _objects.end();
}

void Collision::DirectMode::clear()
{
    _objects.clear();
}

bool Collision::DirectMode::select(const Geometry::Point &pos, std::vector<Geometry::GeometryObject *> &objects) const
{
    const size_t size = objects.size();
    for (Geometry::GeometryObject *object : _objects)
    {
        switch (object->type())
        {
        case Geometry::Type::POLYGON:
            if (Geometry::is_inside(pos, *static_cast<Geometry::Polygon *>(object), true))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::RECTANGLE:
            if (Geometry::is_inside(pos, *static_cast<Geometry::Rectangle *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::AABBRECT:
            if (Geometry::is_inside(pos, *static_cast<Geometry::AABBRect *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::SQUARE:
            if (Geometry::is_inside(pos, *static_cast<Geometry::Square *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::POLYLINE:
            if (Geometry::is_inside(pos, *static_cast<Geometry::Polyline *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::BEZIER:
            if (Geometry::is_inside(pos, static_cast<Geometry::Bezier *>(object)->shape()))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::TRIANGLE:
            if (Geometry::is_inside(pos, *static_cast<Geometry::Triangle *>(object), true))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::CIRCLE:
            if (Geometry::is_inside(pos, *static_cast<Geometry::Circle *>(object), true))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::LINE:
            if (Geometry::is_inside(pos, *static_cast<Geometry::Line *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::POINT:
            if (pos == *static_cast<Geometry::Point *>(object))
            {
                objects.push_back(object);
            }
            break;
        default:
            break;
        }
    }
    return objects.size() > size;
}

bool Collision::DirectMode::select(const Geometry::AABBRect &rect, std::vector<Geometry::GeometryObject *> &objects) const
{
    const size_t size = objects.size();
    for (Geometry::GeometryObject *object : _objects)
    {
        switch (object->type())
        {
        case Geometry::Type::POLYGON:
            if (Geometry::is_intersected(rect, *static_cast<Geometry::Polygon *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::POLYLINE:
            if (Geometry::is_intersected(rect, *static_cast<Geometry::Polyline *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::RECTANGLE:
            if (Geometry::is_intersected(rect, *static_cast<Geometry::Rectangle *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::AABBRECT:
            if (Geometry::is_intersected(rect, *static_cast<Geometry::AABBRect *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::SQUARE:
            if (Geometry::is_intersected(rect, *static_cast<Geometry::Square *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::TRIANGLE:
            if (Geometry::is_intersected(rect, *static_cast<Geometry::Triangle *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::BEZIER:
            if (Geometry::is_intersected(rect, static_cast<Geometry::Bezier *>(object)->shape()))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::CIRCLE:
            if (Geometry::is_intersected(rect, *static_cast<Geometry::Circle *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::LINE:
            if (Geometry::is_intersected(rect, *static_cast<Geometry::Line *>(object)))
            {
                objects.push_back(object);
            }
            break;
        case Geometry::Type::POINT:
            if (Geometry::is_inside(*static_cast<Geometry::Point *>(object), rect))
            {
                objects.push_back(object);
            }
            break;
        default:
            break;
        }
    }
    return objects.size() > size;
}

bool Collision::DirectMode::find_collision_objects(const Geometry::GeometryObject *object, std::vector<Geometry::GeometryObject *> &objects, const bool norepeat) const
{
    const size_t size = objects.size();
    for (Geometry::GeometryObject *obj : _objects)
    {
        if (obj != object && Geometry::is_intersected(object, obj))
        {
            objects.push_back(obj);
        }
    }
    return objects.size() > size;
}

bool Collision::DirectMode::find_collision_pairs(std::vector<std::pair<Geometry::GeometryObject *, Geometry::GeometryObject *>> &pairs, const bool norepeat) const
{
    const size_t size = pairs.size();
    for (size_t i = 0, count = _objects.size(); i < count; ++i)
    {
        for (size_t j = i + 1; j < count; ++j)
        {
            if (Geometry::is_intersected(_objects[i], _objects[j]))
            {
                pairs.emplace_back(_objects[i], _objects[j]);
            }
        }
    }
    return pairs.size() > size;
}