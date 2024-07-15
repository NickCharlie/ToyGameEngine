#pragma once
#include "Scene/KeyCode.hpp"
#include <unordered_set>

namespace ToyGameEngine
{
    namespace Spirits
    {
        class Spirit;
    }

    namespace Scenes
    {
        enum EventType { EVENT, IO_EVENT, KEY_EVENT, MOUSE_EVENT, DESTRUCTION_EVENT, ACTION_EVENT };

        struct Event
        {
            bool active = true;
            size_t response = 0;

            virtual EventType type() const
            {
                return EventType::EVENT;
            }
        };

        struct IOEvent : public Event
        {
            bool is_auto_repeat = false;

            virtual EventType type() const
            {
                return EventType::IO_EVENT;
            }
        };

        struct KeyEvent : public IOEvent
        {
            std::unordered_set<Key> keys;

            KeyEvent(const Key value) 
            {
                keys.insert(value);
            }

            KeyEvent(const std::unordered_set<Key> keys_) : keys(keys_) {}

            void insert(const Key value) 
            {
                keys.insert(value);
            }

            EventType type() const override
            {
                return EventType::KEY_EVENT;
            }
        };

        struct MouseEvent : public IOEvent
        {
            MouseButton button;

            MouseEvent(const MouseButton value)
                : button(value) {}
            
            EventType type() const override
            {
                return EventType::MOUSE_EVENT;
            }
        };

        struct DestructionEvent : public Event
        {
            Spirits::Spirit *spirit;

            DestructionEvent(Spirits::Spirit *spirit_)
                : spirit(spirit_)
            {

            }

            EventType type() const override
            {
                return EventType::DESTRUCTION_EVENT;
            }
        };

        struct ActionEvent : public Event
        {
        private:
            std::function<void()> func;

        public:
            ActionEvent(std::function<void()> func_)
                : func(func_) {}

            void run()
            {
                if (func)
                {
                    return func();
                }
            }

            EventType type() const override
            {
                return EventType::ACTION_EVENT;
            }
        };
    }
}