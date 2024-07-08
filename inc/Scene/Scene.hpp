#pragma once
#include "Spirit/SpiritGroup.hpp"
#include "Math/Geometry/AABBRect.hpp"


namespace ToyGameEngine 
{
    namespace Scenes
    {
        class Scene
        {
        public:
            Scene();

            void update();

            std::vector<Spirits::SpiritGroup> &groups();

            const std::vector<Spirits::SpiritGroup> &groups() const;

            void set_viewport(double left, double top, double right, double bottom);

            bool is_visible(const Spirits::Spirit *spirit) const;

        private:
            std::vector<Spirits::SpiritGroup> _groups;

            Math::Geometry::AABBRect _viewport;
        };
    }
}