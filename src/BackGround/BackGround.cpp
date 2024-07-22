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

    // 清空之前的点和图像字符串
    _points.clear();
    _pixmap_strings.clear();

    int cols = Utils::Util::get_mainwindow_size().width() / 50;
    int image_index = 0;
    
    for (const std::string& str : ret_strings)
    {
        int x = (image_index % cols) * 50;
        int y = (image_index / cols) * 50;
        
        _points.push_back({(double) x, (double) y});
        _pixmap_strings.push_back(str);
        ++image_index;
    }

    // 检查Point点和图像字符串的数量是否一致
    if (_points.size() != _pixmap_strings.size())
    {
        std::cerr << "Error: _points size (" << _points.size() << ") does not match _pixmap_strings size (" << _pixmap_strings.size() << ")" << std::endl;
    }

    // QSize mainWindowSize = Util::get_mainwindow_size();
    // int width = mainWindowSize.width();
    // int height = mainWindowSize.height();

    // for (int x = 0; x < width; x += 50) 
    // {
    //     for (int y = 0; y < height; y += 50) 
    //     {
    //         Math::Geometry::Point p(x, y);
    //         _points.push_back(p);
    //     }
    // }

    // _pixmap_strings.insert(_pixmap_strings.end(), ret_strings.begin(), ret_strings.end());
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