#pragma once
#include <vector>
#include <QPixmap>

namespace ToyGameEngine 
{
    namespace Utils
    {
        class PixmapUtils
        {
        public:
            static std::vector<QPixmap> split_pixmap(QPixmap pixmap, int tile_width, int tile_height)
            {
                std::vector<QPixmap> tiles;
                int rows = pixmap.height() / tile_height;
                int cols = pixmap.width() / tile_width;

                for (int row = 0; row < rows; ++row)
                {
                    for (int col = 0; col < cols; ++col)
                    {
                        int x = col * tile_width;
                        int y = row * tile_height;
                        QPixmap tile = pixmap.copy(x, y, tile_width, tile_height);
                        tiles.push_back(tile);
                    }
                }

                return tiles;
            }
        };
    }
}