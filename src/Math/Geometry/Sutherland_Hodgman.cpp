#include "Math/Geometry/Sutherland_Hodgman.hpp"


using namespace ToyGameEngine::Math::Geometry;


Polygon Sutherland_Hodgman::clip(const Polygon &polygon, const Polygon &clipper)
{
    std::vector<Point> output , clipper_points;
    
    for (size_t i = 0; i < polygon.size() - 1; i++)
    {
        output.push_back(polygon[i]);
        
    }
    for (size_t i = 0; i < clipper.size() - 1; i++)
    {
        clipper_points.push_back(clipper[i]);
    }
    ensureClockwise(clipper_points); 
    for (size_t i = 0; i < clipper_points.size(); ++i) 
    {
        std::vector<Point> input = output;
        output.clear();

        Point edgeStart = clipper_points[i];
        Point edgeEnd = clipper_points[(i + 1) % clipper_points.size()];

        for (size_t j = 0; j < input.size(); ++j) 
        {
            Point currentVertex = input[j];
            Point prevVertex = input[(j + input.size() - 1) % (input.size())];

            if (inside(currentVertex, edgeStart, edgeEnd)) 
            {
                 if (!inside(prevVertex, edgeStart, edgeEnd)) 
                 {
                     output.push_back(intersection(prevVertex, currentVertex, edgeStart, edgeEnd));
                 }
                 output.push_back(currentVertex);
            }
            else if (inside(prevVertex, edgeStart, edgeEnd)) 
            {
                output.push_back(intersection(prevVertex, currentVertex, edgeStart, edgeEnd));
            }
        }
    }
    return Polygon(output.begin(), output.end());
}



bool Sutherland_Hodgman::inside(const Point &p, const Point &edgeStart, const Point &edgeEnd)
{
     return (edgeEnd.x - edgeStart.x) * (p.y - edgeStart.y) > (edgeEnd.y - edgeStart.y) * (p.x - edgeStart.x);
}

Point Sutherland_Hodgman::intersection(const Point &start, const Point &end, const  Point &edgeStart, const  Point &edgeEnd)
{
    double a1 = end.y - start.y;
    double b1 = start.x - end.x;
    double c1 = a1 * start.x + b1 * start.y;

    double a2 = edgeEnd.y - edgeStart.y;
    double b2 = edgeStart.x - edgeEnd.x;
    double c2 = a2 * edgeStart.x + b2 * edgeStart.y;

    double determinant = a1 * b2 - a2 * b1;

    Point intersect;
    intersect.x = (b2 * c1 - b1 * c2) / determinant;
    intersect.y = (a1 * c2 - a2 * c1) / determinant;

    return intersect;
}

// �������ε��������ֵ��ʾ˳ʱ�룬��ֵ��ʾ��ʱ��
double Sutherland_Hodgman::polygonArea(const std::vector<Point>& polygon) {
    float area = 0;
    int n = polygon.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += (polygon[i].x * polygon[j].y) - (polygon[j].x * polygon[i].y);
    }
    return area / 2.0;
}

// ȷ������ζ��㰴˳ʱ�뷽������
void Sutherland_Hodgman::ensureClockwise(std::vector<Point>& polygon) {
    if (polygonArea(polygon) < 0) {
        std::reverse(polygon.begin(), polygon.end());
    }
}
