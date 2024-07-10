#pragma once
#include <vector>


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            const static double PI = 3.14159265358979323846;
            const static double EPSILON = 1e-10;

            struct MarkedPoint
            {
                bool original = true;
                bool active = true;
                int value = 0;
                double x = 0;
                double y = 0;

                MarkedPoint();

                MarkedPoint(const double x_, const double y_, const bool original_ = true, const int value_ = 0);

                bool operator==(const MarkedPoint &point) const;

                bool operator!=(const MarkedPoint &point) const;
            };

            class GeometryObject;
            class Point;
            using Vector = Point;
            class Line;
            class Polyline;
            class Polygon;
            class Rectangle;
            class AABBRect;
            class Square;
            class Circle;
            class Triangle;

            // 两点间距离
            double distance(const double x0, const double y0, const double x1, const double y1);

            // 两点间距离
            double distance(const Point &point0, const Point &point1);

            // 点到直线距离,如果为有限长线段且垂足不在线段上,则计算点到线段端点距离
            double distance(const Point &point, const Line &line, const bool infinite = false);

            // 点到直线距离,如果为有限长线段且垂足不在线段上,则计算点到线段端点距离
            double distance(const Point &point, const Point &start, const Point &end, const bool infinite = false);

            // 点到多段线距离,计算点到每一段有限长线段的距离,取最近距离
            double distance(const Point &point, const Polyline &polyline);

            // 点到多边形距离,计算点到每一段有限长线段的距离,取最近距离
            double distance(const Point &point, const Polygon &polygon);

            // 点到矩形距离,计算点到每一段有限长线段的距离,取最近距离
            double distance(const Point &point, const Rectangle &rect);

            // 两有限长线段间的距离
            double distance(const Point &start0, const Point &end0, const Point &start1, const Point &end1);

            // 两有限长线段间的距离
            double distance(const Point &start0, const Point &end0, const Point &start1, const Point &end1, Point &point0, Point &point1);

            // 两点间距离的平方
            double distance_square(const double x0, const double y0, const double x1, const double y1);

            // 两点间距离的平方
            double distance_square(const Point &point0, const Point &point1);

            // 点到直线距离的平方,如果为有限长线段且垂足不在线段上,则计算点到线段端点距离
            double distance_square(const Point &point, const Line &line, const bool infinite = false);

            // 点到直线距离的平方,如果为有限长线段且垂足不在线段上,则计算点到线段端点距离
            double distance_square(const Point &point, const Point &start, const Point &end, const bool infinite = false);

            // 判断点是否在有限长线段或直线上
            bool is_inside(const Point &point, const Line &line, const bool infinite = false);

            // 判断点是否在有限长线段或直线上
            bool is_inside(const Point &point, const Point &start, const Point &end, const bool infinite = false);

            // 判断点是否在多段线上
            bool is_inside(const Point &point, const Polyline &polyline);

            // 判断点是否在多边形内,coincide决定是否包含点在多边形上的情况
            bool is_inside(const Point &point, const Polygon &polygon, const bool coincide = false);

            // 判断点是否在矩形内,conincide决定是否包含在矩形上的情况
            bool is_inside(const Point &point, const Rectangle &rect, const bool coincide = false);

            // 判断点是否在正方形内,conincide决定是否包含含正方形上的情况
            bool is_inside(const Point &point, const Square &square, const bool coincide = false);

            // 判断点是否在AABB矩形内,coincide决定是否包含点在AABB矩形上的情况
            bool is_inside(const Point &point, const AABBRect &rect, const bool coincide = false);

            // 判断点是否在圆内,coincide决定是否包含点在圆上的情况
            bool is_inside(const Point &point, const Circle &circle, const bool coincide = false);

            // 判断点是否在三角形内,coincide决定是否包含点在三角形上的情况
            bool is_inside(const Point &point, const Point &point0, const Point &point1, const Point &point2, const bool coincide = false);

            // 判断点是否在三角形内,coincide决定是否包含点在三角形上的情况
            bool is_inside(const Point &point, const Triangle &triangle, const bool coincide = false);

            // 判断有限长线段是否完全在三角形内,线段与三角形相交或有端点在三角形上均不算在三角形内部
            bool is_inside(const Point &start, const Point &end, const Triangle &triangle);

            // 判断一个三角形是否完全在另一个三角形内部,与三角形相交或有顶点在三角形上均不算在三角形内部
            bool is_inside(const Triangle &triangle0, const Triangle &triangle1);


            // 判断两直线是否平行
            bool is_parallel(const Point &point0, const Point &point1, const Point &point2, const Point &point3);

            // 判断两直线是否平行
            bool is_parallel(const Line &line0, const Line &line1);


            // 判断两线段是否有重合,仅有一个端点重合不算两线段重合
            bool is_coincide(const Point &start0, const Point &end0, const Point &start1, const Point &end1);

            // 判断有限长线段是否与多边形某一边重合
            bool is_coincide(const Point &start, const Point &end, const Polygon &polygon);


            // 判断一个有限长线段是否是另一个有限长线段的一部分
            bool is_part(const Point &start0, const Point &end0, const Point &start1, const Point &end1);

            // 判断一个有限长线段是否是另一个有限长线段的一部分
            bool is_part(const Line &line0, const Line &line1);


            // 判断两线段是否相交并尝试获取交点,共线相交时仅在一个端点相交时获取交点
            bool is_intersected(const Point &point0, const Point &point1, const Point &point2, const Point &point3, Point &output, const bool infinite = false);

            // 判断两线段是否相交并尝试获取交点,共线相交时仅在一个端点相交时获取交点
            bool is_intersected(const Line &line0, const Line &line1, Point &output, const bool infinite = true);

            // 判断线段是否与矩形相交,infinite决定线段是否为无限长的直线,inside决定线段完全在矩形内是否算相交
            bool is_intersected(const Point &start, const Point &end, const Rectangle &rect, const bool infinite = false, const bool inside = true);

            // 判断线段是否与多段线相交,infinite决定线段是否为无限长的直线
            bool is_intersected(const Point &start, const Point &end, const Polyline &polyline, const bool infinite = false);

            // 判断线段是否与多边形相交,infinite决定线段是否为无限长的直线,inside决定线段完全在多边形内是否算相交
            bool is_intersected(const Point &start, const Point &end, const Polygon &polygon, const bool infinite = false, const bool inside = true);

            // 判断两个AABB矩形是否相交,inside决定完全在AABB矩形内部是否算相交
            bool is_intersected(const AABBRect &rect0, const AABBRect &rect1, const bool inside = true);

            // 判断两多段线是否相交
            bool is_intersected(const Polyline &polyline0, const Polyline &polyline1);

            // 判断多段线是否与多边形相交,inside决定多段线完全在多边形内部是否算相交
            bool is_intersected(const Polyline &polyline, const Polygon &polygon, const bool inside = true);

            // 判断多段线是否与矩形相交,inside决定多段线完全在矩形内部是否算相交
            bool is_intersected(const Polyline &polyline, const Rectangle &rect, const bool inside = true);

            // 判断多段线是否与三角形相交,inside决定多段线完全在三角形内部是否算相交
            bool is_intersected(const Polyline &polyline, const Triangle &triangle, const bool inside = true);

            // 判断多段线是否与圆相交
            bool is_intersected(const Polyline &polyline, const Circle &circle);

            // 判断两多边形是否相交,inside决定完全在多边形内部是否算相交
            bool is_intersected(const Polygon &polygon0, const Polygon &polygon1, const bool inside = true);

            // 判断多边形与矩形是否相交,inside决定多边形完全在矩形内或矩形完全在多边形内部是否算相交
            bool is_intersected(const Polygon &polygon, const Rectangle &rect, const bool inside = true);

            // 判断多边形与三角形是否相交,inside决定多边形完全在三角形内或三角形完全在多边形内部是否算相交
            bool is_intersected(const Polygon &polygon, const Triangle &triangle, const bool inside = true);

            // 判断多边形与圆是否相交,inside决定多边形完全在圆内或圆完全在多边形内是否算相交
            bool is_intersected(const Polygon &polygon, const Circle &circle, const bool inside = true);

            // 判断两圆是否相交,inside决定完全在圆内是否算相交
            bool is_intersected(const Circle &circle0, const Circle &circle1, const bool inside = true);

            // 判断圆和三角形是否相交
            bool is_intersected(const Circle &circle, const Triangle &triangle);

            // 判断两矩形是否相交,inside决定完全在矩形内部是否算相交
            bool is_intersected(const Rectangle &rect0, const Rectangle &rect1, const bool inside = true);

            // 判断矩形与圆是否相交,inside决定圆完全在矩形内部或矩形完全在圆内部是否算相交
            bool is_intersected(const Rectangle &rect, const Circle &circle, const bool inside = true);

            // 判断矩形与圆是否相交,inside决定三角形完全在矩形内部或矩形完全在三角形内部是否算相交
            bool is_intersected(const Rectangle &rect, const Triangle &triangle, const bool inside = true);

            // 判断两正方形是否相交,inside决定完全在正方形内部是否算相交
            bool is_intersected(const Square &square0, const Square &square1, const bool inside = true);

            // 判断正方形与圆是否相交,inside决定圆完全在正方形内部或正方形完全在圆内部是否算相交
            bool is_intersected(const Square &square, const Circle &circle, const bool inside = true);

            // 判断两三角形是否相交,inside决定在三角形内部是否算相交
            bool is_intersected(const Triangle &triangle0, const Triangle &triangle1, const bool inside = true);

            // 判断AABB矩形是否与有限长线段相交,线段完全在AABB矩形内也算相交
            bool is_intersected(const AABBRect &rect, const Point &point0, const Point &point1);

            // 判断AABB矩形是否与有限长线段相交,线段完全在AABB矩形内也算相交
            bool is_intersected(const AABBRect &rect, const Line &line);

            // 判断AABB矩形是否与多段线相交,多段线完全在AABB矩形内也算相交
            bool is_intersected(const AABBRect &rect, const Polyline &polyline);

            // 判断AABB矩形是否与多边形相交,多边形完全在AABB矩形内或AABB矩形完全在多边形内也算相交
            bool is_intersected(const AABBRect &rect, const Polygon &polygon);

            // 判断AABB矩形是否与圆相交,圆完全在AABB矩形内或AABB矩形完全在圆内也算相交
            bool is_intersected(const AABBRect &rect, const Circle &circle);

            // 判断有限长线段是否与三角形相交,线段完全在三角形内不算相交
            bool is_intersected(const Point &start, const Point &end, const Triangle &triangle, Point &output0, Point &output1);

            // 判断有限长线段是否与三角形相交,线段完全在三角形内不算相交
            bool is_intersected(const Line &line, const Triangle &triangle, Point &output0, Point &output1);

            namespace NoAABBTest
            {
                // 判断两多段线是否相交
                bool is_intersected(const Polyline &polyline0, const Polyline &polyline1);

                // 判断多段线是否与多边形相交,inside决定多段线完全在多边形内部是否算相交
                bool is_intersected(const Polyline &polyline, const Polygon &polygon, const bool inside = true);

                // 判断多段线是否与矩形相交,inside决定多段线完全在矩形内部是否算相交
                bool is_intersected(const Polyline &polyline, const Rectangle &rect, const bool inside = true);

                // 判断两多边形是否相交,inside决定完全在多边形内部是否算相交
                bool is_intersected(const Polygon &polygon0, const Polygon &polygon1, const bool inside = true);

                // 判断多边形与矩形是否相交,inside决定多边形完全在矩形内或矩形完全在多边形内部是否算相交
                bool is_intersected(const Polygon &polygon, const Rectangle &rect, const bool inside = true);

                // 判断两矩形是否相交,inside决定完全在矩形内部是否算相交
                bool is_intersected(const Rectangle &rect0, const Rectangle &rect1, const bool inside = true);

                // 判断矩形与圆是否相交,inside决定圆完全在矩形内部或矩形完全在圆内部是否算相交
                bool is_intersected(const Rectangle &rect, const Circle &circle, const bool inside = true);

                // 判断两正方形是否相交,inside决定完全在正方形内部是否算相交
                bool is_intersected(const Square &square0, const Square &square1, const bool inside = true);

                // 判断正方形与圆是否相交,inside决定圆完全在正方形内部或正方形完全在圆内部是否算相交
                bool is_intersected(const Square &square, const Circle &circle, const bool inside = true);

                // 判断AABB矩形是否与多段线相交,多段线完全在AABB矩形内也算相交
                bool is_intersected(const AABBRect &rect, const Polyline &polyline);

                // 判断AABB矩形是否与多边形相交,多边形完全在AABB矩形内或AABB矩形完全在多边形内也算相交
                bool is_intersected(const AABBRect &rect, const Polygon &polygon);

                // 判断两Geometry Object是否相交
                bool is_intersected(const GeometryObject *object0, const GeometryObject *object1, const bool infinite = false, const bool inside = true);

                // 判断AABB矩形与Geometry Object是否相交
                bool is_intersected(const AABBRect &rect, const GeometryObject *object, const bool infinite = false, const bool inside = true);
            }

            // 判断两Geometry Object是否相交
            bool is_intersected(const GeometryObject *object0, const GeometryObject *object1, const bool infinite = false, const bool inside = true);

            // 判断AABB矩形与Geometry Object是否相交
            bool is_intersected(const AABBRect &rect, const GeometryObject *object, const bool infinite = false, const bool inside = true);

            // 判断点是否在直线的左侧
            bool is_on_left(const Point &point, const Point &start, const Point &end);


            // 判断多边形是否是矩形
            bool is_Rectangle(const Polygon &polygon);


            // 计算两向量叉积
            double cross(const double x0, const double y0, const double x1, const double y1);

            // 计算两向量叉积
            double cross(const Vector &vec0, const Vector &vec1);

            // 计算两向量叉积
            double cross(const Point &start0, const Point &end0, const Point &start1, const Point &end1);


            // 计算线段或直线外一点的垂足
            bool foot_point(const Point &start, const Point &end, const Point &point, Point &foot, const bool infinite = false);

            // 计算线段或直线外一点的垂足
            bool foot_point(const Line &line, const Point &point, Point &foot, const bool infinite = false);


            // 计算直线的旋转角度(弧度制,-PI-PI)
            double angle(const Point &start, const Point &end);

            // 计算角度(弧度制,-PI-PI)
            double angle(const Point &point0, const Point &point1, const Point &point2);

            // 计算两直线角夹角(弧度制,-PI-PI)
            double angle(const Point &start0, const Point &end0, const Point &start1, const Point &end1);

            // 计算两直线角夹角(弧度制,-PI-PI)
            double angle(const Line &line0, const Line &line1);


            // 弧度转为-PI-PI
            double rad_to_PI(double value);

            // 弧度转为0-2PI
            double rad_to_2PI(double value);

            // 弧度转为角度
            double rad_to_degree(double value);


            // 角度转为-180°-180°
            double degree_to_180(double value);

            // 角度转为0°-360°
            double degree_to_360(double value);

            // 角度转为弧度
            double degree_to_rad(double value);

            // 常用角度的弧度值
            template <int value>
            inline constexpr double degree_to_rad()
            {
                return value * Geometry::PI / 180;
            }


            // 倒圆角
            bool angle_to_arc(const Point &point0, const Point &point1, const Point &point2, const double radius, Polyline &arc);


            // 圆插值转为多边形
            Polygon circle_to_polygon(const double x, const double y, const double r);

            // 圆插值转为多边形
            Polygon circle_to_polygon(const Circle &circle);


            // 多边形并集
            bool polygon_union(const Polygon &polygon0, const Polygon &polygon1, std::vector<Polygon> &output);

            // 多边形交集
            bool polygon_intersection(const Polygon &polygon0, const Polygon &polygon1, std::vector<Polygon> &output);

            // 多边形差集(polygon0 - polygon1)
            bool polygon_difference(const Polygon &polygon0, const Polygon &polygon1, std::vector<Polygon> &output);


            // 耳切多边形获取点索引
            std::vector<size_t> ear_cut_to_indexs(const Polygon &polygon);

            // 耳切多边形获取点索引
            std::vector<size_t> ear_cut_to_indexs_test(const Polygon &polygon);

            // 耳切多边形获取点
            std::vector<MarkedPoint> ear_cut_to_coords(const Polygon &polygon);

            // 耳切多边形获取点索引
            std::vector<Point> ear_cut_to_points(const Polygon &polygon);

            // 耳切多边形获取三角形
            std::vector<Triangle> ear_cut_to_triangles(const Polygon &polygon);

            // 合并三角形为多边形
            bool merge_ear_cut_triangles(const std::vector<Triangle> &triangles, std::vector<Polygon> &polygons);


            // 偏移多段线
            bool offset(const Polyline &input, Polyline &result, const double distance);

            // 偏移多边形
            bool offset(const Polygon &input, Polygon &result, const double distance);

            // 偏移多边形
            bool offset_test(const Polygon &input, Polygon &result, const double distance);

            // 偏移圆
            bool offset(const Circle &input, Circle &result, const double distance);

            // 偏移AABB矩形
            bool offset(const AABBRect &input, AABBRect &result, const double distance);
        }
    }
}