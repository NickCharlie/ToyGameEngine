#include "Math/Geometry/Algorithm.hpp"
#include "Math/Geometry/Sutherland_Hodgman.hpp"


using namespace ToyGameEngine::Math::Geometry;


Polygon Sutherland_Hodgman::clip(const Polygon &polygon, const Polygon &clipper)
{
    std::vector<Point> input, output(polygon.begin(), polygon.end() - 1);
    Polygon clipper_points(clipper);
    if (clipper_points.is_cw())
    {
        clipper_points.flip();
    }

    Geometry::Point point;
    for (size_t i = 1, count0 = clipper.size(); i < count0; ++i)
    {
        std::swap(input, output);
        output.clear();

        const Point &edgeStart = clipper_points[i - 1];
        const Point &edgeEnd = clipper_points[i];

        for (size_t j = 0, count1 = input.size(); j < count1; ++j)
        {
            const Point &currentVertex = input[j];
            const Point &prevVertex = input[(j + count1 - 1) % count1];

            if (inside(currentVertex, edgeStart, edgeEnd))
            {
                if (!inside(prevVertex, edgeStart, edgeEnd))
                {
                    Geometry::is_intersected(prevVertex, currentVertex, edgeStart, edgeEnd, point, true);
                    output.emplace_back(point);
                }
                output.emplace_back(currentVertex);
            }
            else if (inside(prevVertex, edgeStart, edgeEnd))
            {
                Geometry::is_intersected(prevVertex, currentVertex, edgeStart, edgeEnd, point, true);
                output.emplace_back(point);
            }
        }
    }
    return Polygon(output.begin(), output.end());
}