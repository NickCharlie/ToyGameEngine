#pragma once
#include "Math/Geometry/Point.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            class Triangle : public GeometryObject
            {
            private:
                Point _vecs[3] = {Point()};
            
            public:
                Triangle();

                Triangle(const Point &point0, const Point &point1, const Point &point2);

                Triangle(const double x0, const double y0, const double x1, const double y1, const double x2, const double y2);

                Triangle(const Triangle &triangle);

                bool empty() const override;

                double length() const override;

                void clear() override;

                Triangle *clone() const override;

                double area() const;

                // 顶角度数(弧度制)
                double angle(const size_t index) const;

                void reorder_points(const bool cw = true);

                // 判断点顺序是否为顺时针
                bool is_cw() const;

                Point &operator[](const size_t index);

                const Point &operator[](const size_t index) const;

                Triangle &operator=(const Triangle &triangle);

                Triangle operator+(const Point &point) const;

                Triangle operator-(const Point &point) const;

                void operator+=(const Point &point);

                void operator-=(const Point &point);

                void transform(const double a, const double b, const double c, const double d, const double e, const double f) override;

                void transform(const double mat[6]) override;

                void translate(const double tx, const double ty) override;

                void rotate(const double x, const double y, const double rad) override; // 弧度制

                void scale(const double x, const double y, const double k) override;

                Type type() const override;

                Polygon convex_hull() const override;

                AABBRect bounding_rect() const override;

                Polygon mini_bounding_rect() const override;

                // 内接圆圆心
                Point inner_circle_center() const;

                // 内接圆半径
                double inner_circle_radius() const;
            };
        }
    }
}