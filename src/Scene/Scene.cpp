#include "Scene/Scene.hpp"
#include "Math/Geometry/Algorithm.hpp"

using namespace ToyGameEngine::Scenes;
using namespace ToyGameEngine::Spirits;
using namespace ToyGameEngine::Math;

Scene::Scene()
{
}

std::vector<SpiritGroup> &Scene::groups()
{
    return _groups;
}

const std::vector<SpiritGroup> &Scene::groups() const
{
    return _groups;
}

void Scene::update()
{
    for (SpiritGroup &group : _groups)
    {
        group.update();
    }
}

void Scene::set_viewport(double left, double top, double right, double bottom)
{
    if (left > right)
    {
        std::swap(left, right);
    }
    if (bottom > top)
    {
        std::swap(top, bottom);
    }
    _viewport.set_left(left);
    _viewport.set_top(top);
    _viewport.set_right(right);
    _viewport.set_bottom(bottom);
}

bool Scene::is_visible(const Spirit *spirit) const
{
    if (spirit->visible())
    {
        switch (spirit->type())
        {
        case Geometry::Type::RECTANGLE:
            return Geometry::is_intersected(_viewport, static_cast<const ShapedSpirit<Geometry::Rectangle> *>(spirit)->shape());
        case Geometry::Type::SQUARE:
            return Geometry::is_intersected(_viewport, static_cast<const ShapedSpirit<Geometry::Square> *>(spirit)->shape());
        case Geometry::Type::AABBRECT:
            return Geometry::is_intersected(_viewport, static_cast<const ShapedSpirit<Geometry::AABBRect> *>(spirit)->shape());
        case Geometry::Type::CIRCLE:
            return Geometry::is_intersected(_viewport, static_cast<const ShapedSpirit<Geometry::Circle> *>(spirit)->shape());
        case Geometry::Type::POLYGON:
            return Geometry::is_intersected(_viewport, static_cast<const ShapedSpirit<Geometry::Polygon> *>(spirit)->shape());
        case Geometry::Type::POLYLINE:
            return Geometry::is_intersected(_viewport, static_cast<const ShapedSpirit<Geometry::Polyline> *>(spirit)->shape());
        case Geometry::Type::BEZIER:
            return Geometry::is_intersected(_viewport, static_cast<const ShapedSpirit<Geometry::Bezier> *>(spirit)->shape().shape());
        case Geometry::Type::POINT:
            return Geometry::is_inside(static_cast<const ShapedSpirit<Geometry::Point> *>(spirit)->shape(), _viewport, true);
        default:
            return false;
        }
    }
    else
    {
        return false;
    }
}