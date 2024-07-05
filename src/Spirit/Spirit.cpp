#include "Spirit/Spirit.hpp"

using namespace ToyGameEngine::Spirits;
using namespace ToyGameEngine::Math;


Spirit* Spirit::clone() const
{
    return new Spirits::Spirit(*this);
}

Spirit::Spirit(const Math::Geometry::Vector& position)
{
    set_position(position);
}

Spirit::Spirit(const Math::Geometry::Vector& position, const Math::Geometry::Vector& velocity)
{
    set_position(position);
    set_velocity(velocity);
}

Spirit::Spirit(const Math::Geometry::Vector& position, const double direction)
{
    set_position(position);
    set_degree_direction(direction);
}

Spirit::Spirit(const Math::Geometry::Vector& position, const Math::Geometry::Vector& velocity, const double direction)
{
    set_position(position);
    set_velocity(velocity);
    set_degree_direction(direction);
}

void Spirit::set_position(const Math::Geometry::Vector& position)
{
    this->_position = position;
}

void Spirit::set_velocity(const Math::Geometry::Vector& velocity)
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