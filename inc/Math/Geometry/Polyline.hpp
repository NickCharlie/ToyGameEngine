#pragma once
#include <vector>
#include <array>
#include "Math/Geometry/Point.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            class Polyline : public GeometryObject
            {
            protected:
                std::vector<Point> _points;

            public:
                Polyline();

                Polyline(const Polyline &polyline);

                Polyline(std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end);

                Polyline(std::array<Point, 4>::const_iterator begin, std::array<Point, 4>::const_iterator end);

                Polyline(const std::initializer_list<Point> &points);

                size_t size() const;

                bool empty() const override;

                double length() const override;

                void clear() override;

                Polyline *clone() const override;

                bool is_self_intersected() const;

                Point &operator[](const size_t index);

                const Point &operator[](const size_t index) const;

                Polyline &operator=(const Polyline &polyline);

                Polyline operator+(const Point &point) const;

                Polyline operator-(const Point &point) const;

                void operator+=(const Point &point);

                void operator-=(const Point &point);

                virtual void append(const Point &point);

                virtual void append(const Polyline &polyline);

                virtual void append(std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end);

                virtual void insert(const size_t index, const Point &point);

                virtual void insert(const size_t index, const Polyline &polyline);

                virtual void insert(const size_t index, std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end);

                virtual void remove(const size_t index);

                virtual void remove(const size_t index, const size_t count);

                virtual Point pop(const size_t index);

                void flip();

                Point &front();

                const Point &front() const;

                Point &back();

                const Point &back() const;

                std::vector<Point>::iterator begin();

                std::vector<Point>::const_iterator begin() const;

                std::vector<Point>::const_iterator cbegin() const;

                std::vector<Point>::iterator end();

                std::vector<Point>::const_iterator end() const;

                std::vector<Point>::const_iterator cend() const;

                std::vector<Point>::reverse_iterator rbegin();

                std::vector<Point>::const_reverse_iterator rbegin() const;

                std::vector<Point>::const_reverse_iterator crbegin() const;

                std::vector<Point>::reverse_iterator rend();

                std::vector<Point>::const_reverse_iterator rend() const;

                std::vector<Point>::const_reverse_iterator crend() const;

                std::vector<Point>::iterator find(const Point &point);

                std::vector<Point>::const_iterator find(const Point &point) const;

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