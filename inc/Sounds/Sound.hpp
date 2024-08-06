#pragma once
#include <QtMultimedia/QMediaPlayer>
#include <string>
#include <vector>

namespace ToyGameEngine
{
    namespace Sounds
    {
        class Sound
        {
        public:
            Sound();
            ~Sound();

            Sound* clone() const;
            QMediaPlayer* get_sound(const std::string name) const;

            void push_sound(const std::string sound_string, const std::string file_path);
            void push_sounds(std::vector<std::string> sound_strings, std::vector<std::string> files_path);

            void add_sound(const std::string sound_string, QMediaPlayer* sound);
            void add_sounds(std::vector<std::string> sound_strings, std::vector<QMediaPlayer*> sounds);

            void add_exist_sound(const std::string sound_string);
            void add_exist_sounds(std::vector<std::string> sound_strings);

            std::string get_sound_state() const;
            std::vector<std::string> get_sounds_strings() const;

            size_t size() const;
        protected:
            std::string _sound_state;

            std::vector<std::string> _sound_strings;
        };
    }
}