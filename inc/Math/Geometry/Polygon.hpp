#pragma once
#include "Math/Geometry/Polyline.hpp"
#include "Math/Geometry/Rectangle.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            class Polygon : public Polyline
            {
            public:
                Polygon();

                Polygon(const Polygon &polygon);

                Polygon(std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end);

                Polygon(std::array<Point, 4>::const_iterator begin, std::array<Point, 4>::const_iterator end);

                Polygon(const std::initializer_list<Point> &points);

                Polygon(const Polyline &polyline);

                Polygon(const AABBRect &rect);

                Polygon &operator=(const Polygon &polygon);

                Polygon &operator=(const Rectangle &rect);

                Polygon *clone() const override;

                Type type() const override;

                void reorder_points(const bool cw = true);

                // 判断点顺序是否为顺时针
                bool is_cw() const;

                void append(const Point &point) override;

                void append(const Polyline &polyline) override;

                void append(std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end) override;

                void insert(const size_t index, const Point &point) override;

                void insert(const size_t index, const Polyline &polyline) override;

                void insert(const size_t index, std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end) override;

                void remove(const size_t index) override;

                void remove(const size_t index, const size_t count) override;

                Point pop(const size_t index) override;

                Polygon operator+(const Point &point) const;

                Polygon operator-(const Point &point) const;

                double area() const;

                size_t next_point_index(const size_t index) const;

                const Point &next_point(const size_t index) const;

                Point &next_point(const size_t index);

                size_t last_point_index(const size_t index) const;

                const Point &last_point(const size_t index) const;

                Point &last_point(const size_t index);

                size_t index(const double x, const double y) const;

                size_t index(const Point &point) const;

                Point average_point() const override;
            };
        }
    }
}