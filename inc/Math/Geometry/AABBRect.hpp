#pragma once
#include <vector>
#include "Math/Geometry/Rectangle.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            class AABBRect : public Rectangle
            {
            public:
                AABBRect();

                AABBRect(const double x0, const double y0, const double x1, const double y1);

                AABBRect(const Point &point0, const Point &point1);

                AABBRect(const AABBRect &rect);

                double left() const;

                double top() const;

                double right() const;

                double bottom() const;

                void set_left(const double value);

                void set_top(const double value);

                void set_right(const double value);

                void set_bottom(const double value);

                AABBRect &operator=(const AABBRect &rect);

                AABBRect *clone() const override;

                void set_width(const double value);

                void set_height(const double value);

                Type type() const override;
            };
        }
    }
}