#pragma once
#include <vector>
#include "Math/Geometry/Point.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            class AABBRect : public GeometryObject
            {
            private:
                std::vector<Point> _points;

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
                
                Point center() const;

                const Point &operator[](const size_t index) const;

                bool empty() const override;

                double length() const override;

                void clear() override;

                AABBRect *clone() const override;

                double area() const;

                double width() const;

                double height() const;

                void set_width(const double value);

                void set_height(const double value);

                void transform(const double a, const double b, const double c, const double d, const double e, const double f) override;

                void transform(const double mat[6]) override;

                void translate(const double tx, const double ty) override;

                void rotate(const double x, const double y, const double rad) override; // 弧度制

                void scale(const double x, const double y, const double k) override;

                Type type() const override;

                Polygon convex_hull() const override;

                AABBRect bounding_rect() const override;

                Polygon mini_bounding_rect() const override;

                std::vector<Point>::const_iterator begin() const;

                std::vector<Point>::const_iterator cbegin() const;

                std::vector<Point>::const_iterator end() const;

                std::vector<Point>::const_iterator cend() const;

                std::vector<Point>::const_reverse_iterator rbegin() const;

                std::vector<Point>::const_reverse_iterator crbegin() const;

                std::vector<Point>::const_reverse_iterator rend() const;

                std::vector<Point>::const_reverse_iterator crend() const;

                std::vector<Point>::const_iterator find(const Point &point) const;

                AABBRect operator+(const Point &point) const;

                AABBRect operator-(const Point &point) const;

                void operator+=(const Point &point);

                void operator-=(const Point &point);
            };
        }
    }
}