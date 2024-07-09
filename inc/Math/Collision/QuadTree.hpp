#pragma once

#include "Math/Collision/GridMap.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Collision
        {
            class QuadTreeNode : public GridNode
            {
            private:
                QuadTreeNode *_nodes[4] = {nullptr};

                void split();

                bool is_tail_node() const;

                bool merge();
            
            public:
                QuadTreeNode();

                QuadTreeNode(const Geometry::AABBRect &rect);

                QuadTreeNode(const double left, const double top, const double right, const double bottom);

                ~QuadTreeNode();

                bool append(Geometry::GeometryObject *object);

                void append_node(const size_t index, QuadTreeNode *node);

                bool remove(Geometry::GeometryObject *object);

                bool has(Geometry::GeometryObject *object) const;

                void clear();

                bool select(const Geometry::Point &pos, std::vector<Geometry::GeometryObject *> &objects) const;

                bool select(const Geometry::AABBRect &rect, std::vector<Geometry::GeometryObject *> &objects) const;

                bool find_collision_objects(const Geometry::GeometryObject *object, std::vector<Geometry::GeometryObject *> &objects) const;

                bool find_collision_pairs(std::vector<std::pair<Geometry::GeometryObject *, Geometry::GeometryObject *>> &pairs) const;
            };
            
            class QuadTree
            {
            private:
                QuadTreeNode *_root = nullptr;
                std::vector<Geometry::GeometryObject *> _objects;
                std::vector<Geometry::AABBRect> _rects;
                double _left, _top, _right, _bottom;

            public:
                QuadTree();

                QuadTree(const std::vector<Geometry::GeometryObject *> &objects);

                QuadTree(const std::initializer_list<Geometry::GeometryObject *> &objects);

                QuadTree(const std::vector<Geometry::GeometryObject *>::const_iterator &begin, const std::vector<Geometry::GeometryObject *>::const_iterator &end);

                ~QuadTree();

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

                bool find_collision_objects(const Geometry::GeometryObject *object, std::vector<Geometry::GeometryObject *> &objects) const;

                bool find_collision_pairs(std::vector<std::pair<Geometry::GeometryObject *, Geometry::GeometryObject *>> &pairs) const;
            };
        }
    }
}