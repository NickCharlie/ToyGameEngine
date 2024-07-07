#include "Scene/Scene.hpp"
#include "Canvas/Canvas.hpp"
#include "Canvas/CanvasT.hpp"

using namespace ToyGameEngine::Scenes;
using namespace ToyGameEngine::Spirits;
using namespace ToyGameEngine::Canvas;
using namespace ToyGameEngine::Math;

Scene::Scene()
{

}

Scene::Scene(SpiritGroup& group)
{
    for(size_t i = 0; i < group.size(); ++i) 
    {
        _group.append(group[i]->clone());
    }
}

SpiritGroup& Scene::get_group()
{
    return _group;
}

void Scene::update()
{
    ICanvas canvas;
    for(size_t i = 0; i < _group.size(); ++i) 
    {
        // 这里不知道如何写 TODO
        Spirits::Spirit* sp = _group[i];
        if (!sp) 
        {
            return;
        }

        switch (sp->type())
        {
        case Geometry::Type::POLYGON:
            // canvas.draw_polygon(painter, static_cast<ShapedSpirit<Geometry::Polygon> *>(sp)->shape());
            break;
        case Geometry::Type::CIRCLE:
            // canvas.draw_circle(painter, static_cast<ShapedSpirit<Geometry::Circle> *>(sp)->shape());
            break;
        case Geometry::Type::AABBRECT:
            // canvas.draw_rect(painter, static_cast<ShapedSpirit<Geometry::AABBRect> *>(sp)->shape());
            break;
        case Geometry::Type::TRIANGLE:
            // canvas.draw_triangle(painter, static_cast<ShapedSpirit<Geometry::Triangle> *>(sp)->shape());
            break;
        }

    }
}