#include <set>
#include "Math/Collision/GridMap.hpp"
#include "Math/Collision/Algorithm.hpp"
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/AllGeometryObjects.hpp"


using namespace ToyGameEngine::Math;

Collision::GridNode::GridNode()
{

}

Collision::GridNode::GridNode(const Geometry::AABBRect &rect)
    : _rect(rect)
{
  
}

Collision::GridNode::GridNode(const double left, const double top, const double right, const double bottom)
    : _rect(left, top, right, bottom)
{

}

void Collision::GridNode::set_rect(const Geometry::AABBRect &rect)
{
    _rect = rect;
}

const Geometry::AABBRect &Collision::GridNode::rect() const
{
    return _rect;
}

bool Collision::GridNode::append(Geometry::GeometryObject *object)
{
    if (std::find(_objects.begin(), _objects.end(), object) == _objects.end())
    {
        _objects.push_back(object);
        return true;
    }
    else
    {
        return false;
    }
}

bool Collision::GridNode::remove(Geometry::GeometryObject *object)
{   
    std::vector<Geometry::GeometryObject *>::iterator it = std::find(_objects.begin(), _objects.end(), object);
    if (it == _objects.end())
    {
        return false;
    }
    else
    {
        _objects.erase(it);
        return true;
    }
}

bool Collision::GridNode::has(Geometry::GeometryObject *object) const
{
    return std::find(_objects.begin(), _objects.end(), object) != _objects.end(); 
}

void Collision::GridNode::clear()
{
    _objects.clear();
}

bool Collision::GridNode::select(const Geometry::Point &pos, std::vector<Geometry::GeometryObject *> &objects) const
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

bool Collision::GridNode::select(const Geometry::AABBRect &rect, std::vector<Geometry::GeometryObject *> &objects) const
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

bool Collision::GridNode::find_collision_objects(const Geometry::GeometryObject *object, std::vector<Geometry::GeometryObject *> &objects) const
{
    const size_t size = objects.size();
    for (Geometry::GeometryObject *obj : _objects)
    {
        if (obj != object && Collision::gjk(obj, object))
        {
            objects.push_back(obj);
        }
    }
    return objects.size() > size;
}

bool Collision::GridNode::find_collision_pairs(std::vector<std::pair<Geometry::GeometryObject *, Geometry::GeometryObject *>> &pairs) const
{
    const size_t size = pairs.size();
    for (size_t i = 0, count = _objects.size(); i < count; ++i)
    {
        for (size_t j = i + 1; j < count; ++j)
        {
            if (Collision::gjk(_objects[i], _objects[j]))
            {
                pairs.emplace_back(_objects[i], _objects[j]);
            }
        }
    }
    return pairs.size() > size;
}


Collision::GridMap::GridMap()
{

}

Collision::GridMap::GridMap(const std::vector<Geometry::GeometryObject *> &objects)
    : _objects(objects)
{
    build(_objects);
}

Collision::GridMap::GridMap(const std::initializer_list<Geometry::GeometryObject *> &objects)
    : _objects(objects.begin(), objects.end())
{
    build(_objects);
}

Collision::GridMap::GridMap(const std::vector<Geometry::GeometryObject *>::const_iterator &begin, 
    const std::vector<Geometry::GeometryObject *>::const_iterator &end)
    : _objects(begin, end)
{
    build(_objects);
}

void Collision::GridMap::build(const std::vector<Geometry::GeometryObject *>::const_iterator &begin, 
    const std::vector<Geometry::GeometryObject *>::const_iterator &end)
{
    if (begin == end)
    {
        _left = _bottom = 0;
        _right = _top = 100;
        _rects.clear();
        _objects.clear();
        _grids.clear();
        _grids.emplace_back(_left, _top, _right, _bottom);
        return;
    }

    _left = _bottom = DBL_MAX;
    _right = _top = -DBL_MAX;
    _rects.clear();
    _objects.clear();
    _grids.clear();
    for (std::vector<Geometry::GeometryObject *>::const_iterator it = begin; it != end; ++it)
    {
        _objects.push_back(*it);
        _rects.emplace_back((*it)->bounding_rect());
        _left = std::min(_rects.back().left(), _left);
        _top = std::max(_rects.back().top(), _top);
        _right = std::max(_rects.back().right(), _right);
        _bottom = std::min(_rects.back().bottom(), _bottom);
    }

    if (_objects.size() > 40 || (_right - _left) > 800)
    {
        double x_step = (_right - _left) / 8, y_step = (_top - _bottom) / 4;
        for (size_t i = 0; i < 8; ++i)
        {
            for (size_t j = 0; j < 4; ++j)
            {
                _grids.emplace_back(_left + x_step * i, _top - y_step * j,
                    _left + x_step * i + x_step, _top - y_step * j - y_step);

                for (size_t k = 0, count = _rects.size(); k < count; ++k)
                {
                    if (Geometry::is_intersected(_grids.back().rect(), _rects[k]))
                    {
                        _grids.back().append(_objects[k]);
                    }
                }
            }
        }
    }
    else
    {
        _grids.emplace_back(_left, _top, _right, _bottom);
        for (Geometry::GeometryObject *object : _objects)
        {
            _grids.back().append(object);
        }
    }
}

