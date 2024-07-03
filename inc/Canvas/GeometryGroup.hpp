#pragma once
#include "Math/Geometry/Line.hpp"
#include "Math/Geometry/Point.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Bezier.hpp"
#include "Math/Geometry/Circle.hpp"
#include "Math/Geometry/Polygon.hpp"
#include "Math/Geometry/Polyline.hpp"
#include "Math/Geometry/Triangle.hpp"
#include "Math/Geometry/Square.hpp"
#include "Math/Geometry/Rectangle.hpp"
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
            GeometryGroup(const std::initializer_list<Math::Geometry::GeometryObject*>& objs);
            GeometryGroup(std::vector<Math::Geometry::GeometryObject*>::const_iterator begin, std::vector<Math::Geometry::GeometryObject*>::const_iterator end);

            ~GeometryGroup();

            const bool visible() const;

            void show();
            void hide();

            GeometryGroup* clone() const;
            void clone(GeometryGroup& group);

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

            const Math::Geometry::GeometryObject* operator[](const size_t index) const;

            void clear();

            const size_t size() const;

            void append(GeometryGroup* container);

            void append(Math::Geometry::GeometryObject* object);

            void append(GeometryGroup &group, const bool merge = true);

            void insert(const size_t index, Math::Geometry::GeometryObject* object);

            std::vector<Math::Geometry::GeometryObject*>::iterator remove(const size_t index);

            std::vector<Math::Geometry::GeometryObject*>::iterator remove(const std::vector<Math::Geometry::GeometryObject*>::iterator& it);

            std::vector<Math::Geometry::GeometryObject*>::iterator remove(const std::vector<Math::Geometry::GeometryObject*>::reverse_iterator& it);

            Math::Geometry::GeometryObject* pop(const size_t index);

            Math::Geometry::GeometryObject* pop(const std::vector<Math::Geometry::GeometryObject*>::iterator& it);

            Math::Geometry::GeometryObject* pop(const std::vector<Math::Geometry::GeometryObject*>::reverse_iterator& it);

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

