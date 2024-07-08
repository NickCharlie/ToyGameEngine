#include "Spirit/Spirit.hpp"

using namespace ToyGameEngine::Spirits;
using namespace ToyGameEngine::Math;

Spirit *Spirit::clone() const
{
    return new Spirits::Spirit(*this);
}

Spirit::Spirit(const Math::Geometry::Vector &position)
    : _position(position)
{
}

Spirit::Spirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity)
    : _position(position), _velocity(velocity)
{
}

Spirit::Spirit(const Math::Geometry::Vector &position, const double direction)
    : _position(position), _direction(Math::Geometry::degree_to_rad(direction))
{
}

Spirit::Spirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const double direction)
    : _position(position), _velocity(velocity), _direction(Math::Geometry::degree_to_rad(direction))
{
}

void Spirit::set_position(const Math::Geometry::Vector &position)
{
    this->_position = position;
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

Geometry::Vector Spirit::position() const
{
    return this->_position;
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

void Spirit::update()
{
}