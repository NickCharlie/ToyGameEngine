#include "Spirit/Spirit.hpp"
#include "Math/Geometry/Algorithm.hpp"
#include "Resource/ResManager.hpp"

#include <iostream>

using namespace ToyGameEngine::Spirits;
using namespace ToyGameEngine::Math;


Spirit::Spirit(const Math::Geometry::Vector &position)
    : Geometry::Point(position)
{
}

Spirit::Spirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity)
    : Geometry::Point(position), _velocity(velocity)
{
}

Spirit::Spirit(const Math::Geometry::Vector &position, const double direction)
    : Geometry::Point(position), _direction(Math::Geometry::degree_to_rad(direction))
{
}

Spirit::Spirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const double direction)
    : Geometry::Point(position), _velocity(velocity), _direction(Math::Geometry::degree_to_rad(direction))
{
}

Spirit::Spirit(const double x, const double y)
    : Geometry::Point(x, y)
{
}

Spirit::Spirit(const double x, const double y, const Math::Geometry::Vector &velocity)
    : Geometry::Point(x, y), _velocity(velocity)
{
}

Spirit::Spirit(const double x, const double y, const double direction)
    : Geometry::Point(x, y), _direction(Math::Geometry::degree_to_rad(direction))
{
}

Spirit::Spirit(const double x, const double y, const Math::Geometry::Vector &velocity, const double direction)
    : Geometry::Point(x, y), _velocity(velocity), _direction(Math::Geometry::degree_to_rad(direction))
{
}

void Spirit::set_velocity(const Math::Geometry::Vector &velocity)
{
    this->_velocity = velocity;
}

void Spirit::set_degree_direction(double degree)
{
    this->_direction = Math::Geometry::degree_to_rad(degree);
}

void Spirit::set_rad_direction(double rad)
{
    this->_direction = rad;
}


Geometry::Vector Spirit::velocity() const
{
    return this->_velocity;
}

double Spirit::direction() const
{
    return this->_direction;
}

std::string Spirit::name() const
{
    return this->_name;
}

void Spirit::set_name(std::string name)
{
    this->_name = name;
}

bool Spirit::visible() const
{
    return this->_visible;
}

void Spirit::show()
{
    this->_visible = true;
}

inline void Spirit::hide()
{
    this->_visible = false;
}

Spirit *Spirit::clone() const
{
    return new Spirits::Spirit(*this);
}

void Spirit::update()
{
}

void Spirit::update(Scenes::Event *event)
{
}

void Spirit::update(Scenes::IOEvent *event)
{
}

void Spirit::update(Scenes::KeyEvent *event)
{
}

void Spirit::update(Scenes::MouseEvent *event)
{
}

void Spirit::load_event_queue(std::function<void(Scenes::Event *)> func)
{
    _append_event = func;
}

QPixmap* Spirit::get_pixmap(const std::string& pixmap_name)
{
    return Resource::ResManager::get_instance().get_pixmap_resource(pixmap_name);
}


void Spirit::push_pixmap(std::string map_string, std::string file_path)
{
    this->_pixmaps_strings.push_back(map_string);
    Resource::ResManager::get_instance().load_pixmap_resource(map_string, file_path);
}

void Spirit::push_pixmaps(std::vector<std::string> maps_string, std::vector<std::string> file_path)
{
    for (size_t i = 0; (i < maps_string.size()) && (i < file_path.size()); ++i)
    {
        this->_pixmaps_strings.push_back(maps_string[i]);
        Resource::ResManager::get_instance().load_pixmap_resource(maps_string[i], file_path[i]);
    }
}

void Spirit::add_pixmap(std::string map_string, QPixmap* map)
{
    QPixmap* map_copy = new QPixmap(*map);
    this->_pixmaps_strings.push_back(map_string);
    Resource::ResManager::get_instance().add_pixmap_resource(map_string, map_copy);
}

void Spirit::add_exist_pixmap(std::string map_string)
{
    if (Resource::ResManager::get_instance().get_pixmap_resource(map_string) == nullptr)
    {
        std::cerr << "cant find your map_string" << std::endl;
        return;
    }
    this->_pixmaps_strings.push_back(map_string);
}

void Spirit::add_exist_pixmaps(std::vector<std::string> map_strings)
{
    for (std::string str : map_strings)
    {
        if (Resource::ResManager::get_instance().get_pixmap_resource(str) == nullptr)
        {
            std::cerr << "cant find your map_string : " << str << std::endl;
            continue;
        }
        this->_pixmaps_strings.push_back(str);
    }
}

void Spirit::set_pixmap_state(std::string state)
{
    this->_pixmap_state = state;
    for (size_t i = 0; i < this->_pixmaps_strings.size(); ++i)
    {
        if (_pixmaps_strings[i] == this->_pixmap_state)
        {
            _pixmaps_strings[0].swap(_pixmaps_strings[i]);
            return;
        }
    }
}

std::string Spirit::get_pixmap_state() const
{
    return this->_pixmap_state;
}

std::vector<std::string> Spirit::get_pixmaps_strings() const
{
    return this->_pixmaps_strings;
}