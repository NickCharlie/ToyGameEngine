#pragma once

#include <queue>
#include <functional>
#include "Spirit/SpiritGroup.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Scene/Event.hpp"


namespace ToyGameEngine 
{
    namespace Scenes
    {
        class Scene
        {
        public:
            Scene();

            void load_canvas(std::function<void()> func);

            void update();

            std::vector<Spirits::SpiritGroup> &groups();

            const std::vector<Spirits::SpiritGroup> &groups() const;

            void set_viewport(double left, double top, double right, double bottom);

            bool is_visible(const Spirits::Spirit *spirit) const;

            void append_event(Event *event);

            void respond_events();

            void start();

            void stop();

        private:
            void run();

        private:
            std::vector<Spirits::SpiritGroup> _groups;

            Math::Geometry::AABBRect _viewport;

            std::queue<Event *> _events;

            bool _is_running = false;

            std::function<void()> _canvas_update;
        };
    }
}