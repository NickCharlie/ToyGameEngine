#pragma once
#include "Math/Geometry/Polyline.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            class Bezier : public Polyline
            {
            private:
                size_t _order = 2;
                Polyline _shape;

            public:
                Bezier(const size_t n);

                Bezier(const Bezier &bezier);

                Bezier(std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end, const size_t n);

                Bezier(const std::initializer_list<Point> &points, const size_t n);

                // 贝塞尔曲线阶数
                size_t order() const;

                const Polyline &shape() const;

                void update_shape(const double step = 0.01);

                void append_shape(const double step = 0.01);

                double length() const override;

                void clear() override;

                Bezier *clone() const override;

                Bezier &operator=(const Bezier &bezier);

                void transform(const double a, const double b, const double c, const double d, const double e, const double f) override;

                void transform(const double mat[6]) override;

                void translate(const double tx, const double ty) override;

                void rotate(const double x, const double y, const double rad) override;

                void scale(const double x, const double y, const double k) override;

                Type type() const override;

                Polygon convex_hull() const override;

                AABBRect bounding_rect() const override;

                Polygon mini_bounding_rect() const override;
            };
        }
    }
}