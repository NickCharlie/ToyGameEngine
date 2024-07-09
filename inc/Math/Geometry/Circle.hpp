#pragma once
#include "Math/Geometry/Point.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            class Circle : public Point
            {
            public:
                double radius = 0;

            public:
                Circle();

                Circle(const double x, const double y, const double r);

                Circle(const Point &point, const double r);

                Circle(const Circle &circle);

                Circle &operator=(const Circle &circle);

                double area() const;

                double length() const override;

                bool empty() const override;

                void clear() override;

                Circle *clone() const override;

                void transform(const double a, const double b, const double c, const double d, const double e, const double f) override;

                void transform(const double mat[6]) override;

                void scale(const double x, const double y, const double k) override;

                Type type() const override;

                AABBRect bounding_rect() const override;

                Polygon mini_bounding_rect() const override;

                Point average_point() const override;

                Circle operator+(const Point &point) const;

                Circle operator-(const Point &point) const;
            };
        }
    }
}