#include "BackGround/BackGround.hpp"
#include "Resource/ResManager.hpp"
#include "BackGround/BackGround.hpp"
#include "Utils/PixmapUtils.hpp"
#include "Utils/Utils.hpp"

using namespace ToyGameEngine::BackGrounds;
using namespace ToyGameEngine::Utils;
using namespace ToyGameEngine::Math;


ToyGameEngine::BackGrounds::BackGround::BackGround()
{
}

ToyGameEngine::BackGrounds::BackGround::~BackGround()
{
}



ToyGameEngine::BackGrounds::BackGround *BackGround::BackGround::clone() const
{
    return new BackGround(*this);
}

QPixmap* ToyGameEngine::BackGrounds::BackGround::BackGround::get_pixmap(const std::string& name)
{
    return Resource::ResManager::get_instance().get_pixmap_resource(name);
}

void ToyGameEngine::BackGrounds::BackGround::push_pixmap(std::string map_string, std::string file_path)
{
    std::vector<std::string> ret_strings = Resource::ResManager::get_instance().load_background_resource(map_string, file_path);

    for (size_t i = 0; i < ret_strings.size(); ++i)
    {
        for (size_t x = 0; x < Utils::Util::get_mainwindow_size().width(); x +=50)
        {
            for (size_t y = 0; y < Utils::Util::get_mainwindow_size().height(); y +=50)
            {
                Math::Geometry::Point p(x, y);
                this->_points.push_back(p);
            }
        }
    }

    for (std::string str : ret_strings)
    {
        this->_pixmap_strings.push_back(str);
    }
}

void ToyGameEngine::BackGrounds::BackGround::push_pixmaps(std::vector<std::string> maps_string, std::vector<std::string> file_path)
{
    for (size_t i = 0; i < maps_string.size(); i++)
    {
        std::vector<std::string> ret_strings = Resource::ResManager::get_instance().load_background_resource(maps_string[i], file_path[i]);
        
        for (std::string str : ret_strings)
        {
            this->_pixmap_strings.push_back(str);
        }
    }
}

void ToyGameEngine::BackGrounds::BackGround::add_pixmap(std::string map_string, QPixmap* map)
{
    QPixmap* map_copy = new QPixmap(*map);
    std::vector<std::string> ret_strings = Resource::ResManager::get_instance().add_background_resource(map_string, map_copy);
    
    for (std::string str : ret_strings)
    {
        this->_pixmap_strings.push_back(str);
    }
}

// void ToyGameEngine::BackGrounds::BackGround::add_exist_pixmap(std::string map_string)
// {
//     if(Resource::ResManager::get_instance().get_pixmap_resource(map_string) == nullptr)
//     {
//         std::cerr << "cant find your map_string" << std::endl;
//         return;
//     }
//     this->_pixmap_strings.push_back(map_string);
// }

// void ToyGameEngine::BackGrounds::BackGround::add_exist_pixmaps(std::vector<std::string> map_strings)
// {
//     for (std::string str : map_strings)
//     {
//         if (Resource::ResManager::get_instance().get_pixmap_resource(str) == nullptr)
//         {
//             std::cerr << "cant find your map_string : " << str << std::endl;
//             continue;
//         }
//         this->_pixmap_strings.push_back(str);
//     }
// }

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
}

std::string ToyGameEngine::BackGrounds::BackGround::get_pixmap_state() const
{
    return this->_pixmap_state;
}

std::vector<std::string> ToyGameEngine::BackGrounds::BackGround::get_pixmaps_strings() const
{
    return this->_pixmap_strings;
}

size_t ToyGameEngine::BackGrounds::BackGround::size() const
{
    return this->_pixmap_strings.size();
}

std::vector<Geometry::Point> ToyGameEngine::BackGrounds::BackGround::get_points() const
{
    return this->_points;
}