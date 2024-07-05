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
            Math::Geometry::Type type() const override;
        private:
            T _shape;
        };

        template<typename T>
        Math::Geometry::Type ShapedSpirit<T>::type() const override 
        {
            if constexpr (std::is_same_v<T, Math::Geometry::Polygon>) 
            {
                return Math::Geometry::Type::POLYGON;
            }
            else if constexpr (std::is_same_v<T, Math::Geometry::Rectangle>)
            {
                return Math::Geometry::Type::RECTANGLE;
            }
            else if constexpr (std::is_same_v<T, Math::Geometry::AABBRect>)
            {
                return Math::Geometry::Type::AABBRect;
            }
            else
            {
                return Math::Geometry::Type::GEOMETRY_OBJECT;
            }
        }
    }
}