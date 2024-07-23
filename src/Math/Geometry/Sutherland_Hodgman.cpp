#include "Math/Geometry/Sutherland_Hodgman.hpp"
#include "Math/Geometry/Polygon.hpp"

using namespace ToyGameEngine::Math::Geometry;


Polygon Sutherland_Hodgman::clip(const Polygon &polygon, const Polygon &clipper)
{
    Polygon output = polygon;

    for (size_t i = 0; i < clipper.size(); ++i) {
        Polygon input = output;
        output.clear();

        Point edgeStart = clipper[i];
        Point edgeEnd = clipper[(i + 1) % clipper.size()];

        for (size_t j = 0; j < input.size(); ++j) {
            Point currentVertex = input[j];
            Point prevVertex = input[(j + input.size() - 1) % input.size()];

            if (inside(currentVertex, edgeStart, edgeEnd)) {
                if (!inside(prevVertex, edgeStart, edgeEnd)) {
                    output.append(intersection(prevVertex, currentVertex, edgeStart, edgeEnd));
                }
                output.append(currentVertex);
            }
            else if (inside(prevVertex, edgeStart, edgeEnd)) {
                output.append(intersection(prevVertex, currentVertex, edgeStart, edgeEnd));
            }
        }
    }

    return output;
}



bool Sutherland_Hodgman::inside(const Point &p, const Point &edgeStart, const Point &edgeEnd)
{
     return (edgeEnd.x - edgeStart.x) * (p.y - edgeStart.y) > (edgeEnd.y - edgeStart.y) * (p.x - edgeStart.x);
}

Point Sutherland_Hodgman::intersection(const Point &start, const Point &end, const Point &edgeStart, const Point &edgeEnd)
{
    float a1 = end.y - start.y;
    float b1 = start.x - end.x;
    float c1 = a1 * start.x + b1 * start.y;

    float a2 = edgeEnd.y - edgeStart.y;
    float b2 = edgeStart.x - edgeEnd.x;
    float c2 = a2 * edgeStart.x + b2 * edgeStart.y;

    float determinant = a1 * b2 - a2 * b1;

    Point intersect;
    intersect.x = (b2 * c1 - b1 * c2) / determinant;
    intersect.y = (a1 * c2 - a2 * c1) / determinant;

    return intersect;
}
