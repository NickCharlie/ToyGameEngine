#pragma once
#include <vector>
#include <utility>
#include "Math/Geometry/AABBRect.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Geometry
        {
            namespace Collision
            {
                class GridNode
                {
                protected:
                    AABBRect _rect;
                    std::vector<GeometryObject *> _objects;

                public:
                    GridNode();

                    GridNode(const AABBRect &rect);

                    GridNode(const double left, const double top, const double right, const double bottom);

                    void set_rect(const AABBRect &rect);

                    const AABBRect &rect() const;

                    bool append(GeometryObject *object);

                    bool remove(GeometryObject *object);

                    bool has(GeometryObject *object) const;

                    void clear();

                    bool select(const Point &pos, std::vector<GeometryObject *> &objects) const;

                    bool select(const AABBRect &rect, std::vector<GeometryObject *> &objects) const;

                    bool find_collision_objects(const GeometryObject *object, std::vector<GeometryObject *> &objects, const bool infinite = false, const bool inside = true) const;

                    bool find_collision_pairs(std::vector<std::pair<GeometryObject *, GeometryObject *>> &pairs, const bool infinite = false, const bool inside = true) const;
                };
            
                class GridMap
                {
                private:
                    std::vector<GridNode> _grids;
                    std::vector<GeometryObject *> _objects;
                    std::vector<AABBRect> _rects;
                    double _left, _top, _right, _bottom;

                public:
                    GridMap();

                    GridMap(const std::vector<GeometryObject *> &objects);

                    GridMap(const std::initializer_list<GeometryObject *> &objects);

                    GridMap(const std::vector<GeometryObject *>::const_iterator &begin, const std::vector<GeometryObject *>::const_iterator &end);

                    void build(const std::vector<GeometryObject *> &objects);

                    void build(const std::vector<GeometryObject *>::const_iterator &begin, const std::vector<GeometryObject *>::const_iterator &end);

                    void build(const std::vector<GeometryObject *> &objects, const std::vector<AABBRect> &rects);

                    void append(GeometryObject *object);

                    void remove(GeometryObject *object);

                    void update(GeometryObject *object);

                    void update();

                    bool has(GeometryObject *object) const;

                    void clear();

                    bool select(const Point &pos, std::vector<GeometryObject *> &objects) const;

                    bool select(const AABBRect &rect, std::vector<GeometryObject *> &objects) const;

                    bool find_collision_objects(const GeometryObject *object, std::vector<GeometryObject *> &objects,  const bool infinite = false, const bool inside = true) const;

                    bool find_collision_pairs(std::vector<std::pair<GeometryObject *, GeometryObject *>> &pairs, const bool infinite = false, const bool inside = true) const;
                };

                class QuadTreeNode : public GridNode
                {
                private:
                    QuadTreeNode *_nodes[4] = {nullptr};

                    void split();

                    bool is_tail_node() const;

                    bool merge();
                
                public:
                    QuadTreeNode();

                    QuadTreeNode(const AABBRect &rect);

                    QuadTreeNode(const double left, const double top, const double right, const double bottom);

                    ~QuadTreeNode();

                    bool append(GeometryObject *object);

                    void append_node(const size_t index, QuadTreeNode *node);

                    bool remove(GeometryObject *object);

                    bool has(GeometryObject *object) const;

                    void clear();

                    bool select(const Point &pos, std::vector<GeometryObject *> &objects) const;

                    bool select(const AABBRect &rect, std::vector<GeometryObject *> &objects) const;

                    bool find_collision_objects(const GeometryObject *object, std::vector<GeometryObject *> &objects, const bool infinite = false, const bool inside = true) const;

                    bool find_collision_pairs(std::vector<std::pair<GeometryObject *, GeometryObject *>> &pairs, const bool infinite = false, const bool inside = true) const;
                };
            
                class QuadTree
                {
                private:
                    QuadTreeNode *_root = nullptr;
                    std::vector<GeometryObject *> _objects;
                    std::vector<AABBRect> _rects;
                    double _left, _top, _right, _bottom;

                public:
                    QuadTree();

                    QuadTree(const std::vector<GeometryObject *> &objects);

                    QuadTree(const std::initializer_list<GeometryObject *> &objects);

                    QuadTree(const std::vector<GeometryObject *>::const_iterator &begin, const std::vector<GeometryObject *>::const_iterator &end);

                    ~QuadTree();

                    void build(const std::vector<GeometryObject *> &objects);

                    void build(const std::vector<GeometryObject *>::const_iterator &begin, const std::vector<GeometryObject *>::const_iterator &end);

                    void build(const std::vector<GeometryObject *> &objects, const std::vector<AABBRect> &rects);

                    void append(GeometryObject *object);

                    void remove(GeometryObject *object);

                    void update(GeometryObject *object);

                    void update();

                    bool has(GeometryObject *object) const;

                    void clear();

                    bool select(const Point &pos, std::vector<GeometryObject *> &objects) const;

                    bool select(const AABBRect &rect, std::vector<GeometryObject *> &objects) const;

                    bool find_collision_objects(const GeometryObject *object, std::vector<GeometryObject *> &objects, const bool infinite = false, const bool inside = true) const;

                    bool find_collision_pairs(std::vector<std::pair<GeometryObject *, GeometryObject *>> &pairs, const bool infinite = false, const bool inside = true) const;
                };

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
}