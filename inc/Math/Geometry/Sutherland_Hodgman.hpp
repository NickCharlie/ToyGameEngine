#pragma once
#include <vector>
#include "Polygon.hpp"


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
                // 判断点是否在边界的内侧
                static bool inside(const Point& p, const Point& edgeStart, const Point& edgeEnd);
                // 计算线段与边界的交点
                static Point intersection(const Point& start, const Point& end, const Point& edgeStart, const Point& edgeEnd);
            };
        }
    }

}