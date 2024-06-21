#include "Math/Geometry/GeometryObject.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Polygon.hpp"


using namespace ToyGameEngine::Math;

Geometry::GeometryObject::GeometryObject()
{

}

Geometry::GeometryObject::GeometryObject(const GeometryObject &object)
{

}

Geometry::GeometryObject::~GeometryObject()
{

}

Geometry::GeometryObject &Geometry::GeometryObject::operator=(const GeometryObject &object)
{
    return *this;
}

double Geometry::GeometryObject::length() const
{
    return 0;
}

bool Geometry::GeometryObject::empty() const
{
    return true;
}

void Geometry::GeometryObject::clear()
{

}

Geometry::GeometryObject *Geometry::GeometryObject::clone() const
{
    return new Geometry::GeometryObject(*this);
}

void Geometry::GeometryObject::transform(const double a, const double b, const double c, const double d, const double e, const double f)
{

}

void Geometry::GeometryObject::transform(const double mat[6])
{

}

void Geometry::GeometryObject::translate(const double tx, const double ty)
{

}

void Geometry::GeometryObject::rotate(const double x, const double y, const double rad)
{

}

void Geometry::GeometryObject::scale(const double x, const double y, const double k)
{

}

Geometry::Type Geometry::GeometryObject::type() const
{
    return Geometry::Type::GEOMETRY_OBJECT;
}

// 凸包
Geometry::Polygon Geometry::GeometryObject::convex_hull() const
{
    return Geometry::Polygon();
}

// 外接AABB矩形
Geometry::AABBRect Geometry::GeometryObject::bounding_rect() const
{
    return Geometry::AABBRect();
}

// 最小外接矩形
Geometry::Polygon Geometry::GeometryObject::mini_bounding_rect() const
{
    return Geometry::Polygon();
}