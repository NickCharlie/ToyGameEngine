#pragma once
#include "Canvas_Impl.hpp"
#include "GeometryGroup.hpp"
#include <QWidget>
#include <QPen>

namespace ToyGameEngine {
    
    namespace Canvas {

        class ICanvas : public ICanvas_Impl, public QWidget {
        public:

            ICanvas(QWidget *parent = nullptr) : QWidget(parent) {}

            // 绘图事件
            void paintEvent(QPaintEvent *event) override;

            void draw_line(QPainter& painter, Math::Geometry::Line& line);

            void draw_rect(QPainter& painter, Math::Geometry::AABBRect &rect);

            void draw_point(QPainter& painter, Math::Geometry::Point& point);

            void draw_bezier(QPainter& painter, Math::Geometry::Bezier& bezier);

            void draw_circle(QPainter& painter, Math::Geometry::Circle& circle);

            void draw_polygon(QPainter& painter, Math::Geometry::Polygon& polygon);

            void draw_polyline(QPainter& painter, Math::Geometry::Polyline& polyline);

            void draw_triangle(QPainter& painter, Math::Geometry::Triangle& triangle);

            // GeometryGroup& get_group();

            // void push_to_group(Math::Geometry::GeometryObject* o);

        private:


            void init();

            void draw_graph();

            void draw_cache();

            void draw_select_rect();

        protected:
            void mousePressEvent(QMouseEvent *event);

            void mouseReleaseEvent(QMouseEvent *event);

            void mouseMoveEvent(QMouseEvent *event);

            void wheelEvent(QWheelEvent *event);

            void mouseDoubleClickEvent(QMouseEvent *event);

            void resizeEvent(QResizeEvent *event);
        };
    }
}