#pragma once

#include "Math/Geometry/GeometryObject.hpp"


namespace ToyGameEngine {
    
    namespace Canvas {
        
        class GeometryGroup {
        private:
            std::vector<Math::Geometry::GeometryObject*> _objects;
            bool _visible = true;
        public:
            GeometryGroup();
            GeometryGroup(const GeometryGroup& group);
            GeometryGroup(const std::initializer_list<Math::Geometry::GeometryObject*>& groups);
            GeometryGroup(std::vector<Math::Geometry::GeometryObject*>::const_iterator begin, std::vector<Math::Geometry::GeometryObject*>::const_iterator end);

            ~GeometryGroup();

            const bool& visible() const;

            void show();
            void hide();

            GeometryGroup* clone() const;
            void transfer(GeometryGroup& group);

            GeometryGroup &operator=(const GeometryGroup &group);

            std::vector<Math::Geometry::GeometryObject*>::iterator begin();

            std::vector<Math::Geometry::GeometryObject*>::const_iterator begin() const;

            std::vector<Math::Geometry::GeometryObject*>::const_iterator cbegin() const;

            std::vector<Math::Geometry::GeometryObject*>::iterator end();

            std::vector<Math::Geometry::GeometryObject*>::const_iterator end() const;

            std::vector<Math::Geometry::GeometryObject*>::const_iterator cend() const;

            std::vector<Math::Geometry::GeometryObject*>::reverse_iterator rbegin();

            std::vector<Math::Geometry::GeometryObject*>::const_reverse_iterator rbegin() const;

            std::vector<Math::Geometry::GeometryObject*>::const_reverse_iterator crbegin() const;

            std::vector<Math::Geometry::GeometryObject*>::reverse_iterator rend();

            std::vector<Math::Geometry::GeometryObject*>::const_reverse_iterator rend() const;

            std::vector<Math::Geometry::GeometryObject*>::const_reverse_iterator crend() const;

            Math::Geometry::GeometryObject* operator[](const size_t index);

            void clear();

            const size_t size() const;

            void append(GeometryGroup* container);

            void append(Math::Geometry::Polyline* polyline);

            void append(Math::Geometry::AABBRect* rect);

            void append(Math::Geometry::Circle* circle);

            void append(Math::Geometry::Polygon* polygon);

            void append(Math::Geometry::Line* line);

            void append(Math::Geometry::Triangle* triangle);

            void append(Math::Geometry::Point* point);

            void append(GeometryGroup &group, const bool merge = true);

            void insert(const size_t index, GeometryGroup *container);

            void insert(const size_t index, Math::Geometry::Polyline *polyline);

            void insert(const size_t index, Math::Geometry::Bezier *bezier);

            std::vector<Math::Geometry::GeometryObject*>::iterator remove(const size_t index);

            std::vector<Math::Geometry::GeometryObject*>::iterator remove(const std::vector<Math::Geometry::GeometryObject*>::iterator &it);

            std::vector<Math::Geometry::GeometryObject*>::iterator remove(const std::vector<Math::Geometry::GeometryObject*>::reverse_iterator &it);

            Math::Geometry::GeometryObject* pop(const size_t index);

            Math::Geometry::GeometryObject* pop(const std::vector<Math::Geometry::GeometryObject*>::iterator &it);

            Math::Geometry::GeometryObject* pop(const std::vector<Math::Geometry::GeometryObject*>::reverse_iterator &it);

            Math::Geometry::GeometryObject* pop_front();

            Math::Geometry::GeometryObject* pop_back();

            const bool empty() const;

            Math::Geometry::GeometryObject* front();

            const Math::Geometry::GeometryObject* front() const;

            Math::Geometry::GeometryObject* back();

            const Math::Geometry::GeometryObject* back() const;

            void remove_front();

            void remove_back();
        }; 

    }
    
}