void Collision::GridMap::build(const std::vector<Geometry::GeometryObject *> &objects)
{
    if (objects.empty())
    {
        _left = _bottom = 0;
        _right = _top = 100;
        _rects.clear();
        _objects.clear();
        _grids.clear();
        _grids.emplace_back(_left, _top, _right, _bottom);
        return;
    }

    _left = _bottom = DBL_MAX;
    _right = _top = -DBL_MAX;
    _rects.clear();
    _grids.clear();
    for (Geometry::GeometryObject *object : objects)
    {
        _rects.emplace_back(object->bounding_rect());
        _left = std::min(_rects.back().left(), _left);
        _top = std::max(_rects.back().top(), _top);
        _right = std::max(_rects.back().right(), _right);
        _bottom = std::min(_rects.back().bottom(), _bottom);
    }
    if (&objects != &_objects)
    {
        _objects.assign(objects.begin(), objects.end());
    }

    if (_objects.size() > 40 || (_right - _left) > 800)
    {
        double x_step = (_right - _left) / 8, y_step = (_top - _bottom) / 4;
        for (size_t i = 0; i < 8; ++i)
        {
            for (size_t j = 0; j < 4; ++j)
            {
                _grids.emplace_back(_left + x_step * i, _top - y_step * j,
                    _left + x_step * i + x_step, _top - y_step * j - y_step);

                for (size_t k = 0, count = _rects.size(); k < count; ++k)
                {
                    if (Geometry::is_intersected(_grids.back().rect(), _rects[k]))
                    {
                        _grids.back().append(objects[k]);
                    }
                }
            }
        }
    }
    else
    {
        _grids.emplace_back(_left, _top, _right, _bottom);
        for (Geometry::GeometryObject *object : _objects)
        {
            _grids.back().append(object);
        }
    }
}

void Collision::GridMap::build(const std::vector<Geometry::GeometryObject *> &objects, const std::vector<Geometry::AABBRect> &rects)
{
    if (objects.empty())
    {
        _left = _bottom = 0;
        _right = _top = 100;
        _rects.clear();
        _objects.clear();
        _grids.clear();
        _grids.emplace_back(_left, _top, _right, _bottom);
        return;
    }

    _left = _bottom = DBL_MAX;
    _right = _top = -DBL_MAX;
    _grids.clear();
    for (const Geometry::AABBRect &rect : rects)
    {
        _left = std::min(rect.left(), _left);
        _top = std::max(rect.top(), _top);
        _right = std::max(rect.right(), _right);
        _bottom = std::min(rect.bottom(), _bottom);
    }
    if (&objects != &_objects)
    {
        _objects.assign(objects.begin(), objects.end());
        _rects.assign(rects.begin(), rects.end());
    }

    if (objects.size() > 40 || (_right - _left) > 800)
    {
        double x_step = (_right - _left) / 8, y_step = (_top - _bottom) / 4;
        for (size_t i = 0; i < 8; ++i)
        {
            for (size_t j = 0; j < 4; ++j)
            {
                _grids.emplace_back(_left + x_step * i, _top - y_step * j,
                    _left + x_step * i + x_step, _top - y_step * j - y_step);

                for (size_t k = 0, count = rects.size(); k < count; ++k)
                {
                    if (Geometry::is_intersected(_grids.back().rect(), rects[k]))
                    {
                        _grids.back().append(objects[k]);
                    }
                }
            }
        }
    }
    else
    {
        _grids.emplace_back(_left, _top, _right, _bottom);
        for (Geometry::GeometryObject *object : objects)
        {
            _grids.back().append(object);
        }
    }
}

void Collision::GridMap::append(Geometry::GeometryObject *object)
{
    if (std::find(_objects.begin(), _objects.end(), object) != _objects.end())
    {
        return;
    }

    _objects.push_back(object);
    _rects.emplace_back(object->bounding_rect());
    if (_rects.back().left() >= _left && _rects.back().right() <= _right
        && _rects.back().top() <= _top && _rects.back().bottom() >= _bottom)
    {
        for (GridNode &grid : _grids)
        {
            if (Geometry::is_intersected(grid.rect(), _rects.back()))
            {
                grid.append(object);
            }
        }
    }
    else
    {
        _grids.clear();
        _left = std::min(_left, _rects.back().left());
        _top = std::max(_top, _rects.back().top());
        _right = std::max(_right, _rects.back().right());
        _bottom = std::min(_bottom, _rects.back().bottom());

        if (_objects.size() > 40 || (_right - _left) > 800)
        {
            double x_step = (_right - _left) / 8, y_step = (_top - _bottom) / 4;
            for (size_t i = 0; i < 8; ++i)
            {
                for (size_t j = 0; j < 4; ++j)
                {
                    _grids.emplace_back(_left + x_step * i, _top - y_step * j,
                        _left + x_step * i + x_step, _top - y_step * j - y_step);

                    for (size_t k = 0, count = _rects.size(); k < count; ++k)
                    {
                        if (Geometry::is_intersected(_grids.back().rect(), _rects[k]))
                        {
                            _grids.back().append(_objects[k]);
                        }
                    }
                }
            }
        }
        else
        {
            _grids.emplace_back(_left, _top, _right, _bottom);
            for (Geometry::GeometryObject *object : _objects)
            {
                _grids.back().append(object);
            }
        }
    }
}

