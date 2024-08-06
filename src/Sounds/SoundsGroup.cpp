#include "Sounds/SoundsGroup.hpp"

using namespace ToyGameEngine::Sounds;

SoundGroup::SoundGroup()
{

}

SoundGroup::SoundGroup(const SoundGroup &group)
{
    for (Sound* _obj :  group._objects)
    {
        if (_obj)
        {
            _objects.push_back(_obj->clone());
        }
    }
}

SoundGroup::SoundGroup(const std::initializer_list<Sounds::Sound *> &objs)
{
    for (Sound* _obj :  objs)
    {
        if (_obj)
        {
            _objects.push_back(_obj->clone());
        }
    }
}

SoundGroup::SoundGroup(std::vector<Sounds::Sound *>::const_iterator begin, std::vector<Sounds::Sound *>::const_iterator end)
{
    for (auto it = begin; it != end; ++it)
    {
        if (*it)
        {
            _objects.push_back((*it)->clone());
        }
    }
}

SoundGroup::~SoundGroup()
{
    for (size_t i = 0, count = _objects.size(); i < count; ++i)
    {
        delete _objects[i];
    }
}


SoundGroup* SoundGroup::clone() const
{
    SoundGroup* g = new SoundGroup();

    for (const Sound* _obj :  _objects)
    {
       g->_objects.push_back(_obj->clone());
    }
    return g;
}

void SoundGroup::clone(SoundGroup &group)
{
    for (const Sound* _obj :  _objects)
    {
       group._objects.push_back(_obj->clone());
    }    
}

SoundGroup& SoundGroup::operator=(const SoundGroup &group)
{
    if (this != &group)
    {
        for (size_t i = 0; i < _objects.size(); ++i)
        {
            delete _objects[i];
        }
        _objects.clear();
        _objects.shrink_to_fit();

        _objects = group._objects;
    }
    return *this;    
}

std::vector<Sound *>::iterator SoundGroup::begin()
{
    return _objects.begin();    
}

std::vector<Sound *>::const_iterator SoundGroup::begin() const
{
    return _objects.begin();
}

std::vector<Sound *>::const_iterator SoundGroup::cbegin() const
{
    return _objects.cbegin();
}

std::vector<Sound *>::iterator SoundGroup::end()
{
    return _objects.end();
}

std::vector<Sound *>::const_iterator SoundGroup::end() const
{
    return _objects.end();
}

std::vector<Sound *>::const_iterator SoundGroup::cend() const
{
    return _objects.cend();
}

std::vector<Sound *>::reverse_iterator SoundGroup::rbegin()
{
    return _objects.rbegin();
}

std::vector<Sound *>::const_reverse_iterator SoundGroup::rbegin() const
{
    return _objects.rbegin();
}

std::vector<Sound *>::const_reverse_iterator SoundGroup::crbegin() const
{
    return _objects.crbegin();
}

std::vector<Sound *>::reverse_iterator SoundGroup::rend()
{
    return _objects.rend();
}

std::vector<Sound *>::const_reverse_iterator SoundGroup::rend() const
{
    return _objects.rend();
}

std::vector<Sound *>::const_reverse_iterator SoundGroup::crend() const
{
    return _objects.crend();
}

Sound* SoundGroup::operator[](int index)
{
    assert(index < _objects.size());
    return _objects[index];
}

const Sound* SoundGroup::operator[](int index) const
{
    assert(index < _objects.size());
    return _objects[index];    
}

void SoundGroup::clear()
{
    for (size_t i = 0; i < _objects.size(); i++)
    {
        delete _objects[i];
    }
    _objects.clear();
    _objects.shrink_to_fit();    
}

const size_t SoundGroup::size() const
{
    return _objects.size();    
}

void SoundGroup::append(SoundGroup *container)
{
    //TODO : Nothing to do    
}

void SoundGroup::append(Sounds::Sound *object)
{
    _objects.push_back(object);    
}

void SoundGroup::append(SoundGroup &group, const bool merge)
{
    if(merge)
    {
        //TODO : load_event_queue
        /*for (BackGroundGroup::BackGroundGroup *bgg : group)
        {
            bgg->load_event_queue(_append_event);
        }*/
        _objects.insert(_objects.end(), group._objects.begin(), group._objects.end());
        group._objects.clear();
    }
    else
    {
       for (Sound* _obj :  group._objects)
       {
           _objects.emplace_back(_obj->clone());
           //TODO : load_event_queue
           /*
           *_objects.back()->load_event_queue();
           */
       }
    }    
}

void SoundGroup::insert(const size_t index, Sounds::Sound *object)
{
    _objects.insert(_objects.begin() + index , object);    
}

std::vector<Sound *>::iterator SoundGroup::remove(const size_t index)
{
    assert(index < _objects.size());
    delete _objects[index];
    return _objects.erase(_objects.begin() + index);    
}

std::vector<Sound *>::iterator SoundGroup::remove(const std::vector<Sounds::Sound *>::iterator &it)
{
    delete *it;
    return _objects.erase(it);    
}

std::vector<Sound *>::iterator SoundGroup::remove(const std::vector<Sounds::Sound *>::reverse_iterator &it)
{
    std::vector<Sound *>::iterator b = _objects.begin();
    while (*b != *it)
    {
        ++b;
    }
    delete *b;
    return _objects.erase(b);    
}

Sound* SoundGroup::pop(const size_t index)
{
    assert(index < _objects.size());
    Sound* obj = _objects[index];
    _objects.erase(_objects.begin() + index);
    return obj;    
}

Sound* SoundGroup::pop(const std::vector<Sounds::Sound *>::iterator &it)
{
    Sound *container = *it;
    _objects.erase(it);
    return container;    
}
Sound* SoundGroup::pop(const std::vector<Sounds::Sound *>::reverse_iterator &it)
{
    std::vector<Sound *>::iterator b = _objects.begin();
    while (*b != *it)
    {
        ++b;
    }
    Sound *container = *b;
    _objects.erase(b);
    return container;    
}

Sound* SoundGroup::pop_front()
{
    assert(!_objects.empty());
    Sound *container = _objects.front();
    _objects.erase(_objects.begin());
    return container;    
}

Sound* SoundGroup::pop_back()
{
    assert(!_objects.empty());
    Sound *container = _objects.back();
    _objects.pop_back();
    return container;    
}

const bool SoundGroup::empty() const
{
    return _objects.empty();
}

Sound* SoundGroup::front()
{
    assert(!_objects.empty());
    return _objects.front();
}

const Sound* SoundGroup::front() const
{
    assert(!_objects.empty());
    return _objects.front();   
}

Sound* SoundGroup::back()
{
    assert(!_objects.empty());
    return _objects.back();    
}

const Sound* SoundGroup::back() const
{
    assert(!_objects.empty());
    return _objects.back();    
}

void SoundGroup::remove_front()
{
    if (!_objects.empty())
    {
        delete _objects.front();
        _objects.erase(_objects.begin());
    }    
}

void SoundGroup::remove_back()
{
    if (!_objects.empty())
    {
        delete _objects.back();
        _objects.pop_back();
    }    
}
