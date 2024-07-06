#pragma once
#include "Spirit/SpiritGroup.hpp"

namespace ToyGameEngine 
{
    namespace Scenes
    {
        class Scene
        {
        public:
            Scene();
            Scene(Spirits::SpiritGroup& group);

            void update();

            Spirits::SpiritGroup& get_group();
        private:
            Spirits::SpiritGroup _group;
        };
    }
}