#include "Spirit/Spirit.hpp"
#include "Math/Geometry/Algorithm.hpp"

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