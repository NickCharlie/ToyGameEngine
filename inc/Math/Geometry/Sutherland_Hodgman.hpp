#pragma once
#include "Math/Geometry/Polygon.hpp"

namespace ToyGameEngine
{

    namespace Math
    {

        namespace Geometry
        {

            namespace Sutherland_Hodgman
            {
                Polygon clip(const Polygon &polygon, const Polygon &clipper);

                namespace
                {
                    bool inside(const Point& p, const Point& edgeStart, const Point& edgeEnd)
                    {
                        return (edgeEnd.x - edgeStart.x) * (p.y - edgeStart.y) > (edgeEnd.y - edgeStart.y) * (p.x - edgeStart.x);
                    }
                }
            }
        }
    }

}