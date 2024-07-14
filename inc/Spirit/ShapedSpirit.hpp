#pragma once

#include "Spirit.hpp"
#include "Math/Geometry/AllGeometryObjects.hpp"

#include <QPixmap>

namespace ToyGameEngine
{
    namespace Spirits
    {

        template <typename T>
        class ShapedSpirit : public Spirit
        {
        public:
            ShapedSpirit(const Math::Geometry::Vector &position) : Spirit(position) {}

            template <typename = std::enable_if_t<!std::is_same_v<T, Math::Geometry::Point>>>
            ShapedSpirit(const Math::Geometry::Vector &position, const T &shape) : Spirit(position)
            {
                set_shape(shape);
            }

            ShapedSpirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity)
                : Spirit(position, velocity) {}

            ShapedSpirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const T &shape)
                : Spirit(position, velocity)
            {
                set_shape(shape);
            }

            ShapedSpirit(const Math::Geometry::Vector &position, const double direction)
                : Spirit(position, direction) {}

            ShapedSpirit(const Math::Geometry::Vector &position, const double direction, const T &shape)
                : Spirit(position, direction)
            {
                set_shape(shape);
            }

            ShapedSpirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const double direction)
                : Spirit(position, velocity, direction) {}

            ShapedSpirit(const Math::Geometry::Vector &position, const Math::Geometry::Vector &velocity, const double direction, const T &shape)
                : Spirit(position, velocity, direction)
            {
                set_shape(shape);
            }

            Math::Geometry::Type type() const override
            {
                return _shape.type();
            }

            const T &shape() const
            {
                return _shape;
            }

            void replace_shape(const T &shape)
            {
                _shape = shape;
            }

            void set_shape(const T &shape)
            {
                if constexpr (std::is_same_v<T, Math::Geometry::Point>)
                {
                    _shape = *this;
                    return;
                }

                _shape = shape;
                if constexpr (std::is_same_v<T, Math::Geometry::Bezier>)
                {
                    const Math::Geometry::Vector vec = (*this) - shape.shape().front();
                    _shape.translate(vec.x, vec.y);
                }
                else if constexpr (std::is_same_v<T, Math::Geometry::Polyline> || std::is_same_v<T, Math::Geometry::Line>)
                {
                    const Math::Geometry::Vector vec = (*this) - shape.front();
                    _shape.translate(vec.x, vec.y);
                }
                else if constexpr (std::is_same_v<T, Math::Geometry::Triangle>)
                {
                    const Math::Geometry::Vector vec = (*this) - shape.inner_circle_center();
                    _shape.translate(vec.x, vec.y);
                }
                else if constexpr (std::is_same_v<T, Math::Geometry::Circle>)
                {
                    const Math::Geometry::Vector vec = (*this) - shape;
                    _shape.translate(vec.x, vec.y);
                }
                else if constexpr (std::is_same_v<T, Math::Geometry::Rectangle> || std::is_base_of_v<T, Math::Geometry::Rectangle>)
                {
                    const Math::Geometry::Vector vec = (*this) - shape.center();
                    _shape.translate(vec.x, vec.y);
                }
                else
                {
                    const Math::Geometry::Vector vec = (*this) - shape.bounding_rect().center();
                    _shape.translate(vec.x, vec.y);
                }
            }

            void transform(const double a, const double b, const double c, const double d, const double e, const double f) override
            {
                Spirit::transform(a, b, c, d, e, f);
                _shape.transform(a, b, c, d, e, f);
            }

            void transform(const double mat[6]) override
            {
                Spirit::transform(mat);
                _shape.transform(mat);
            }

            void translate(const double tx, const double ty) override
            {
                Spirit::translate(tx, ty);
                _shape.translate(tx, ty);
            }

            void rotate(const double x_, const double y_, const double rad) override
            {
                Spirit::rotate(x_, y_, rad);
                _shape.rotate(x_, y_, rad);
            }

            void scale(const double x_, const double y_, const double k) override
            {
                Spirit::scale(x_, y_, k);
                _shape.scale(x_, y_, k);
            }

            Math::Geometry::AABBRect bounding_rect() const override
            {
                return _shape.bounding_rect();
            }

            Math::Geometry::Polygon mini_bounding_rect() const override
            {
                return _shape.mini_bounding_rect();
            }

            void set_pixmap(QPixmap map) 
            {
                pixmap = map;
            }

            QPixmap& get_pixmap()
            {
                return pixmap;
            }

        private:
            T _shape;
            
            QPixmap pixmap;
        };


        using RectangleSpirit = ShapedSpirit<Math::Geometry::Rectangle>;
        using AABBRectSpirit = ShapedSpirit<Math::Geometry::AABBRect>;
        using SquareSpirit = ShapedSpirit<Math::Geometry::Square>;
        using CircleSpirit = ShapedSpirit<Math::Geometry::Circle>;
        using PointSpirit = ShapedSpirit<Math::Geometry::Point>;
        using LineSpirit = ShapedSpirit<Math::Geometry::Line>;
        using PolylineSpirit = ShapedSpirit<Math::Geometry::Polyline>;
        using PolygonSpirit = ShapedSpirit<Math::Geometry::Polygon>;
    }
}