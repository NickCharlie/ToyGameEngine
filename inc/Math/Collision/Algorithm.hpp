#pragma once

#include "Math/Geometry/AllGeometryObjects.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Collision
        {
            void gjk_furthest_point(const Geometry::Polygon &polygon, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result);

            void gjk_furthest_point(const Geometry::Polyline &polyline, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result);

            void gjk_furthest_point(const Geometry::Bezier &bezier, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result);

            void gjk_furthest_point(const Geometry::Rectangle &rectangle, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result);

            void gjk_furthest_point(const Geometry::Triangle &triangle, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result);

            void gjk_furthest_point(const Geometry::Circle &circle, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result);

            void gjk_furthest_point(const Geometry::Line &line, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result);

            void gjk_furthest_point(const Geometry::Point &point, const Geometry::Point &start, const Geometry::Point &end, Geometry::Point &result);


            Geometry::Vector edge_direciton(const Geometry::Point &start, const Geometry::Point &end, const bool to_origin);


            bool is_point_inside(const Geometry::Point &point, const Geometry::Polygon &polygon);


            template <typename L, typename R>
            bool gjk(const L &points0, const R &point1)
            {
                Geometry::Point start = points0.average_point(), end = points0.average_point(), point0, point1;
                Geometry::Triangle triangle, last_triangle;
                double distance[3];

                if (start.x == end.x)
                {
                    start.x += 1;
                }
                if (start.y == end.y)
                {
                    start.y += 1;
                }
                Collision::gjk_furthest_point(points0, start, end, point0);
                Collision::gjk_furthest_point(points1, end, start, point1);
                triangle[0] = point0 - point1;
                Collision::gjk_furthest_point(points0, end, start, point0);
                Collision::gjk_furthest_point(points1, start, end, point1);
                triangle[1] = point0 - point1;
                end.clear(); // 现在是原点(0,0)了
                Geometry::foot_point(triangle[0], triangle[1], end, start, true);

                while (true)
                {
                    if (start.x == 0)
                    {
                        start.x = 1;
                    }
                    if (start.y == 0)
                    {
                        start.y = 1;
                    }
                    Collision::gjk_furthest_point(points0, start, end, point0);
                    Collision::gjk_furthest_point(points1, end, start, point1);
                    triangle[2] = point0 - point1;

                    if (triangle[2] * (point0 - point1) < 0)
                    {
                        return false;
                    }

                    if (Geometry::is_inside(end, triangle, true))
                    {
                        return true;
                    }
                    else if (last_triangle[0] == triangle[0] && last_triangle[1] == triangle[1]
                        && last_triangle[2] == triangle[2])
                    {
                        return false;
                    }

                    distance[0] = Geometry::distance_square(end, triangle[0], triangle[1], true);
                    distance[1] = Geometry::distance_square(end, triangle[1], triangle[2], true);
                    distance[2] = Geometry::distance_square(end, triangle[0], triangle[2], true);
                    last_triangle = triangle;
                    if (distance[0] <= distance[1])
                    {
                        if (distance[0] > distance[2])
                        {
                            triangle[1] = triangle[2];
                        }
                    }
                    else
                    {
                        if (distance[1] <= distance[2])
                        {
                            triangle[0] = triangle[2];
                        }
                        else
                        {
                            triangle[1] = triangle[2];
                        }
                    }
                    Geometry::foot_point(triangle[0], triangle[1], end, start, true);
                }
            }

            bool gjk(const Geometry::Circle &circle0, const Geometry::Circle &circle1);

            bool gjk(const Geometry::Circle &circle, const Geometry::Polygon &polygon);

            bool gjk(const Geometry::Circle &circle, const Geometry::Rectangle &rectangle);

            bool gjk(const Geometry::Circle &circle, const Geometry::AABBRect &rectangle);

            bool gjk(const Geometry::Circle &circle, const Geometry::Square &square);

            bool gjk(const Geometry::Circle &circle, const Geometry::Triangle &triangle);

            bool gjk(const Geometry::Polygon &polygon, const Geometry::Circle &circle);

            bool gjk(const Geometry::Rectangle &rectangle, const Geometry::Circle &circle);

            bool gjk(const Geometry::AABBRect &rectangle, const Geometry::Circle &circle);

            bool gjk(const Geometry::Square &square, const Geometry::Circle &circle);

            bool gjk(const Geometry::Triangle &triangle, const Geometry::Circle &circle);

            bool gjk(const Geometry::GeometryObject *points0, const Geometry::GeometryObject *points1);


            template <typename L, typename R>
            double epa(const L &points0, const R &points1, Geometry::Vector &vec)
            {
                Geometry::Point start = points0.average_point(), end = points1.average_point();
                Geometry::Point point0, point1, point2;
                Geometry::Triangle triangle, last_triangle;
                double distance[3] = {DBL_MAX, DBL_MAX, DBL_MAX};

                if (start.x == end.x)
                {
                    start.x += 1;
                }
                if (start.y == end.y)
                {
                    start.y += 1;
                }
                Collision::gjk_furthest_point(points0, start, end, point0);
                Collision::gjk_furthest_point(points1, end, start, point1);
                triangle[0] = point0 - point1;
                Collision::gjk_furthest_point(points0, end, start, point0);
                Collision::gjk_furthest_point(points1, start, end, point1);
                triangle[1] = point0 - point1;
                end.clear(); // 现在是原点(0,0)了
                start = Collision::edge_direciton(triangle[0], triangle[1], false);

                while (true)
                {
                    if (start.x == 0)
                    {
                        start.x = 1;
                    }
                    if (start.y == 0)
                    {
                        start.y = 1;
                    }
                    Collision::gjk_furthest_point(points0, start, end, point0);
                    Collision::gjk_furthest_point(points1, end, start, point1);
                    triangle[2] = point0 - point1;

                    if (triangle[2] * (point0 - point1) < 0)
                    {
                        return -1;
                    }

                    if (Geometry::is_inside(end, triangle))
                    {
                        break;
                    }
                    else if (last_triangle[0] == triangle[0] && last_triangle[1] == triangle[1]
                        && last_triangle[2] == triangle[2])
                    {
                        return -1;
                    }

                    distance[0] = Geometry::distance_square(end, triangle[0], triangle[1]);
                    distance[1] = Geometry::distance_square(end, triangle[1], triangle[2]);
                    distance[2] = Geometry::distance_square(end, triangle[0], triangle[2]);
                    last_triangle = triangle;
                    if (distance[0] <= distance[1])
                    {
                        if (distance[0] > distance[2])
                        {
                            triangle[1] = triangle[2];
                        }
                    }
                    else
                    {
                        if (distance[1] <= distance[2])
                        {
                            triangle[0] = triangle[2];
                        }
                        else
                        {
                            triangle[1] = triangle[2];
                        }
                    }
                    start = Collision::edge_direciton(triangle[0], triangle[1], false);
                }

                std::vector<Geometry::Point> points;
                points.emplace_back(triangle[0]);
                points.emplace_back(triangle[1]);
                points.emplace_back(triangle[2]);

                if (Geo::is_on_left(points[2], points[0], points[1]))
                {
                    std::reverse(points.begin(), points.end());
                }

                size_t index;
                while (true)
                {
                    distance[0] = Geometry::distance_square(end, points.front(), points.back());
                    index = points.size();
                    for (size_t i = 1, count = points.size(); i < count; ++i)
                    {
                        distance[1] = Geometry::distance_square(end, points[i - 1], points[i]);
                        if (distance[1] < distance[0])
                        {
                            distance[0] = distance[1];
                            index = i;
                        }
                    }

                    vec = Collision::edge_direciton(points[index - 1], points[index % points.size()], false);
                    Collision::gjk_furthest_point(points0, end, vec, point0);
                    Collision::gjk_furthest_point(points1, vec, end, point1);
                    point2 = point0 - point1;
                    if (vec * point2 <= 0 || points[index - 1] == point2 || points[index % points.size()] == point2)
                    {
                        break;
                    }
                    else
                    {
                        if (std::find(points.begin(), points.end(), point2) == points.end())
                        {
                            if (index < points.size())
                            {
                                points.insert(points.begin() + index, point2);
                            }
                            else
                            {
                                points.emplace_back(point2);
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            
                distance[0] = Geo::distance_square(end, points.front(), points.back());
                index = points.size();
                for (size_t i = 1, count = points.size(); i < count; ++i)
                {
                    distance[1] = Geo::distance_square(end, points[i - 1], points[i]);
                    if (distance[1] < distance[0])
                    {
                        distance[0] = distance[1];
                        index = i;
                    }
                }
                if (!Geo::foot_point(points[index - 1], points[index % points.size()], end, vec))
                {
                    if (Geo::distance_square(end, points[index - 1]) <= Geo::distance_square(end, points[index % points.size()]))
                    {
                        vec = points[index - 1];
                    }
                    else
                    {
                        vec = points[index % points.size()];
                    }
                }

                return vec.length();
            }

            double epa(const Geometry::Circle &circle0, const Geometry::Circle &circle1, Geometry::Vector &vec);

            double epa(const Geometry::Circle &circle, const Geometry::Polygon &polygon, Geometry::Vector &vec);

            double epa(const Geometry::Circle &circle, const Geometry::Rectangle &rectangle, Geometry::Vector &vec);

            double epa(const Geometry::Circle &circle, const Geometry::AABBRect &rectangle, Geometry::Vector &vec);

            double epa(const Geometry::Circle &circle, const Geometry::Square &square, Geometry::Vector &vec);

            double epa(const Geometry::Circle &circle, const Geometry::Triangle &triangle, Geometry::Vector &vec);

            double epa(const Geometry::Polygon &polygon, const Geometry::Circle &circle, Geometry::Vector &vec);

            double epa(const Geometry::Rectangle &rectangle, const Geometry::Circle &circle, Geometry::Vector &vec);

            double epa(const Geometry::AABBRect &rectangle, const Geometry::Circle &circle, Geometry::Vector &vec);

            double epa(const Geometry::Square &square, const Geometry::Circle &circle, Geometry::Vector &vec);

            double epa(const Geometry::Triangle &triangle, const Geometry::Circle &circle, Geometry::Vector &vec);

            double epa(const Geometry::GeometryObject *points0, const Geometry::GeometryObject *points1, Geometry::Vector &vec);


            template <typename L, typename R>
            double epa(const L &points0, const R &points1, Geometry::Point &head, Geometry::Point &tail)
            {
                Geometry::Point start = points0.average_point(), end = points1.average_point();
                Geometry::Point point0, point1, point2;
                Geometry::Triangle triangle, last_triangle;
                double distance[3] = {DBL_MAX, DBL_MAX, DBL_MAX};
                std::vector<std::tuple<Geometry::Point, Geometry::Point>> point_pairs;

                if (start.x == end.x)
                {
                    start.x += 1;
                }
                if (start.y == end.y)
                {
                    start.y += 1;
                }
                Collision::gjk_furthest_point(points0, start, end, point0);
                Collision::gjk_furthest_point(points1, end, start, point1);
                point_pairs.emplace_back(point0, point1);
                triangle[0] = point0 - point1;
                Collision::gjk_furthest_point(points0, end, start, point0);
                Collision::gjk_furthest_point(points1, start, end, point1);
                point_pairs.emplace_back(point0, point1);
                triangle[1] = point0 - point1;
                end.clear(); // 现在是原点(0,0)了
                start = Collision::edge_direciton(triangle[0], triangle[1], false);

                while (true)
                {
                    if (start.x == 0)
                    {
                        start.x = 1;
                    }
                    if (start.y == 0)
                    {
                        start.y = 1;
                    }
                    Collision::gjk_furthest_point(points0, start, end, point0);
                    Collision::gjk_furthest_point(points1, end, start, point1);
                    point_pairs.emplace_back(point0, point1);
                    triangle[2] = point0 - point1;

                    if (triangle[2] * (point0 - point1) < 0)
                    {
                        return -1;
                    }

                    if (Geometry::is_inside(end, triangle))
                    {
                        break;
                    }
                    else if (last_triangle[0] == triangle[0] && last_triangle[1] == triangle[1]
                        && last_triangle[2] == triangle[2])
                    {
                        return -1;
                    }

                    distance[0] = Geometry::distance_square(end, triangle[0], triangle[1]);
                    distance[1] = Geometry::distance_square(end, triangle[1], triangle[2]);
                    distance[2] = Geometry::distance_square(end, triangle[0], triangle[2]);
                    last_triangle = triangle;
                    if (distance[0] <= distance[1])
                    {
                        if (distance[0] > distance[2])
                        {
                            triangle[1] = triangle[2];
                            point_pairs[1] = point_pairs[2];
                        }
                    }
                    else
                    {
                        if (distance[1] <= distance[2])
                        {
                            triangle[0] = triangle[2];
                            point_pairs[0] = point_pairs[2];
                        }
                        else
                        {
                            triangle[1] = triangle[2];
                            point_pairs[1] = point_pairs[2];
                        }
                    }
                    start = Collision::edge_direciton(triangle[0], triangle[1], false);
                    point_pairs.pop_back();
                }

                std::vector<Geometry::Point> points;
                points.emplace_back(triangle[0]);
                points.emplace_back(triangle[1]);
                points.emplace_back(triangle[2]);

                if (Geo::is_on_left(points[2], points[0], points[1]))
                {
                    std::reverse(points.begin(), points.end());
                }

                size_t index;
                while (true)
                {
                    distance[0] = Geometry::distance_square(end, points.front(), points.back());
                    index = points.size();
                    for (size_t i = 1, count = points.size(); i < count; ++i)
                    {
                        distance[1] = Geometry::distance_square(end, points[i - 1], points[i]);
                        if (distance[1] < distance[0])
                        {
                            distance[0] = distance[1];
                            index = i;
                        }
                    }

                    head = Collision::edge_direciton(points[index - 1], points[index % points.size()], false);
                    Collision::gjk_furthest_point(points0, end, head, point0);
                    Collision::gjk_furthest_point(points1, head, end, point1);
                    point2 = point0 - point1;
                    if (head * point2 <= 0 || points[index - 1] == point2 || points[index % points.size()] == point2)
                    {
                        break;
                    }
                    else
                    {
                        if (std::find(points.begin(), points.end(), point2) == points.end())
                        {
                            if (index < points.size())
                            {
                                points.insert(points.begin() + index, point2);
                                point_pairs.insert(point_pairs.begin(), std::make_tuple(point0, point1));
                            }
                            else
                            {
                                points.emplace_back(point2);
                                point_pairs.emplace_back(point0, point1);
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                distance[0] = Geo::distance_square(end, points.front(), points.back());
                index = points.size();
                for (size_t i = 1, count = points.size(); i < count; ++i)
                {
                    distance[1] = Geo::distance_square(end, points[i - 1], points[i]);
                    if (distance[1] < distance[0])
                    {
                        distance[0] = distance[1];
                        index = i;
                    }
                }
                return Geometry::distance(std::get<0>(point_pairs[index - 1]), std::get<0>(point_pairs[index % points.size()]),
                            std::get<1>(point_pairs[index - 1]), std::get<1>(point_pairs[index % points.size()]), head, tail);
            }

            double epa(const Geometry::Circle &circle0, const Geometry::Circle &circle1, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::Circle &circle, const Geometry::Polygon &polygon, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::Circle &circle, const Geometry::Rectangle &rectangle, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::Circle &circle, const Geometry::AABBRect &rectangle, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::Circle &circle, const Geometry::Square &square, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::Circle &circle, const Geometry::Triangle &triangle, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::Polygon &polygon, const Geometry::Circle &circle, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::Rectangle &rectangle, const Geometry::Circle &circle, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::AABBRect &rectangle, const Geometry::Circle &circle, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::Square &square, const Geometry::Circle &circle, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::Triangle &triangle, const Geometry::Circle &circle, Geometry::Point &head, Geometry::Point &tail);

            double epa(const Geometry::GeometryObject *points0, const Geometry::GeometryObject *points1, Geometry::Point &head, Geometry::Point &tail);


            template <typename L, typename R>
            double epa(const L &points0, const R &points1, const double tx, const double ty, Geometry::Vector &vec)
            {
                if constexpr (std::is_same_v<L, Geometry::Circle> || std::is_same_v<R, Geometry::Circle>)
                {
                    return Collision::epa(points0, points1, vec);
                }

                Geometry::Point start = points0.average_point(), end = points1.average_point();
                Geometry::Point point0, point1, point2;
                Geometry::Triangle triangle, last_triangle;
                double distance[3] = {DBL_MAX, DBL_MAX, DBL_MAX};

                if (start.x == end.x)
                {
                    start.x += 1;
                }
                if (start.y == end.y)
                {
                    start.y += 1;
                }
                Collision::gjk_furthest_point(points0, start, end, point0);
                Collision::gjk_furthest_point(points1, end, start, point1);
                triangle[0] = point0 - point1;
                Collision::gjk_furthest_point(points0, end, start, point0);
                Collision::gjk_furthest_point(points1, start, end, point1);
                triangle[1] = point0 - point1;
                end.clear(); // 现在是原点(0,0)了
                start = Collision::edge_direciton(triangle[0], triangle[1], false);

                while (true)
                {
                    if (start.x == 0)
                    {
                        start.x = 1;
                    }
                    if (start.y == 0)
                    {
                        start.y = 1;
                    }
                    Collision::gjk_furthest_point(points0, start, end, point0);
                    Collision::gjk_furthest_point(points1, end, start, point1);
                    triangle[2] = point0 - point1;

                    if (triangle[2] * (point0 - point1) < 0)
                    {
                        return -1;
                    }

                    if (Geometry::is_inside(end, triangle))
                    {
                        break;
                    }
                    else if (last_triangle[0] == triangle[0] && last_triangle[1] == triangle[1]
                        && last_triangle[2] == triangle[2])
                    {
                        return -1;
                    }

                    distance[0] = Geometry::distance_square(end, triangle[0], triangle[1]);
                    distance[1] = Geometry::distance_square(end, triangle[1], triangle[2]);
                    distance[2] = Geometry::distance_square(end, triangle[0], triangle[2]);
                    last_triangle = triangle;
                    if (distance[0] <= distance[1])
                    {
                        if (distance[0] > distance[2])
                        {
                            triangle[1] = triangle[2];
                        }
                    }
                    else
                    {
                        if (distance[1] <= distance[2])
                        {
                            triangle[0] = triangle[2];
                        }
                        else
                        {
                            triangle[1] = triangle[2];
                        }
                    }
                    start = Collision::edge_direciton(triangle[0], triangle[1], false);
                }

                std::vector<Geometry::Point> points;
                points.emplace_back(triangle[0]);
                points.emplace_back(triangle[1]);
                points.emplace_back(triangle[2]);

                if (Geo::is_on_left(points[2], points[0], points[1]))
                {
                    std::reverse(points.begin(), points.end());
                }

                size_t index;
                while (true)
                {
                    distance[0] = Geometry::distance_square(end, points.front(), points.back());
                    index = points.size();
                    for (size_t i = 1, count = points.size(); i < count; ++i)
                    {
                        distance[1] = Geometry::distance_square(end, points[i - 1], points[i]);
                        if (distance[1] < distance[0])
                        {
                            distance[0] = distance[1];
                            index = i;
                        }
                    }

                    vec = Collision::edge_direciton(points[index - 1], points[index % points.size()], false);
                    Collision::gjk_furthest_point(points0, end, vec, point0);
                    Collision::gjk_furthest_point(points1, vec, end, point1);
                    point2 = point0 - point1;
                    if (vec * point2 <= 0 || points[index - 1] == point2 || points[index % points.size()] == point2)
                    {
                        break;
                    }
                    else
                    {
                        if (std::find(points.begin(), points.end(), point2) == points.end())
                        {
                            if (index < points.size())
                            {
                                points.insert(points.begin() + index, point2);
                            }
                            else
                            {
                                points.emplace_back(point2);
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            
                distance[0] = Geo::distance_square(end, points.front(), points.back());
                index = points.size();
                std::vector<size_t> indexs;
                for (size_t i = 1, count = points.size(); i < count; ++i)
                {
                    distance[1] = Geo::distance_square(end, points[i - 1], points[i]);
                    if (distance[1] < distance[0])
                    {
                        distance[0] = distance[1];
                        index = i;
                        indexs.clear();
                    }
                    else if (distance[0] == distance[1])
                    {
                        indexs.push_back(i);
                    }
                }
                if (!Geo::foot_point(points[index - 1], points[index % points.size()], end, vec))
                {
                    if (Geo::distance_square(end, points[index - 1]) <= Geo::distance_square(end, points[index % points.size()]))
                    {
                        vec = points[index - 1];
                    }
                    else
                    {
                        vec = points[index % points.size()];
                    }
                }
                if (!indexs.empty())
                {
                    distance[0] = vec.x * tx + vec.y * ty;
                    for (const size_t i : indexs)
                    {
                        if (!Geo::foot_point(points[i - 1], points[i % points.size()], end, point2))
                        {
                            if (Geo::distance_square(end, points[i - 1]) <=
                                Geo::distance_square(end, points[i % points.size()]))
                            {
                                point2 = points[i - 1];
                            }
                            else
                            {
                                point2 = points[i % points.size()];
                            }
                        }
                        distance[1] = point2.x * tx + point2.y * ty;
                        if (distance[1] > distance[0])
                        {
                            distance[0] = distance[1];
                            vec = point2;
                        }
                    }
                }

                return vec.length();
            }
        
            double epa(const Geometry::Circle &circle0, const Geometry::Circle &circle1, const double tx, const double ty, Geometry::Vector &vec);

            double epa(const Geometry::GeometryObject *points0, const Geometry::GeometryObject *points1, const double tx, const double ty, Geometry::Vector &vec);
        }
    }
}