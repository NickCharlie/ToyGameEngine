#pragma once

#include <queue>
#include <functional>
#include "Spirit/SpiritGroup.hpp"
#include "BackGround/BackGroundGroup.hpp"
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

            std::vector<BackGrounds::BackGroundGroup> &background_groups();

            const std::vector<Spirits::SpiritGroup> &groups() const;

            const std::vector<BackGrounds::BackGroundGroup> &background_groups() const;

            void append_spiritgroup();

            void append_spiritgroup(Spirits::SpiritGroup &group);

            void set_viewport(double left, double top, double right, double bottom);

            bool is_visible(const Spirits::Spirit *spirit) const;

            void append_event(IOEvent *event);

            void append_event(Event *event);

            void respond_events();

            void respond_internal_events();

            void start();

            void stop();

        private:
            void run();

        private:
            std::vector<Spirits::SpiritGroup> _groups;
            std::vector<BackGrounds::BackGroundGroup> _backgroung_groups;

            Math::Geometry::AABBRect _viewport;

            std::queue<IOEvent *> _io_events;
            std::queue<Event *> _internal_events;

            bool _is_running = false;

            std::function<void()> _canvas_update;
        };
    }
}