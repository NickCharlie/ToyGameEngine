#pragma once

#include "Spirit.hpp"
#include "Math/Geometry/AllGeometryObjects.hpp"

namespace ToyGameEngine
{
    namespace Spirits
    {

        template <typename T>
        class ShapedSpirit : public Spirit
        {
        public:
            ShapedSpirit(const Math::Geometry::Vector &position) : Spirit(position) {}
            ShapedSpirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity) : Spirit(position, velocity) {}
            ShapedSpirit(const Math::Geometry::Vector &position, const double direction) : Spirit(position, direction) {}
            ShapedSpirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const double direction) : Spirit(position, velocity, direction) {}
            Math::Geometry::Type type() const override;

            T &shape();
            const T &shape() const;
            void replace(const T &shape);

        private:
            T _shape;
        };

        template <typename T>
        T &ShapedSpirit<T>::shape()
        {
            return _shape;
        }

        template <typename T>
        const T &ShapedSpirit<T>::shape() const
        {
            return _shape;
        }

        template <typename T>
        void ShapedSpirit<T>::replace(const T &shape)
        {
            _shape = shape;
        }

        template <typename T>
        Math::Geometry::Type ShapedSpirit<T>::type() const
        {
            return _shape.type();
        }


        using RectangleSpirit = ShapedSpirit<Math::Geometry::Rectangle>;
        using AABBRectSpirit = ShapedSpirit<Math::Geometry::AABBRect>;
        using SquareSpirit = ShapedSpirit<Math::Geometry::Square>;
        using CircleSpirit = ShapedSpirit<Math::Geometry::Circle>;
        using PointSpirit = ShapedSpirit<Math::Geometry::Point>;
        using LineSpirit = ShapedSpirit<Math::Geometry::Line>;
        using PolylineSpirit = ShapedSpirit<Math::Geometry::Polyline>;
        using Polygon = ShapedSpirit<Math::Geometry::Polygon>;
    }
}