#pragma once

#include "Player.hpp"
#include <vector>

namespace ToyGameEngine
{

    namespace Spirits
    {

        class SpiritGroup
        {
        private:
            std::vector<Spirits::Spirit *> _objects;
            bool _visible = true;

        public:
            SpiritGroup();
            SpiritGroup(const SpiritGroup &group);
            SpiritGroup(const std::initializer_list<Spirits::Spirit *> &objs);
            SpiritGroup(std::vector<Spirits::Spirit *>::const_iterator begin, std::vector<Spirits::Spirit *>::const_iterator end);

            ~SpiritGroup();

            void update();

            const bool &visible() const;

            void show();
            void hide();

            SpiritGroup *clone() const;
            void clone(SpiritGroup &group);

            SpiritGroup &operator=(const SpiritGroup &group);

            std::vector<Spirits::Spirit *>::iterator begin();

            std::vector<Spirits::Spirit *>::const_iterator begin() const;

            std::vector<Spirits::Spirit *>::const_iterator cbegin() const;

            std::vector<Spirits::Spirit *>::iterator end();

            std::vector<Spirits::Spirit *>::const_iterator end() const;

            std::vector<Spirits::Spirit *>::const_iterator cend() const;

            std::vector<Spirits::Spirit *>::reverse_iterator rbegin();

            std::vector<Spirits::Spirit *>::const_reverse_iterator rbegin() const;

            std::vector<Spirits::Spirit *>::const_reverse_iterator crbegin() const;

            std::vector<Spirits::Spirit *>::reverse_iterator rend();

            std::vector<Spirits::Spirit *>::const_reverse_iterator rend() const;

            std::vector<Spirits::Spirit *>::const_reverse_iterator crend() const;

            Spirits::Spirit *operator[](const size_t index);

            const Spirits::Spirit *operator[](const size_t index) const;

            void clear();

            const size_t size() const;

            void append(SpiritGroup *container);

            void append(Spirits::Spirit *object);

            void append(SpiritGroup &group, const bool merge = true);

            void insert(const size_t index, Spirits::Spirit *object);

            std::vector<Spirits::Spirit *>::iterator remove(const size_t index);

            std::vector<Spirits::Spirit *>::iterator remove(const std::vector<Spirits::Spirit *>::iterator &it);

            std::vector<Spirits::Spirit *>::iterator remove(const std::vector<Spirits::Spirit *>::reverse_iterator &it);

            Spirits::Spirit *pop(const size_t index);

            Spirits::Spirit *pop(const std::vector<Spirits::Spirit *>::iterator &it);

            Spirits::Spirit *pop(const std::vector<Spirits::Spirit *>::reverse_iterator &it);

            Spirits::Spirit *pop_front();

            Spirits::Spirit *pop_back();

            const bool empty() const;

            Spirits::Spirit *front();

            const Spirits::Spirit *front() const;

            Spirits::Spirit *back();

            const Spirits::Spirit *back() const;

            void remove_front();

            void remove_back();
        };

    }

}
