#include "Spirit/SpiritGroup.hpp"
#include <cassert>

using namespace ToyGameEngine::Spirits;

SpiritGroup::SpiritGroup()
{
}

SpiritGroup::~SpiritGroup()
{
    for (size_t i = 0, count = _objects.size(); i < count; ++i)
    {
        delete _objects[i];
    }
}

SpiritGroup::SpiritGroup(const SpiritGroup &group)
{
    _visible = group.visible();

    for (Spirits::Spirit *obj : group._objects)
    {
        if (obj)
        {
            _objects.push_back(obj->clone());
        }
    }
}

SpiritGroup::SpiritGroup(const std::initializer_list<Spirits::Spirit *> &objs)
{
    for (Spirits::Spirit *obj : objs)
    {
        _objects.push_back(obj->clone());
    }
}

SpiritGroup::SpiritGroup(std::vector<Spirits::Spirit *>::const_iterator begin, std::vector<Spirits::Spirit *>::const_iterator end)
{
    for (auto it = begin; it != end; ++it)
    {
        _objects.push_back((*it)->clone());
    }
}

void SpiritGroup::update()
{
    for (Spirit *sp : _objects)
    {
        sp->update();
    }
}

const bool &SpiritGroup::visible() const
{
    return _visible;
}

void SpiritGroup::show()
{
    _visible = true;
}

void SpiritGroup::hide()
{
    _visible = false;
}

SpiritGroup *SpiritGroup::clone() const
{
    SpiritGroup *g = new SpiritGroup();
    for (const Spirits::Spirit *sp : _objects)
    {
        g->_objects.push_back(sp->clone());
    }
    return g;
}

void SpiritGroup::clone(SpiritGroup &group)
{
    for (const Spirits::Spirit *sp : _objects)
    {
        group._objects.push_back(sp->clone());
    }
}

