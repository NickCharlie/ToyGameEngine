#pragma once
#include "Math/Geometry/GeometryObject.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            struct MarkedPoint;

            class Point : public GeometryObject
            {
            public:
                double x = 0;
                double y = 0;

            public:
                Point();

                Point(const double x_, const double y_);

                Point(const Point &point);

                Point(const MarkedPoint &point);

                Point &operator=(const Point &point);

                bool operator==(const Point &point) const;

                bool operator!=(const Point &point) const;

                Point &normalize();

                Point normalized() const;

                // 获取左侧的垂直向量
                Point vertical() const;

                // 向量模长
                double length() const override;

                // 判断是否为零向量
                bool empty() const override;

                // 变为零向量
                void clear() override;

                Point *clone() const override;

                void transform(const double a, const double b, const double c, const double d, const double e, const double f) override;

                void transform(const double mat[6]) override;

                void translate(const double tx, const double ty) override;

                void rotate(const double x_, const double y_, const double rad) override;

                void scale(const double x_, const double y_, const double k) override;

                Type type() const override;

                AABBRect bounding_rect() const override;

                Polygon mini_bounding_rect() const override;

                Point average_point() const override;

                Point operator*(const double k) const;

                // 向量点积
                double operator*(const Point &point) const;

                // 向量叉积
                double cross(const Point &point) const;

                Point operator+(const Point &point) const;

                Point operator-(const Point &point) const;

                Point operator/(const double k) const;

                void operator*=(const double k);

                void operator+=(const Point &point);

                void operator-=(const Point &point);

                void operator/=(const double k);
            };

            using Vector = Point;
        }
    }
}
   