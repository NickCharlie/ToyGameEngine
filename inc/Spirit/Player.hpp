#pragma once

#include "Character.hpp"

namespace ToyGameEngine 
{
    namespace Spirits 
    {
        template<typename T>
        class Player : public Character<T> {
        public:
            Player(const Math::Geometry::Vector& position) : Character(position) {}
            Player(const Math::Geometry::Vector& position, const Math::Geometry::Vector& velocity) : Character(position, velocity) {}
            Player(const Math::Geometry::Vector& position, const double direction) : Character(position, direction) {}
            Player(const Math::Geometry::Vector& position, const Math::Geometry::Vector& velocity, const double direction) : Character(position, velocity, direction) {}
        };
    }
}