SpiritGroup &SpiritGroup::operator=(const SpiritGroup &group)
{

    if (this != &group)
    {
        // Spirits::Spirit::operator=(group);

        for (size_t i = 0; i < _objects.size(); ++i)
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

std::vector<ToyGameEngine::Spirits::Spirit *>::iterator SpiritGroup::begin()
{
    return _objects.begin();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::const_iterator SpiritGroup::begin() const
{
    return _objects.begin();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::const_iterator SpiritGroup::cbegin() const
{
    return _objects.cbegin();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::iterator SpiritGroup::end()
{
    return _objects.end();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::const_iterator SpiritGroup::end() const
{
    return _objects.end();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::const_iterator SpiritGroup::cend() const
{
    return _objects.cend();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::reverse_iterator SpiritGroup::rbegin()
{
    return _objects.rbegin();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::const_reverse_iterator SpiritGroup::rbegin() const
{
    return _objects.rbegin();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::const_reverse_iterator SpiritGroup::crbegin() const
{
    return _objects.crbegin();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::reverse_iterator SpiritGroup::rend()
{
    return _objects.rend();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::const_reverse_iterator SpiritGroup::rend() const
{
    return _objects.rend();
}

std::vector<ToyGameEngine::Spirits::Spirit *>::const_reverse_iterator SpiritGroup::crend() const
{
    return _objects.crend();
}

ToyGameEngine::Spirits::Spirit *SpiritGroup::operator[](const size_t index)
{
    assert(index < _objects.size());
    return _objects[index];
}

const ToyGameEngine::Spirits::Spirit *SpiritGroup::operator[](const size_t index) const
{
    assert(index < _objects.size());
    return _objects[index];
}

void SpiritGroup::clear()
{
    for (size_t i = 0, count = _objects.size(); i < count; ++i)
    {
        delete _objects[i];
    }
    _objects.clear();
    _objects.shrink_to_fit();
}

const size_t SpiritGroup::size() const
{
    return _objects.size();
}

void SpiritGroup::append(Spirits::Spirit *object)
{
    _objects.push_back(object);
    object->load_event_queue(_append_event);
}

void SpiritGroup::append(SpiritGroup &group, const bool merge)
{
    if (merge)
    {
        for (Spirits::Spirit *sp : group)
        {
            sp->load_event_queue(_append_event);
        }
        _objects.insert(_objects.end(), group._objects.begin(), group._objects.end());
        group._objects.clear();
    }
    else
    {
        for (Spirits::Spirit *sp : group)
        {
            _objects.emplace_back(sp->clone());
            _objects.back()->load_event_queue(_append_event);
        }
    }
}

void SpiritGroup::insert(const size_t index, Spirits::Spirit *object)
{
    _objects.insert(_objects.begin() + index, object);
    object->load_event_queue(_append_event);
}

std::vector<ToyGameEngine::Spirits::Spirit *>::iterator SpiritGroup::remove(const size_t index)
{
    assert(index < _objects.size());
    delete _objects[index];
    return _objects.erase(_objects.begin() + index);
}

std::vector<ToyGameEngine::Spirits::Spirit *>::iterator SpiritGroup::remove(const std::vector<Spirits::Spirit *>::iterator &it)
{
    delete *it;
    return _objects.erase(it);
}

std::vector<ToyGameEngine::Spirits::Spirit *>::iterator SpiritGroup::remove(const std::vector<ToyGameEngine::Spirits::Spirit *>::reverse_iterator &it)
{

    std::vector<ToyGameEngine::Spirits::Spirit *>::iterator b = _objects.begin();
    while (*b != *it)
    {
        ++b;
    }
    delete *b;
    return _objects.erase(b);
}

ToyGameEngine::Spirits::Spirit *SpiritGroup::pop(const size_t index)
{
    assert(index < _objects.size());
    ToyGameEngine::Spirits::Spirit *container = _objects[index];
    _objects.erase(_objects.begin() + index);
    return container;
}

ToyGameEngine::Spirits::Spirit *SpiritGroup::pop(const std::vector<ToyGameEngine::Spirits::Spirit *>::iterator &it)
{
    ToyGameEngine::Spirits::Spirit *container = *it;
    _objects.erase(it);
    return container;
}

ToyGameEngine::Spirits::Spirit *SpiritGroup::pop(const std::vector<ToyGameEngine::Spirits::Spirit *>::reverse_iterator &it)
{
    std::vector<ToyGameEngine::Spirits::Spirit *>::iterator b = _objects.begin();
    while (*b != *it)
    {
        ++b;
    }
    ToyGameEngine::Spirits::Spirit *container = *b;
    _objects.erase(b);
    return container;
}

ToyGameEngine::Spirits::Spirit *SpiritGroup::pop_front()
{
    assert(!_objects.empty());
    ToyGameEngine::Spirits::Spirit *container = _objects.front();
    _objects.erase(_objects.begin());
    return container;
}

ToyGameEngine::Spirits::Spirit *SpiritGroup::pop_back()
{
    assert(!_objects.empty());
    ToyGameEngine::Spirits::Spirit *container = _objects.back();
    _objects.pop_back();
    return container;
}

const bool SpiritGroup::empty() const
{
    return _objects.empty();
}

ToyGameEngine::Spirits::Spirit *SpiritGroup::front()
{
    assert(!_objects.empty());
    return _objects.front();
}

const ToyGameEngine::Spirits::Spirit *SpiritGroup::front() const
{
    assert(!_objects.empty());
    return _objects.front();
}

ToyGameEngine::Spirits::Spirit *SpiritGroup::back()
{
    assert(!_objects.empty());
    return _objects.back();
}

const ToyGameEngine::Spirits::Spirit *SpiritGroup::back() const
{
    assert(!_objects.empty());
    return _objects.back();
}

void SpiritGroup::remove_front()
{
    if (!_objects.empty())
    {
        delete _objects.front();
        _objects.erase(_objects.begin());
    }
}

void SpiritGroup::remove_back()
{
    if (!_objects.empty())
    {
        delete _objects.back();
        _objects.pop_back();
    }
}

void SpiritGroup::update(Scenes::Event *event)
{
    if (this->ignore_all_events)
    {
        return;
    }

    switch (event->type())
    {
    case Scenes::EventType::DESTRUCTION_EVENT:
        return update(static_cast<Scenes::DestructionEvent *>(event));
    case Scenes::EventType::KEY_EVENT:
        return update(static_cast<Scenes::KeyEvent *>(event));
    case Scenes::EventType::MOUSE_EVENT:
        return update(static_cast<Scenes::MouseEvent *>(event));
    default:
        for (Spirit *sp : _objects)
        {
            if (!sp->ignore_all_events)
            {
                sp->update(event);
                if (!event->active)
                {
                    break;
                }
            }
        }
        break;
    }
}

void SpiritGroup::update(Scenes::IOEvent *event)
{
    if (this->ignore_all_events)
    {
        return;
    }

    if (dynamic_cast<Scenes::KeyEvent *>(event) != nullptr)
    {
        update(static_cast<Scenes::KeyEvent *>(event));
    }
    else
    {
        update(static_cast<Scenes::MouseEvent *>(event));
    }
}

void SpiritGroup::update(Scenes::KeyEvent *event)
{
    if (!this->key_event_update)
    {
        return;
    }
    for (Spirit *sp : _objects)
    {
        if (!sp->ignore_all_events)
        {
            sp->update(event);
            if (!event->active)
            {
                break;
            }
        }
    }
}

void SpiritGroup::update(Scenes::MouseEvent *event)
{
    if (!this->mouse_event_update)
    {
        return;
    }
    for (Spirit *sp : _objects)
    {
        if (!sp->ignore_all_events)
        {
            sp->update(event);
            if (!event->active)
            {
                break;
            }
        }
    }
}

void SpiritGroup::update(Scenes::DestructionEvent *event)
{
    for (size_t i = 0, count = _objects.size(); i < count; ++i)
    {
        if (_objects[i] == event->spirit)
        {
            delete _objects[i];
            _objects.erase(_objects.begin() + i);
            event->active = false;
            break;
        }
    }
}

void SpiritGroup::load_event_queue(std::function<void(Scenes::Event *)> func)
{
    _append_event = func;
}
