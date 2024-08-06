#pragma once
#include "Sounds/Sound.hpp"

namespace ToyGameEngine
{
    namespace Sounds
    {
        class SoundGroup
        {
        private:
            std::vector<Sounds::Sound *> _objects;

        public:
            SoundGroup();
            SoundGroup(const SoundGroup &group);
            SoundGroup(const std::initializer_list<Sounds::Sound *> &objs);
            SoundGroup(std::vector<Sounds::Sound *>::const_iterator begin, std::vector<Sounds::Sound *>::const_iterator end);

            virtual ~SoundGroup();

            SoundGroup *clone() const;
            void clone(SoundGroup &group);

            SoundGroup &operator=(const SoundGroup &group);

            std::vector<Sounds::Sound *>::iterator begin();

            std::vector<Sounds::Sound *>::const_iterator begin() const;

            std::vector<Sounds::Sound *>::const_iterator cbegin() const;

            std::vector<Sounds::Sound *>::iterator end();

            std::vector<Sounds::Sound *>::const_iterator end() const;

            std::vector<Sounds::Sound *>::const_iterator cend() const;

            std::vector<Sounds::Sound *>::reverse_iterator rbegin();

            std::vector<Sounds::Sound *>::const_reverse_iterator rbegin() const;

            std::vector<Sounds::Sound *>::const_reverse_iterator crbegin() const;

            std::vector<Sounds::Sound *>::reverse_iterator rend();

            std::vector<Sounds::Sound *>::const_reverse_iterator rend() const;

            std::vector<Sounds::Sound *>::const_reverse_iterator crend() const;

            Sounds::Sound *operator[](int index);

            const Sounds::Sound *operator[](int index) const;

            void clear();

            const size_t size() const;

            void append(SoundGroup *container);

            void append(Sounds::Sound *object);

            void append(SoundGroup &group, const bool merge = true);

            void insert(const size_t index, Sounds::Sound *object);

            std::vector<Sounds::Sound *>::iterator remove(const size_t index);

            std::vector<Sounds::Sound *>::iterator remove(const std::vector<Sounds::Sound *>::iterator &it);

            std::vector<Sounds::Sound *>::iterator remove(const std::vector<Sounds::Sound *>::reverse_iterator &it);

            Sounds::Sound *pop(const size_t index);

            Sounds::Sound *pop(const std::vector<Sounds::Sound *>::iterator &it);

            Sounds::Sound *pop(const std::vector<Sounds::Sound *>::reverse_iterator &it);

            Sounds::Sound *pop_front();

            Sounds::Sound *pop_back();

            const bool empty() const;

            Sounds::Sound *front();

            const Sounds::Sound *front() const;

            Sounds::Sound *back();

            const Sounds::Sound *back() const;

            void remove_front();

            void remove_back();

        };
    }
}