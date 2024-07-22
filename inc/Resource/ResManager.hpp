#pragma once

#include "Utils/PixmapUtils.hpp"
#include "Utils/Utils.hpp"

#include <string>
#include <map>
#include <variant>
#include <QPixmap>
#include <QtMultimedia/QMediaPlayer>
#include <iostream>

using namespace ToyGameEngine::Utils;

namespace ToyGameEngine
{
    namespace Resource
    {
        using ResourceVariant = std::variant<QPixmap*, QMediaPlayer*>;

        class ResManager {
        public:
            static ResManager& get_instance() {
                static ResManager instance;
                return instance;
            }

            bool load_pixmap_resource(const std::string& name, const std::string& filePath) 
            {
                QPixmap* pixmap = new QPixmap(QString::fromStdString(filePath));
                if (pixmap->isNull()) 
                {
                    delete pixmap;
                    std::cerr << "Failed to load QPixmap from: " << filePath << std::endl;
                    return false;
                }
                _resources[name] = pixmap;
                return true;
            }

            
            std::vector<std::string> load_background_resource(const std::string& name, const std::string& filePath) 
            {   
                std::vector<std::string> ret;
                QPixmap* pixmap = new QPixmap(QString::fromStdString(filePath));

                QPixmap pm = pixmap->scaled(Utils::Util::get_mainwindow_size().width(), Utils::Util::get_mainwindow_size().height(),
                 Qt::KeepAspectRatio, Qt::SmoothTransformation);

                if (pixmap->isNull()) 
                {
                    delete pixmap;
                    std::cerr << "Failed to load QPixmap from: " << filePath << std::endl;
                    return std::vector<std::string>();
                }

                std::vector<QPixmap> split_maps = Utils::PixmapUtils::split_pixmap(pm, 50, 50);

                if (split_maps.size() <= 0)
                {
                    std::cerr << "Failed to split QPixmap" << std::endl;
                    return std::vector<std::string>();
                }

                for (size_t i = 0; i < split_maps.size(); ++i)
                {
                    std::string ret_name = name + "_" + std::to_string(i);
                    ret.push_back(ret_name);
                    _resources[ret_name] = new QPixmap(split_maps[i]);
                }
                return ret;
            }

            std::vector<std::string> add_background_resource(const std::string& name, QPixmap* map) 
            {
                std::vector<std::string> ret;
                if (map->isNull()) 
                {
                    delete map;
                    std::cerr << "Failed to load QPixmap" << std::endl;
                    return std::vector<std::string>();
                }

                std::vector<QPixmap> split_maps = Utils::PixmapUtils::split_pixmap(*map, 50, 50);

                if (split_maps.size() <= 0)
                {
                    std::cerr << "Failed to split QPixmap" << std::endl;
                    return std::vector<std::string>();
                }

                for (size_t i = 0; i < split_maps.size(); ++i)
                {
                    std::string ret_name = name + "_" + std::to_string(i);
                    ret.push_back(ret_name);
                    _resources[ret_name] = new QPixmap(split_maps[i]);
                }
                return ret;
            }

            bool add_pixmap_resource(const std::string& name, QPixmap* map)
            {
                if (map->isNull()) 
                {
                    delete map;
                    std::cerr << "Failed to add QPixmap " << name <<  std::endl;
                    return false;
                }
                _resources[name] = map;
                return true;
            }

            bool load_media_resource(const std::string& name, const std::string& filePath) 
            {
                QMediaPlayer* mediaPlayer = new QMediaPlayer();
                mediaPlayer->setSource(QUrl::fromLocalFile(QString::fromStdString(filePath)));
                _resources[name] = mediaPlayer;
                return true;
            }

            QPixmap* get_pixmap_resource(const std::string& name) const 
            {
                std::map<std::string, ResourceVariant>::const_iterator it = _resources.find(name);
                if (it != _resources.end()) {
                    if (QPixmap* const* pixmap = std::get_if<QPixmap*>(&it->second)) 
                    {
                        return *pixmap;
                    }
                }
                std::cerr << "QPixmap resource not found: " << name << std::endl;
                return nullptr;
            }

            QMediaPlayer* get_media_resource(const std::string& name) const 
            {
                std::map<std::string, ResourceVariant>::const_iterator it = _resources.find(name);
                if (it != _resources.end()) {
                    if (QMediaPlayer* const* mediaPlayer = std::get_if<QMediaPlayer*>(&it->second)) {
                        return *mediaPlayer;
                    }
                }
                std::cerr << "QMediaPlayer resource not found: " << name << std::endl;
                return nullptr;
            }

            void release_all() {
                for (auto& pair : _resources) 
                {
                    std::visit([](auto* res) { delete res; }, pair.second);
                }
                _resources.clear();
            }

            ResManager(const ResManager&) = delete;
            ResManager& operator=(const ResManager&) = delete;

        private:
            ResManager() = default;
            ~ResManager() {
                release_all();
            }

            std::map<std::string, ResourceVariant> _resources;
        };
    }
}
