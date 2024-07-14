#pragma once

#include "Spirit/ShapedSpirit.hpp"
#include "Scene/Event.hpp"

#include <iostream>
#include <unordered_set>

namespace ToyGameEngine
{
    namespace Spirits
    {
        template <typename T>
        class Player : public ShapedSpirit<T>
        {
        public:
            Player(const Math::Geometry::Vector &position)
                : ShapedSpirit<T>(position)
            {
                init();
            }

            template <typename = std::enable_if_t<!std::is_same_v<T, Math::Geometry::Point>>>
            Player(const Math::Geometry::Vector &position, const T &shape)
                : ShapedSpirit<T>(position, shape)
            {
                init();
            }

            Player(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity)
                : ShapedSpirit<T>(position, velocity)
            {
                init();
            }

            Player(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const T &shape)
                : ShapedSpirit<T>(position, velocity, shape)
            {
                init();
            }

            Player(const Math::Geometry::Vector &position, const double direction)
                : ShapedSpirit<T>(position, direction)
            {
                init();
            }

            Player(const Math::Geometry::Vector &position, const double direction, const T &shape)
                : ShapedSpirit<T>(position, direction, shape)
            {
                init();
            }

            Player(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const double direction)
                : ShapedSpirit<T>(position, velocity, direction)
            {
                init();
            }

            Player(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const double direction, const T &shape)
                : ShapedSpirit<T>(position, velocity, direction, shape)
            {
                init();
            }
        
            void update(Scenes::KeyEvent *event) override
            {
                
                for (Scenes::Key k : event->keys)
                {
                    switch (k)
                    {
                    case Scenes::Key::Key_Up:
                        this->translate(0, 4);
                        break;
                    case Scenes::Key::Key_Left:
                        this->translate(-4, 0);
                        break;
                    case Scenes::Key::Key_Right:
                        this->translate(4, 0);
                        break;
                    case Scenes::Key::Key_Down:
                        this->translate(0, -4);
                        break;
                    default:
                        break;
                    }
                        event->active = false;

                }

                event->active = false;
            }

        private:

            std::unordered_set<Scenes::Key> keys_pressed;

            void init()
            {
                this->key_event_update = true;
            }
        };
    }
}