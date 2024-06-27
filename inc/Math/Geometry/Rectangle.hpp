#pragma once
#include <array>
#include "Math/Geometry/Point.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            class Rectangle : public GeometryObject
            {
            protected:
                std::array<Point, 4> _points = {Point(0, 0)};

            public:
                Rectangle();

                Rectangle(const double x, const double y, const double w, const double h);

                Rectangle(const Point &point0, const Point &point1);

                Rectangle(const Rectangle &rect);

                Rectangle(const Point &center, const double w, const double h);

                Rectangle &operator=(const Rectangle &rect);
                
                Point center() const;

                const Point &operator[](const size_t index) const;

                bool empty() const override;

                double length() const override;

                void clear() override;

                Rectangle *clone() const override;

                double area() const;

                double width() const;

                double height() const;

                void transform(const double a, const double b, const double c, const double d, const double e, const double f) override;

                void transform(const double mat[6]) override;

                void translate(const double tx, const double ty) override;

                void rotate(const double x, const double y, const double rad) override; // 弧度制

                void scale(const double x, const double y, const double k) override;

                Type type() const override;

                Polygon convex_hull() const override;

                AABBRect bounding_rect() const override;

                Polygon mini_bounding_rect() const override;

                std::array<Point, 4>::const_iterator begin() const;

                std::array<Point, 4>::const_iterator cbegin() const;

                std::array<Point, 4>::const_iterator end() const;

                std::array<Point, 4>::const_iterator cend() const;

                std::array<Point, 4>::const_reverse_iterator rbegin() const;

                std::array<Point, 4>::const_reverse_iterator crbegin() const;

                std::array<Point, 4>::const_reverse_iterator rend() const;

                std::array<Point, 4>::const_reverse_iterator crend() const;

                std::array<Geometry::Point, 4>::const_iterator find(const Point &point) const;

                Rectangle operator+(const Point &point) const;

                Rectangle operator-(const Point &point) const;

                void operator+=(const Point &point);

                void operator-=(const Point &point);

                size_t next_point_index(const size_t index) const;

                const Point &next_point(const size_t index) const;

                size_t last_point_index(const size_t index) const;

                const Point &last_point(const size_t index) const;

                size_t index(const double x, const double y) const;

                size_t index(const Point &point) const;

                // 外接圆半径
                double outer_circle_radius() const;
            };
        }
    }
}