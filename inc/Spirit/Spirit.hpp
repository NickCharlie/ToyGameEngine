#pragma once

#include "Math/Geometry/Point.hpp"
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/GeometryObject.hpp"
#include <string>

namespace ToyGameEngine 
{
    namespace Spirits 
    {
        class Spirit : public Math::Geometry::GeometryObject 
        {
        public:
            Spirit(const Math::Geometry::Vector& position);
            Spirit(const Math::Geometry::Vector& position, const Math::Geometry::Vector& velocity);
            Spirit(const Math::Geometry::Vector& position, const double direction);
            Spirit(const Math::Geometry::Vector& position, const Math::Geometry::Vector& velocity, const double direction);

            Math::Geometry::Vector position() const;
            
            void set_position(const Math::Geometry::Vector& position);

            Math::Geometry::Vector velocity() const;
            void set_velocity(const Math::Geometry::Vector& velocity);

            double direction() const;
            void set_degree_direction(double degree);
            void set_rad_direction(double rad);

            std::string name() const;
            void set_name(std::string);

            bool visible() const;
            void show();
            void hide();

            Spirits::Spirit* clone() const override;
        private:
            Math::Geometry::Vector _position;
            Math::Geometry::Vector _velocity;
            double _direction;

            std::string _name;
            bool _visible = true;
        };
        

    }
}