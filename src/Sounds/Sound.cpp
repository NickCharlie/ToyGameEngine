#include "Sounds/Sound.hpp"
#include "Resource/ResManager.hpp"

using namespace ToyGameEngine::Sounds;

Sound::Sound()
{

}

Sound::~Sound()
{
    
}

Sound* Sound::clone() const
{
    return new Sound(*this);
}

QMediaPlayer* Sound::get_sound(const std::string name) const
{
    return Resource::ResManager::get_instance().get_media_resource(name);
}

void Sound::push_sound(const std::string sound_string, const std::string file_path)
{
    this->_sound_strings.push_back(sound_string);
    Resource::ResManager::get_instance().load_media_resource(sound_string, file_path);
}

void Sound::push_sounds(std::vector<std::string> sound_strings, std::vector<std::string> files_path)
{
    for (size_t i = 0; (i < sound_strings.size() && i < files_path.size()); ++i)
    {
        this->_sound_strings.push_back(sound_strings[i]);
        Resource::ResManager::get_instance().load_media_resource(sound_strings[i], files_path[i]);
    }
}

void Sound::add_sound(const std::string sound_string, QMediaPlayer* sound)
{
    // QMediaPlayer* sound_copy = new QMediaPlayer(*sound);
    this->_sound_strings.push_back(sound_string);
    Resource::ResManager::get_instance().add_media_resource(sound_string, sound);
}

void Sound::add_sounds(std::vector<std::string> sound_strings, std::vector<QMediaPlayer*> sounds)
{
    for (size_t i = 0; (i < sound_strings.size() && i < sounds.size()); ++i)
    {
        // QMediaPlayer* sound_copy = new QMediaPlayer(*(sounds[i]));
        this->_sound_strings.push_back(sound_strings[i]);
        Resource::ResManager::get_instance().add_media_resource(sound_strings[i], sounds[i]);
    }
}

void Sound::add_exist_sound(const std::string sound_string)
{
    this->_sound_strings.push_back(sound_string);
}

void Sound::add_exist_sounds(std::vector<std::string> sound_strings)
{
    for (std::string sound : sound_strings)
    {
        this->_sound_strings.push_back(sound);
    }
}

std::string Sound::get_sound_state() const
{
    return this->_sound_state;
}
std::vector<std::string> Sound::get_sounds_strings() const
{
    return this->_sound_strings;
}

size_t Sound::size() const
{
    return this->_sound_strings.size();
}