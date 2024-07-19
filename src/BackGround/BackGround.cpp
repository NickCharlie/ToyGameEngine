#include "BackGround/BackGround.hpp"
#include "Resource/ResManager.hpp"
#include "BackGround.hpp"

using namespace ToyGameEngine::BackGround;



ToyGameEngine::BackGrounds::BackGround::BackGround()
{
}

ToyGameEngine::BackGrounds::BackGround::~BackGround()
{
}



ToyGameEngine::BackGrounds::BackGround *BackGrounds::BackGround::clone() const
{
    return new BackGround::BackGround(*this);
}

QPixmap* ToyGameEngine::BackGrounds::BackGround::BackGround::get_pixmap(const std::string& name)
{
    return Resource::ResManager::get_instance().get_pixmap_resource(name);
}

void ToyGameEngine::BackGrounds::BackGround::push_pixmap(std::string map_string, std::string file_path)
{
    Resource::ResManager::get_instance().load_pixmap_resource(map_string, file_path);
}

void ToyGameEngine::BackGrounds::BackGround::push_pixmaps(std::vector<std::string> maps_string, std::vector<std::string> file_path)
{
    for (int i = 0; i < maps_string.size(); i++)
    {
        Resource::ResManager::get_instance().load_pixmap_resource(maps_string[i], file_path[i]);
    }
}

void ToyGameEngine::BackGrounds::BackGround::add_pixmap(std::string map_string, QPixmap* map)
{
    QPixmap* map_copy = new QPixmap(*map);
    this->_pixmaps_strings.push_back(map_string);
    Resource::ResManager::get_instance().add_pixmap_resource(map_string, map_copy);
}

void ToyGameEngine::BackGrounds::BackGround::add_exist_pixmap(std::string map_string)
{
    if(Resource::ResManager::get_instance().get_pixmap_resource(map_string) == nullptr)
    {
        std::cerr << "cant find your map_string" << std::endl;
        return;
    }
    this->_pixmap_strings.push_back(map_string);
}

void ToyGameEngine::BackGrounds::BackGround::add_exist_pixmaps(std::vector<std::string> map_strings)
{
    for (std::string str : map_strings)
    {
        if (Resource::ResManager::get_instance().get_pixmap_resource(str) == nullptr)
        {
            std::cerr << "cant find your map_string : " << str << std::endl;
            continue;
        }
        this->_pixmap_strings.push_back(str);
    }
}

void ToyGameEngine::BackGrounds::BackGround::set_pixmap_state(std::string state)
{
    this->_pixmap_state = state;
    for (size_t i = 0; i < this->_pixmap_strings.size(); ++i)
    {
        if (_pixmap_strings[i] == this->_pixmap_state)
        {
            _pixmap_strings[0].swap(_pixmap_strings[i]);
            return;
        }
    }
    std::cerr << "cant find your state" << std::endl;
}

std::string ToyGameEngine::BackGrounds::BackGround::get_pixmap_state() const
{
    return this->_pixmap_state;
}

std::vector<std::string> ToyGameEngine::BackGrounds::BackGround::get_pixmaps_strings() const
{
    return this->_pixmap_strings;
}
