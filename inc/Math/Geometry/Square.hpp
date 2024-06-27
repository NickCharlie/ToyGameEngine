#pragma once
#include "Math/Geometry/Rectangle.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            class Square : public Rectangle
            {
            public:
                Square();

                Square(const double x, const double y, const double w);

                Square(const Point &center, const double w);

                Square(const Square &square);

                Square &operator=(const Square &square);

                Square *clone() const override;

                Type type() const override;

                double inner_cicle_radius() const;
            };
        }
    }
}