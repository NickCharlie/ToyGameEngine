#include "BackGround/BackGroundGroup.hpp"
#include <cassert>


using namespace ToyGameEngine::BackGrounds;

BackGroundGroup::BackGroundGroup()
{
}

BackGroundGroup::BackGroundGroup(const BackGroundGroup &group)
{
    _visible = group._visible;
    for (BackGround::BackGround* _obj :  group._objects)
    {
        if (_obj)
        {
            _objects.push_back(_obj->clone());
        }
    }
    
}

BackGroundGroup::BackGroundGroup(const std::initializer_list<BackGround::BackGround *> &objs)
{
    for (BackGround::BackGround* _obj :  objs)
    {
        if (_obj)
        {
            _objects.push_back(_obj->clone());
        }
    }
}

BackGroundGroup::BackGroundGroup(std::vector<BackGround::BackGround *>::const_iterator begin, std::vector<BackGround::BackGround *>::const_iterator end)
{
    for (auto it = begin; it != end; ++it)
    {
        if (*it)
        {
            _objects.push_back((*it)->clone());
        }
    }

}

BackGroundGroup::~BackGroundGroup()
{
    for (size_t i = 0; i < _objects.size; i++)
    {
        delete _objects[i];
    }
    
}

const bool &BackGroundGroup::visible() const
{
    return _visible;
}

void BackGroundGroup::show()
{
    _visible = true;
}

void BackGroundGroup::hide()
{
    _visible = false;
}

BackGroundGroup *BackGroundGroup::clone() const
{
    BackGroundGroup* g = new BackGroundGroup();

    for (const BackGround::BackGround* _obj :  _objects)
    {
       g->_objects.push_back(_obj->clone());
    }
}

void BackGroundGroup::clone(BackGroundGroup &group)
{
    for (const BackGround::BackGround* _obj :  _objects)
    {
       group._objects.push_back(_obj->clone());
    }
}

BackGroundGroup &BackGroundGroup::operator=(const BackGroundGroup &group)
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
        _visible = group._visible;
    }
    return *this;
}

std::vector<BackGround::BackGround *>::iterator BackGroundGroup::begin()
{
    return _objects.begin();
}

std::vector<BackGround::BackGround *>::const_iterator BackGroundGroup::begin() const
{
    return _objects.begin();
}

std::vector<BackGround::BackGround *>::const_iterator BackGroundGroup::cbegin() const
{
    return _objects.cbegin();
}

std::vector<BackGround::BackGround *>::iterator BackGroundGroup::end()
{
    return _objects.end();
}

std::vector<BackGround::BackGround *>::const_iterator BackGroundGroup::end() const
{
    return _objects.end();
}

std::vector<BackGround::BackGround *>::const_iterator BackGroundGroup::cend() const
{
    return _objects.cend();
}

std::vector<BackGround::BackGround *>::reverse_iterator BackGroundGroup::rbegin()
{
    return _objects.rbegin();
}

std::vector<BackGround::BackGround *>::const_reverse_iterator BackGroundGroup::rbegin() const
{
    return _objects.rbegin();
}

std::vector<BackGround::BackGround *>::const_reverse_iterator BackGroundGroup::crbegin() const
{
    return _objects.crbegin();
}

std::vector<BackGround::BackGround *>::reverse_iterator BackGroundGroup::rend()
{
    return _objects.rend();
}

std::vector<BackGround::BackGround *>::const_reverse_iterator BackGroundGroup::rend() const
{
    return _objects.rend();
}

std::vector<BackGround::BackGround *>::const_reverse_iterator BackGroundGroup::crend() const
{
    return _objects.crend();
}

BackGround::BackGround *BackGroundGroup::operator[](int index)
{
    assert(index < _objects.size());
    return _objects[index];
}

const BackGround::BackGround *BackGroundGroup::operator[](int index) const
{
    assert(index < _objects.size());
    return _objects[index];
}

void BackGroundGroup::clear()
{
    for (size_t i = 0; i < _objects.size(); i++)
    {
        delete _objects[i];
    }
    _objects.clear();
    _objects.shrink_to_fit();
}

