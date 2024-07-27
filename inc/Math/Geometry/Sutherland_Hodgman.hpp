#pragma once
#include <vector>
#include "Math/Geometry/Polygon.hpp"

namespace ToyGameEngine
{

    namespace Math
    {

        namespace Geometry
        {

            class Sutherland_Hodgman
            {
            public:
                static Polygon clip(const Polygon &polygon, const Polygon &clipper);
            private:

                static bool inside(const Point& p, const Point& edgeStart, const Point& edgeEnd);
                static Point intersection(const Point& start, const Point& end, const Point& edgeStart, const Point& edgeEnd);
                static double polygonArea(const std::vector<Point>& polygon);
                static void ensureClockwise(std::vector<Point>& polygon);
            };
        }
    }

}