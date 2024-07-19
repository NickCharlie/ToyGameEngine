#pragma once

#include <vector>
#include "BackGround/BackGround.hpp"



namespace ToyGameEngine
{

    namespace BackGrounds
    {

        class BackGroundGroup
        {
        private:
            std::vector<BackGrounds::BackGround *> _objects;
            bool _visible = true;

        public:
            BackGroundGroup();
            BackGroundGroup(const BackGroundGroup &group);
            BackGroundGroup(const std::initializer_list<BackGrounds::BackGround *> &objs);
            BackGroundGroup(std::vector<BackGrounds::BackGround *>::const_iterator begin, std::vector<BackGrounds::BackGround *>::const_iterator end);

            virtual ~BackGroundGroup();
            const bool &visible() const;

            void show();
            void hide();

            BackGroundGroup *clone() const;
            void clone(BackGroundGroup &group);

            BackGroundGroup &operator=(const BackGroundGroup &group);

            std::vector<BackGrounds::BackGround *>::iterator begin();

            std::vector<BackGrounds::BackGround *>::const_iterator begin() const;

            std::vector<BackGrounds::BackGround *>::const_iterator cbegin() const;

            std::vector<BackGrounds::BackGround *>::iterator end();

            std::vector<BackGrounds::BackGround *>::const_iterator end() const;

            std::vector<BackGrounds::BackGround *>::const_iterator cend() const;

            std::vector<BackGrounds::BackGround *>::reverse_iterator rbegin();

            std::vector<BackGrounds::BackGround *>::const_reverse_iterator rbegin() const;

            std::vector<BackGrounds::BackGround *>::const_reverse_iterator crbegin() const;

            std::vector<BackGrounds::BackGround *>::reverse_iterator rend();

            std::vector<BackGrounds::BackGround *>::const_reverse_iterator rend() const;

            std::vector<BackGrounds::BackGround *>::const_reverse_iterator crend() const;

            BackGrounds::BackGround *operator[](int index);

            const BackGrounds::BackGround *operator[](int index) const;

            void clear();

            const size_t size() const;

            void append(BackGroundGroup *container);

            void append(BackGrounds::BackGround *object);

            void append(BackGroundGroup &group, const bool merge = true);

            void insert(const size_t index, BackGrounds::BackGround *object);

            std::vector<BackGrounds::BackGround *>::iterator remove(const size_t index);

            std::vector<BackGrounds::BackGround *>::iterator remove(const std::vector<BackGrounds::BackGround *>::iterator &it);

            std::vector<BackGrounds::BackGround *>::iterator remove(const std::vector<BackGrounds::BackGround *>::reverse_iterator &it);

            BackGrounds::BackGround *pop(const size_t index);

            BackGrounds::BackGround *pop(const std::vector<BackGrounds::BackGround *>::iterator &it);

            BackGrounds::BackGround *pop(const std::vector<BackGrounds::BackGround *>::reverse_iterator &it);

            BackGrounds::BackGround *pop_front();

            BackGrounds::BackGround *pop_back();

            const bool empty() const;

            BackGrounds::BackGround *front();

            const BackGrounds::BackGround *front() const;

            BackGrounds::BackGround *back();

            const BackGrounds::BackGround *back() const;

            void remove_front();

            void remove_back();

        };

    }
    



}