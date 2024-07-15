#include <thread>
#include <chrono>
#include "Scene/Scene.hpp"
#include "Spirit/ShapedSpirit.hpp"
#include "Math/Geometry/Algorithm.hpp"

using namespace ToyGameEngine::Scenes;
using namespace ToyGameEngine::Spirits;
using namespace ToyGameEngine::Math;

Scene::Scene()
{
}

void Scene::load_canvas(std::function<void()> func)
{
    _canvas_update = func;
}

std::vector<SpiritGroup> &Scene::groups()
{
    return _groups;
}

const std::vector<SpiritGroup> &Scene::groups() const
{
    return _groups;
}

void Scene::append_spiritgroup()
{
    _groups.emplace_back();
    _groups.back().load_event_queue(std::bind(static_cast<void(Scene::*)(Event *)>(&Scene::append_event),
        this, std::placeholders::_1));
}

void Scene::append_spiritgroup(Spirits::SpiritGroup &group)
{
    _groups.emplace_back();
    _groups.back().load_event_queue(std::bind(static_cast<void(Scene::*)(Event *)>(&Scene::append_event),
        this, std::placeholders::_1));
    _groups.back().append(group);
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

void Scene::append_event(IOEvent *event)
{
    _io_events.push(event);
}

void Scene::append_event(Event *event)
{
    _internal_events.push(event);
}

void Scene::respond_events()
{
    if (_io_events.empty() && _internal_events.empty())
    {
        return;
    }
    Event *event = nullptr;
    while (!_internal_events.empty())
    {
        event = _internal_events.front();
        _internal_events.pop();
        if (event->type() == Scenes::EventType::ACTION_EVENT)
        {
            static_cast<ActionEvent *>(event)->run();
        }
        else
        {
            for (Spirits::SpiritGroup &group : _groups)
            {
                group.update(event);
                if (!event->active)
                {
                    break;
                }
            }
        }
        delete event;
    }

    IOEvent *io_event = nullptr;
    while (!_io_events.empty())
    {
        io_event = _io_events.front();
        _io_events.pop();
        for (Spirits::SpiritGroup &group : _groups)
        {
            group.update(io_event);
            if (!io_event->active)
            {
                break;
            }
        }
        delete io_event;
    }
}

void Scene::respond_internal_events()
{
    if (_internal_events.empty())
    {
        return;
    }
    Event *event = nullptr;
    while (!_internal_events.empty())
    {
        event = _internal_events.front();
        _internal_events.pop();
        if (event->type() == Scenes::EventType::ACTION_EVENT)
        {
            static_cast<ActionEvent *>(event)->run();
        }
        else
        {
            for (Spirits::SpiritGroup &group : _groups)
            {
                group.update(event);
                if (!event->active)
                {
                    break;
                }
            }
        }
        delete event;
    }
}

void Scene::start()
{
    if (_is_running)
    {
        return;
    }

    _is_running = true;
    std::thread(&Scene::run, this).detach();
}

void Scene::stop()
{
    _is_running = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Scene::run()
{
    std::chrono::steady_clock::time_point start_point;
    while (_is_running)
    {
        start_point = std::chrono::steady_clock::now();
        respond_events();
        update();
        respond_internal_events();
        _canvas_update();
        std::this_thread::sleep_until(start_point + std::chrono::milliseconds(33));
    }
}