#pragma once
#include <vector>

namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            enum Type {GEOMETRY_OBJECT, POINT, POLYLINE, AABBRECT, POLYGON, TRIANGLE, CIRCLE, LINE, BEZIER};

            class AABBRect;

            class Polygon;

            class GeometryObject
            {
            public:
                GeometryObject();

                GeometryObject(const GeometryObject &object);

                virtual ~GeometryObject();

                GeometryObject &operator=(const GeometryObject &object);

                virtual double length() const;

                virtual bool empty() const;

                virtual void clear();

                virtual GeometryObject *clone() const;

                virtual void transform(const double a, const double b, const double c, const double d, const double e, const double f);

                virtual void transform(const double mat[6]);

                virtual void translate(const double tx, const double ty);

                virtual void rotate(const double x, const double y, const double rad); // 弧度制

                virtual void scale(const double x, const double y, const double k);

                virtual Type type() const;

                // 凸包
                virtual Polygon convex_hull() const;

                // 外接AABB矩形
                virtual AABBRect bounding_rect() const;

                // 最小外接矩形
                virtual Polygon mini_bounding_rect() const;
            };
        }
    }
}