#pragma once
#include <string>
#include <vector>
#include <QPixmap>

namespace ToyGameEngine
{
    namespace BackGrounds
    {

        class BackGround
        {
        public:
            BackGround();
            ~BackGround();

            BackGround *clone() const;

            QPixmap* get_pixmap(const std::string& name);

            void push_pixmap(std::string map_string, std::string file_path);

            void push_pixmaps(std::vector<std::string> maps_string, std::vector<std::string> file_path);

            void add_pixmap(std::string map_string, QPixmap* map);

            void add_exist_pixmap(std::string map_string);

            void add_exist_pixmaps(std::vector<std::string> map_strings);

            void set_pixmap_state(std::string state);

            std::string get_pixmap_state() const;

            std::vector<std::string> get_pixmaps_strings() const;
        protected:
            std::string _pixmap_state;

            bool _visible = true;
            std::vector<std::string> _pixmap_strings;


        };




    }


}