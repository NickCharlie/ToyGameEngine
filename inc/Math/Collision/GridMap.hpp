#pragma once

#include "Math/Geometry/AABBRect.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Collision
        {
            class GridNode
            {
            protected:
                Geometry::AABBRect _rect;
                std::vector<Geometry::GeometryObject *> _objects;

            public:
                GridNode();

                GridNode(const Geometry::AABBRect &rect);

                GridNode(const double left, const double top, const double right, const double bottom);

                void set_rect(const Geometry::AABBRect &rect);

                const Geometry::AABBRect &rect() const;

                bool append(Geometry::GeometryObject *object);

                bool remove(Geometry::GeometryObject *object);

                bool has(Geometry::GeometryObject *object) const;

                void clear();

                bool select(const Geometry::Point &pos, std::vector<Geometry::GeometryObject *> &objects) const;

                bool select(const Geometry::AABBRect &rect, std::vector<Geometry::GeometryObject *> &objects) const;

                bool find_collision_objects(const Geometry::GeometryObject *object, std::vector<Geometry::GeometryObject *> &objects) const;

                bool find_collision_pairs(std::vector<std::pair<Geometry::GeometryObject *, Geometry::GeometryObject *>> &pairs) const;
            };

            class GridMap
            {
            private:
                std::vector<GridNode> _grids;
                std::vector<Geometry::GeometryObject *> _objects;
                std::vector<Geometry::AABBRect> _rects;
                double _left, _top, _right, _bottom;

            public:
                GridMap();

                GridMap(const std::vector<Geometry::GeometryObject *> &objects);

                GridMap(const std::initializer_list<Geometry::GeometryObject *> &objects);

                GridMap(const std::vector<Geometry::GeometryObject *>::const_iterator &begin, const std::vector<Geometry::GeometryObject *>::const_iterator &end);

                void build(const std::vector<Geometry::GeometryObject *> &objects);

                void build(const std::vector<Geometry::GeometryObject *>::const_iterator &begin, const std::vector<Geometry::GeometryObject *>::const_iterator &end);

                void build(const std::vector<Geometry::GeometryObject *> &objects, const std::vector<Geometry::AABBRect> &rects);

                void append(Geometry::GeometryObject *object);

                void remove(Geometry::GeometryObject *object);

                void update(Geometry::GeometryObject *object);

                void update();

                bool has(Geometry::GeometryObject *object) const;

                void clear();

                bool select(const Geometry::Point &pos, std::vector<Geometry::GeometryObject *> &objects) const;

                bool select(const Geometry::AABBRect &rect, std::vector<Geometry::GeometryObject *> &objects) const;

                bool find_collision_objects(const Geometry::GeometryObject *object, std::vector<Geometry::GeometryObject *> &objects, const bool norepeat = true) const;

                bool find_collision_pairs(std::vector<std::pair<Geometry::GeometryObject *, Geometry::GeometryObject *>> &pairs, const bool norepeat = true) const;
            };
        }
    }
}