void Collision::GridMap::remove(Geometry::GeometryObject *object)
{
    std::vector<Geometry::GeometryObject *>::iterator it = std::find(_objects.begin(), _objects.end(), object);
    if (it == _objects.end())
    {
        return;
    }

    for (GridNode &grid : _grids)
    {
        grid.remove(object);
    }
    _rects.erase(_rects.begin() + std::distance(_objects.begin(), it));
    _objects.erase(it);
}

void Collision::GridMap::update(Geometry::GeometryObject *object)
{
    std::vector<Geometry::GeometryObject *>::iterator it = std::find(_objects.begin(), _objects.end(), object);
    if (it == _objects.end())
    {
        return;
    }

    const size_t index = std::distance(_objects.begin(), it);
    _rects[index] = object->bounding_rect();
    if (_rects[index].left() >= _left && _rects[index].right() <= _right
        && _rects[index].top() <= _top && _rects[index].bottom() >= _bottom)
    {
        for (GridNode &grid : _grids)
        {
            if (Geometry::is_intersected(grid.rect(), _rects[index]))
            {
                grid.append(object);
            }
            else
            {
                grid.remove(object);
            }
        }
    }
    else
    {
        _grids.clear();
        build(_objects, _rects);
    }
}

void Collision::GridMap::update()
{
    _grids.clear();
    build(_objects, _rects);
}

bool Collision::GridMap::has(Geometry::GeometryObject *object) const
{
    return std::find(_objects.begin(), _objects.end(), object) != _objects.end();
}

void Collision::GridMap::clear()
{
    _objects.clear();
    _rects.clear();
    _grids.clear();
}

bool Collision::GridMap::select(const Geometry::Point &pos, std::vector<Geometry::GeometryObject *> &objects) const
{
    if (pos.x >= _left && pos.x <= _right && pos.y >= _bottom && pos.y <= _top)
    {
        for (const GridNode &grid : _grids)
        {
            if (Geometry::is_inside(pos, grid.rect()))
            {
                return grid.select(pos, objects);
            }
        }
    }
    return false;
}

bool Collision::GridMap::select(const Geometry::AABBRect &rect, std::vector<Geometry::GeometryObject *> &objects) const
{
    if (rect.right() < _left || rect.left() > _right || rect.bottom() > _top || rect.top() < _bottom)
    {
        return false;
    }

    const size_t size = objects.size();
    for (const GridNode &grid : _grids)
    {
        if (Geometry::is_intersected(rect, grid.rect()))
        {
            grid.select(rect, objects);
        }
    }
    std::set<Geometry::GeometryObject *> temp(objects.begin(), objects.end());
    objects.assign(temp.begin(), temp.end());
    return objects.size() > size;
}

bool Collision::GridMap::find_collision_objects(const Geometry::GeometryObject *object, std::vector<Geometry::GeometryObject *> &objects, const bool norepeat) const
{
    if (object == nullptr)
    {
        return false;
    }

    const size_t size = objects.size();
    const Geometry::AABBRect rect(object->bounding_rect());
    for (const GridNode &grid : _grids)
    {
        if (Geometry::is_intersected(rect, grid.rect()))
        {
            grid.find_collision_objects(object, objects);
        }
    }

    if (norepeat)
    {
        std::set<Geometry::GeometryObject *> temp(objects.begin(), objects.end());
        objects.assign(temp.begin(), temp.end());
    }
    return objects.size() > size;
}

bool Collision::GridMap::find_collision_pairs(std::vector<std::pair<Geometry::GeometryObject *, Geometry::GeometryObject *>> &pairs, const bool norepeat) const
{
    const size_t size = pairs.size();
    for (const GridNode &grid : _grids)
    {
        grid.find_collision_pairs(pairs);
    }

    if (norepeat)
    {
        for (size_t i = 0, count = pairs.size(); i < count; ++i)
        {
            for (size_t j = count - 1; j > i; --j)
            {
                if ((pairs[i].first == pairs[j].first && pairs[i].second == pairs[j].second)
                    || (pairs[i].first == pairs[j].second && pairs[i].second == pairs[j].first))
                {
                    pairs.erase(pairs.begin() + j);
                    --count;
                }
            }
        }
    }

    return pairs.size() > size;
}