const size_t BackGroundGroup::size() const
{
    return _objects.size();
}

void BackGroundGroup::append(BackGroundGroup *container)
{
    //TODO : Nothing to do
}

void BackGroundGroup::append(BackGround::BackGround *object)
{
    _objects.push_back(object);
    //TODO : object->load_event_queue();
}

void BackGroundGroup::append(BackGroundGroup &group, const bool merge)
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
       for (BackGroundGroup::BackGroundGroup* _obj :  group._objects)
       {
           _objects.emplace_back(_obj->clone());
           //TODO : load_event_queue
           /*
           *_objects.back()->load_event_queue();
           */
       }
    }
}

void BackGroundGroup::insert(const size_t index, BackGround::BackGround *object)
{
    _objects.insert(_objects.begin() + index , object);
    //TODO : object->load_event_queue();
}

std::vector<BackGround::BackGround *>::iterator BackGroundGroup::remove(const size_t index)
{
    assert(index < _objects.size());
    delete _objects[index];
    return _objects.erase(_objects.begin() + index);
}

std::vector<BackGround::BackGround *>::iterator BackGroundGroup::remove(const std::vector<BackGround::BackGround *>::iterator &it)
{
    delete *it;
    return _objects.erase(it);
}

std::vector<BackGround::BackGround *>::iterator BackGroundGroup::remove(const std::vector<BackGround::BackGround *>::reverse_iterator &it)
{
    std::vector<BackGround::BackGround *>::iterator b = it.begin();
    while (*b != *it)
    {
        ++b;
    }
    delete *b;
    return _objects.erase(b);
}

BackGround::BackGround *BackGroundGroup::pop(const size_t index)
{
    assert(index < _objects.size());
    BackGround::BackGround* obj = _objects[index];
    _objects.erase(_objects.begin() + index);
    return obj;
}

BackGround::BackGround *BackGroundGroup::pop(const std::vector<BackGround::BackGround *>::iterator &it)
{
    ToyGameEngine::BackGround::BackGround *container = *it;
    _objects.erase(it);
    return container;
}

BackGround::BackGround *ToyGameEngine::BackGrounds::BackGroundGroup::pop(const std::vector<BackGround::BackGround *>::reverse_iterator &it)
{
    std::vector<ToyGameEngine::BackGround::BackGround *>::iterator b = _objects.begin();
    while (*b != *it)
    {
        ++b;
    }
    BackGround::BackGround *container = *b;
    _objects.erase(b);
    return container;
}

BackGround::BackGround *ToyGameEngine::BackGrounds::BackGroundGroup::pop_front()
{
    assert(!_objects.empty());
    BackGround::BackGround *container = _objects.front();
    _objects.erase(_objects.begin());
    return container;
}

BackGround::BackGround *ToyGameEngine::BackGrounds::BackGroundGroup::pop_back()
{
    assert(!_objects.empty());
    BackGround::BackGround *container = _objects.back();
    _objects.pop_back();
    return container;
}

const bool ToyGameEngine::BackGrounds::BackGroundGroup::empty() const
{
    return _objects.empty();
}

BackGround::BackGround *ToyGameEngine::BackGrounds::BackGroundGroup::front()
{
    assert(!_objects.empty());
    return _objects.front();
}

const BackGround::BackGround *ToyGameEngine::BackGrounds::BackGroundGroup::front() const
{
    assert(!_objects.empty());
    return _objects.front();
}

BackGround::BackGround *ToyGameEngine::BackGrounds::BackGroundGroup::back()
{
    assert(!_objects.empty());
    return _objects.back();
}

const BackGround::BackGround *ToyGameEngine::BackGrounds::BackGroundGroup::back() const
{
    assert(!_objects.empty());
    return _objects.back();
}

void ToyGameEngine::BackGrounds::BackGroundGroup::remove_front()
{
    if (!_objects.empty())
    {
        delete _objects.front();
        _objects.erase(_objects.begin());
    }
}

void ToyGameEngine::BackGrounds::BackGroundGroup::remove_back()
{
    if (!_objects.empty())
    {
        delete _objects.back();
        _objects.pop_back();
    }
}
