#pragma once
#include "Scene/KeyCode.hpp"
#include <unordered_set>

namespace ToyGameEngine
{
    namespace Scenes
    {
        enum EventType { EVENT, KEY_EVENT, MOUSE_EVENT };

        struct Event
        {
            bool active = true;
            bool is_auto_repeat = false;
            size_t response = 0;

            virtual EventType type() const
            {
                return EventType::EVENT;
            }
        };

        struct KeyEvent : public Event
        {
            std::unordered_set<Key> key;

            KeyEvent(const Key value) 
            {
                key.insert(value);
            }

            KeyEvent(const std::unordered_set<Key> keys) : key(keys) {}

            void insert(const Key value) 
            {
                key.insert(value);
            }

            std::unordered_set<Key>& get_key()
            {
                return key;
            }
            EventType type() const override
            {
                return EventType::KEY_EVENT;
            }
        };

        struct MouseEvent : public Event
        {
            MouseButton button;

            MouseEvent(const MouseButton value)
                : button(value) {}
            
            EventType type() const override
            {
                return EventType::MOUSE_EVENT;
            }
        };
        
        
    }
}