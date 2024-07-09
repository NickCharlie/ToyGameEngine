#pragma once

#include <string>
#include "Math/Geometry/Point.hpp"
#include "Scene/Event.hpp"


namespace ToyGameEngine
{
    namespace Spirits
    {
        class Spirit : public Math::Geometry::Point
        {
        public:
            bool key_event_update = false;
            bool mouse_event_update = false;
            bool ignore_all_events = false;

        public:
            Spirit(const Math::Geometry::Vector &position);
            Spirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity);
            Spirit(const Math::Geometry::Vector &position, const double direction);
            Spirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const double direction);
            Spirit(const double x, const double y);
            Spirit(const double x, const double y, const Math::Geometry::Vector &velocity);
            Spirit(const double x, const double y, const double direction);
            Spirit(const double x, const double y, const Math::Geometry::Vector &velocity, const double direction);

            Math::Geometry::Vector velocity() const;
            void set_velocity(const Math::Geometry::Vector &velocity);

            double direction() const;
            void set_degree_direction(double degree);
            void set_rad_direction(double rad);

            std::string name() const;
            void set_name(std::string);

            bool visible() const;
            void show();
            void hide();

            Spirits::Spirit *clone() const override;

            virtual void update();

            virtual void update(Scenes::Event *event);

            virtual void update(Scenes::KeyEvent *event);

            virtual void update(Scenes::MouseEvent *event);

        protected:
            Math::Geometry::Vector _velocity;
            double _direction;

            std::string _name;
            bool _visible = true;
        };

    }
}