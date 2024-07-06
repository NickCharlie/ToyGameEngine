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
        Spirits::ShapedSpirit<Geometry::GeometryObject>* sp = dynamic_cast<Spirits::ShapedSpirit<Geometry::GeometryObject>*>(_group[i]);
        if (!sp) 
        {
            std::cout << "nulllptr" << std::endl;
        }
    }
}