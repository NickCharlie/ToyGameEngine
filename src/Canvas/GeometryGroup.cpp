#include "Canvas/GeometryGroup.hpp"

#include <cassert>

using namespace ToyGameEngine::Canvas;

GeometryGroup::GeometryGroup()
{
}

GeometryGroup::~GeometryGroup()
{
    for (size_t i = 0, count = _objects.size(); i < count; ++i)
    {
        delete _objects[i];
    }
}

GeometryGroup::GeometryGroup(const GeometryGroup &group)
{
    _visible = group.visible();

    for (Math::Geometry::GeometryObject *obj : group._objects)
    {
        if (obj)
        {
            _objects.push_back(obj->clone());
        }
    }
}

GeometryGroup::GeometryGroup(const std::initializer_list<Math::Geometry::GeometryObject *> &objs)
{
    for (Math::Geometry::GeometryObject *obj : objs)
    {
        _objects.push_back(obj->clone());
    }
}

GeometryGroup::GeometryGroup(std::vector<Math::Geometry::GeometryObject *>::const_iterator begin, std::vector<Math::Geometry::GeometryObject *>::const_iterator end)
{
    for (auto it = begin; it != end; ++it)
    {
        _objects.push_back((*it)->clone());
    }
}

const bool GeometryGroup::visible() const
{
    return _visible;
}

void GeometryGroup::show()
{
    _visible = true;
}

void GeometryGroup::hide()
{
    _visible = false;
}

GeometryGroup *GeometryGroup::clone() const
{
    GeometryGroup *g = new GeometryGroup();
    for (const Math::Geometry::GeometryObject *geo : _objects)
    {
        g->_objects.push_back(geo->clone());
    }
    return g;
}

void GeometryGroup::clone(GeometryGroup &group)
{
    for (const Math::Geometry::GeometryObject *geo : _objects)
    {
        group._objects.push_back(geo->clone());
    }
}

GeometryGroup &GeometryGroup::operator=(const GeometryGroup &group)
{
    if (this != &group)
    {
        // Math::Geometry::GeometryObject::operator=(group);

        for (size_t i = 0, count = _objects.size(); i < count; ++i)
        {
            delete _objects[i];
        }
        _objects.clear();
        _objects.shrink_to_fit();

        _objects = group._objects;
        _visible = group._visible;
    }
    return *this;
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::iterator GeometryGroup::begin()
{
    return _objects.begin();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::const_iterator GeometryGroup::begin() const
{
    return _objects.begin();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::const_iterator GeometryGroup::cbegin() const
{
    return _objects.cbegin();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::iterator GeometryGroup::end()
{
    return _objects.end();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::const_iterator GeometryGroup::end() const
{
    return _objects.end();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::const_iterator GeometryGroup::cend() const
{
    return _objects.cend();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::reverse_iterator GeometryGroup::rbegin()
{
    return _objects.rbegin();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::const_reverse_iterator GeometryGroup::rbegin() const
{
    return _objects.rbegin();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::const_reverse_iterator GeometryGroup::crbegin() const
{
    return _objects.crbegin();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::reverse_iterator GeometryGroup::rend()
{
    return _objects.rend();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::const_reverse_iterator GeometryGroup::rend() const
{
    return _objects.rend();
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::const_reverse_iterator GeometryGroup::crend() const
{
    return _objects.crend();
}

ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::operator[](const size_t index)
{
    assert(index < _objects.size());
    return _objects[index];
}

const ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::operator[](const size_t index) const
{
    assert(index < _objects.size());
    return _objects[index];
}

void GeometryGroup::clear()
{
    for (size_t i = 0, count = _objects.size(); i < count; ++i)
    {
        delete _objects[i];
    }
    _objects.clear();
    _objects.shrink_to_fit();
}

const size_t GeometryGroup::size() const
{
    return _objects.size();
}

void GeometryGroup::append(Math::Geometry::GeometryObject *object)
{
    _objects.push_back(object);
}

void GeometryGroup::append(GeometryGroup &group, const bool merge)
{
    if (merge)
    {
        _objects.insert(_objects.end(), group._objects.begin(), group._objects.end());
        group._objects.clear();
    }
    else
    {
        for (Math::Geometry::GeometryObject *geo : group)
        {
            _objects.emplace_back(geo->clone());
        }
    }
}

void GeometryGroup::insert(const size_t index, Math::Geometry::GeometryObject *object)
{
    _objects.insert(_objects.begin() + index, object);
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::iterator GeometryGroup::remove(const size_t index)
{
    assert(index < _objects.size());
    delete _objects[index];
    return _objects.erase(_objects.begin() + index);
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::iterator GeometryGroup::remove(const std::vector<Math::Geometry::GeometryObject *>::iterator &it)
{
    delete *it;
    return _objects.erase(it);
}

std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::iterator GeometryGroup::remove(const std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::reverse_iterator &it)
{

    std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::iterator b = _objects.begin();
    while (*b != *it)
    {
        ++b;
    }
    delete *b;
    return _objects.erase(b);
}

ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::pop(const size_t index)
{
    assert(index < _objects.size());
    ToyGameEngine::Math::Geometry::GeometryObject *container = _objects[index];
    _objects.erase(_objects.begin() + index);
    return container;
}

ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::pop(const std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::iterator &it)
{
    ToyGameEngine::Math::Geometry::GeometryObject *container = *it;
    _objects.erase(it);
    return container;
}

ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::pop(const std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::reverse_iterator &it)
{
    std::vector<ToyGameEngine::Math::Geometry::GeometryObject *>::iterator b = _objects.begin();
    while (*b != *it)
    {
        ++b;
    }
    ToyGameEngine::Math::Geometry::GeometryObject *container = *b;
    _objects.erase(b);
    return container;
}

ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::pop_front()
{
    assert(!_objects.empty());
    ToyGameEngine::Math::Geometry::GeometryObject *container = _objects.front();
    _objects.erase(_objects.begin());
    return container;
}

ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::pop_back()
{
    assert(!_objects.empty());
    ToyGameEngine::Math::Geometry::GeometryObject *container = _objects.back();
    _objects.pop_back();
    return container;
}

const bool GeometryGroup::empty() const
{
    return _objects.empty();
}

ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::front()
{
    assert(!_objects.empty());
    return _objects.front();
}

const ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::front() const
{
    assert(!_objects.empty());
    return _objects.front();
}

ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::back()
{
    assert(!_objects.empty());
    return _objects.back();
}

const ToyGameEngine::Math::Geometry::GeometryObject *GeometryGroup::back() const
{
    assert(!_objects.empty());
    return _objects.back();
}

void GeometryGroup::remove_front()
{
    if (!_objects.empty())
    {
        delete _objects.front();
        _objects.erase(_objects.begin());
    }
}

void GeometryGroup::remove_back()
{
    if (!_objects.empty())
    {
        delete _objects.back();
        _objects.pop_back();
    }
}
