#pragma once
#include <QWidget>
#include <QPen>
#include "Canvas_Impl.hpp"
#include "GeometryGroup.hpp"

namespace ToyGameEngine
{

    namespace Canvas
    {

        class ICanvas : public ICanvas_Impl, public QWidget
        {
        private:
            QPolygonF _qpoints;

        public:
            ICanvas(QWidget *parent = nullptr) : QWidget(parent) {}

            // 绘图事件
            void paintEvent(QPaintEvent *event) override;

            void draw_line(QPainter &painter, const Math::Geometry::Line &line);

            void draw_rectangle(QPainter &painter, const Math::Geometry::AABBRect &rect);

            void draw_point(QPainter &painter, const Math::Geometry::Point &point);

            void draw_bezier(QPainter &painter, const Math::Geometry::Bezier &bezier);

            void draw_circle(QPainter &painter, const Math::Geometry::Circle &circle);

            void draw_polygon(QPainter &painter, const Math::Geometry::Polygon &polygon);

            void draw_polyline(QPainter &painter, const Math::Geometry::Polyline &polyline);

            void draw_rectangle(QPainter &painter, const Math::Geometry::Rectangle &rectangle);

            void draw_triangle(QPainter &painter, const Math::Geometry::Triangle &triangle);

        private:
            void init();

            void draw_scene();

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