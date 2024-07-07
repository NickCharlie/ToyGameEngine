#pragma once

#include "Spirit.hpp"
#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/GeometryObject.hpp"

namespace ToyGameEngine 
{
    namespace Spirits 
    {

        template<typename T>
        class ShapedSpirit : public Spirit 
        {
        public:
            ShapedSpirit(const Math::Geometry::Vector& position) : Spirit(position) {}
            ShapedSpirit(const Math::Geometry::Vector& position, const Math::Geometry::Vector& velocity) : Spirit(position, velocity) {}
            ShapedSpirit(const Math::Geometry::Vector& position, const double direction) : Spirit(position, direction) {}
            ShapedSpirit(const Math::Geometry::Vector& position, const Math::Geometry::Vector& velocity, const double direction) : Spirit(position, velocity, direction) {}
            Math::Geometry::Type type() const override;

            T& shape();
            void replace(T& shape);
        private:
            T _shape;
        };


        template<typename T>
        T& ShapedSpirit<T>::shape()
        {
            return _shape;
        }

        template<typename T>
        void ShapedSpirit<T>::replace(T& shape)
        {
            _shape = shape;
        }

        template<typename T>
        Math::Geometry::Type ShapedSpirit<T>::type() const
        {
            return this->type();
            // return _shape.type();
        }
    }
}