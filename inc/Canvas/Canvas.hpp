#pragma once
#include <QWidget>
#include <QPen>
#include <QKeyEvent>
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

            void draw_line(QPainter &painter, const Math::Geometry::Line &line) override;

            void draw_rectangle(QPainter &painter, const Math::Geometry::AABBRect &rect) override;

            void draw_point(QPainter &painter, const Math::Geometry::Point &point) override;

            void draw_bezier(QPainter &painter, const Math::Geometry::Bezier &bezier) override;

            void draw_circle(QPainter &painter, const Math::Geometry::Circle &circle) override;

            void draw_polygon(QPainter &painter, const Math::Geometry::Polygon &polygon) override;

            void draw_polyline(QPainter &painter, const Math::Geometry::Polyline &polyline) override;

            void draw_rectangle(QPainter &painter, const Math::Geometry::Rectangle &rectangle) override;

            void draw_triangle(QPainter &painter, const Math::Geometry::Triangle &triangle) override;

            void update() override;

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

            void keyPressEvent(QKeyEvent *event);
        };
    }
}