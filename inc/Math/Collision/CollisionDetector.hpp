#pragma once

#include "Math/Collision/GridMap.hpp"
#include "Math/Collision/QuadTree.hpp"

namespace ToyGameEngine
{
    namespace Math
    {
        namespace Collision
        {
            template <typename T = GridMap>
            class CollisionDetector
            {
            private:
                T _detector;

            public:
                CollisionDetector() {}

                CollisionDetector(const std::vector<GeometryObject *>::const_iterator &begin, const std::vector<GeometryObject *>::const_iterator &end)
                    : _detector(begin, end) {}

                CollisionDetector(const std::vector<GeometryObject *> &objects)
                    : _detector(objects) {}

                CollisionDetector(const std::initializer_list<GeometryObject *> &objects)
                    : _detector(objects) {}

                void build(const ContainerGroup &group)
                {
                    return _detector.build(group);
                }

                void build(const std::vector<GeometryObject *> &objects)
                {
                    return _detector.build(objects);
                }

                void build(const std::vector<GeometryObject *>::const_iterator &begin, const std::vector<GeometryObject *>::const_iterator &end)
                {
                    return _detector.build(begin, end);
                }

                void build(const std::vector<GeometryObject *> &objects, const std::vector<AABBRect> &rects)
                {
                    return _detector.build(objects, rects);
                }

                void append(GeometryObject *object)
                {
                    return _detector.append(object);
                }

                void remove(GeometryObject *object)
                {
                    return _detector.remove(object);
                }

                void update(GeometryObject *object)
                {
                    return _detector.update(object);
                }

                void update()
                {
                    return _detector.update();
                }

                bool has(GeometryObject *object) const
                {
                    return _detector.has(object);
                }

                void clear()
                {
                    return _detector.clear();
                }

                bool select(const Point &pos, std::vector<GeometryObject *> &objects) const
                {
                    return _detector.select(pos, objects);
                }

                bool select(const AABBRect &rect, std::vector<GeometryObject *> &objects) const
                {
                    return _detector.select(rect, objects);
                }

                bool find_collision_objects(const GeometryObject *object, std::vector<GeometryObject *> &objects, const bool infinite = false, const bool inside = true) const
                {
                    return _detector.find_collision_objects(object, objects, infinite, inside);
                }

                bool find_collision_pairs(std::vector<std::pair<GeometryObject *, GeometryObject *>> &pairs, const bool infinite = false, const bool inside = true) const
                {
                    return _detector.find_collision_pairs(pairs, infinite, inside);
                }
            };
        }
    }
}