#pragma once

#include "ShapedSpirit.hpp"

namespace ToyGameEngine
{
    namespace Spirits
    {
        template <typename T>
        class Character : public ShapedSpirit<T>
        {
        public:
            Character(const Math::Geometry::Vector &position) : Spirit(position) {}
            Character(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity) : Spirit(position, velocity) {}
            Character(const Math::Geometry::Vector &position, const double direction) : Spirit(position, direction) {}
            Character(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const double direction) : Spirit(position, velocity, direction) {}

            float health() const;
            bool bis_dead() const;

            void set_health(float health);
            void set_bis_dead(bool is_dead);

        private:
            float _health;
            bool _is_dead = false;
        };

        template <typename T>
        float Character<T>::health() const
        {
            return this->_health;
        }

        template <typename T>
        bool Character<T>::bis_dead() const
        {
            return this->_is_dead;
        }

        template <typename T>
        void Character<T>::set_health(float health)
        {
            this->_health = health;
        }

        template <typename T>
        void Character<T>::set_bis_dead(bool is_dead)
        {
            this->_is_dead = is_dead;
        }
    }
}