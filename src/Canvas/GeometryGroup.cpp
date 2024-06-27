#include "Canvas/GeometryGroup.hpp"

using namespace ToyGameEngine::Canvas;

GeometryGroup::GeometryGroup() {

}

GeometryGroup::GeometryGroup(const GeometryGroup& group) {

}

GeometryGroup::GeometryGroup(const std::initializer_list<Math::Geometry::GeometryObject*>& groups)
 : _objects(groups.begin(), groups.end()) {

}

GeometryGroup::GeometryGroup(std::vector<Math::Geometry::GeometryObject*>::const_iterator begin, std::vector<Math::Geometry::GeometryObject*>::const_iterator end)
 : _objects(begin, end){

}