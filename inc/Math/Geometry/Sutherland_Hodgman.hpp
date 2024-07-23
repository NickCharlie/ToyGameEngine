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
                // �жϵ��Ƿ��ڱ߽���ڲ�
                static bool inside(const Point& p, const Point& edgeStart, const Point& edgeEnd);
                // �����߶���߽�Ľ���
                static Point intersection(const Point& start, const Point& end, const Point& edgeStart, const Point& edgeEnd);
            };
        }
    }

}