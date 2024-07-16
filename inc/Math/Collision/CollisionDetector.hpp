#pragma once

#include <deque>
#include "Math/Collision/GridMap.hpp"
#include "Math/Collision/QuadTree.hpp"
#include "Math/Collision/DirectMode.hpp"

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

                static bool pair_in_pairs(const std::vector<std::pair<Geo::Geometry *, Geo::Geometry *>> &pairs, const Geo::Geometry *object0, const Geo::Geometry *object1, const bool ordered = false)
                {
                    if (ordered)
                    {
                        for (const std::pair<Geo::Geometry *, Geo::Geometry *> &pair : pairs)
                        {
                            if (pair.first == object0 && pair.second == object1)
                            {
                                return true;
                            }
                        }
                    }
                    else
                    {
                        for (const std::pair<Geo::Geometry *, Geo::Geometry *> &pair : pairs)
                        {
                            if ((pair.first == object0 && pair.second == object1) || 
                                (pair.first == object1 && pair.second == object0))
                            {
                                return true;
                            }
                        }
                    }
                    return false;
                }

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

                bool find_collision_objects(const GeometryObject *object, std::vector<GeometryObject *> &objects, const bool norepeat = true) const
                {
                    return _detector.find_collision_objects(object, objects, norepeat);
                }

                bool find_collision_pairs(std::vector<std::pair<GeometryObject *, GeometryObject *>> &pairs, const bool norepeat = true) const
                {
                    return _detector.find_collision_pairs(pairs, norepeat);
                }

                void collision_translate(Geometry::GeometryObject *object, const double tx, const double ty)
                {
                    std::deque<Geometry::GeometryObject *> crushed_objects({object});
                    std::vector<std::pair<Geometry::GeometryObject *, Geometry::GeometryObject *>> moved_object_pairs;
                    std::vector<Geometry::GeometryObject *> current_objects;
                    Geometry::Vector vec;
                    while (!crushed_objects.empty())
                    {
                        object = crushed_objects.back();
                        crushed_objects.pop_back();
                        if (_detector.find_collision_objects(object, current_objects))
                        {
                            for (Geometry::GeometryObject *current_object : current_objects)
                            {
                                if (pair_in_pairs(moved_object_pairs, object, crushed_objects[i], true))
                                {
                                    continue;
                                }

                                moved_object_pairs.emplace_back(object, current_object);
                                if (Collision::epa(object, current_object, tx, ty, vec) > 0)
                                {
                                    if (vec.x * tx + vec.y * ty > 0)
                                    {
                                        current_object->translate(vec.x, vec.y);
                                        _detector.update(current_object);
                                        current_objects.push_back(current_object);
                                    }
                                    vec.clear();
                                }
                            }
                            current_objects.clear();
                        }
                    }
                }
            };
        }
    }
}