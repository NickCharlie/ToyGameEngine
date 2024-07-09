#pragma once
#include "Math/Geometry/Point.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            class Line : public GeometryObject
            {
            private:
                Point _start_point;
                Point _end_point;

            public:
                Line();

                Line(const double x0, const double y0, const double x1, const double y1);

                Line(const Point &start, const Point &end);

                Line(const Line &line);

                Line &operator=(const Line &line);

                Line operator+(const Point &point);

                Line operator-(const Point &point);

                void operator+=(const Point &point);

                void operator-=(const Point &point);

                double length() const override;

                bool empty() const override;

                void clear() override;

                Line *clone() const override;

                void transform(const double a, const double b, const double c, const double d, const double e, const double f) override;

                void transform(const double mat[6]) override;

                void translate(const double tx, const double ty) override;

                void rotate(const double x, const double y, const double rad) override; // 弧度制

                void scale(const double x, const double y, const double k) override;

                Type type() const override;

                AABBRect bounding_rect() const override;

                Polygon mini_bounding_rect() const override;

                Point average_point() const override;

                Point &front();

                const Point &front() const;

                Point &back();

                const Point &back() const;
            };
        }
    }
}