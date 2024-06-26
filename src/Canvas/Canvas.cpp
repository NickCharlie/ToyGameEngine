#include "Canvas/Canvas.hpp"

using namespace ToyGameEngine::Canvas;

void ICanvas::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
}

void ICanvas::draw_line(QPainter& painter, Math::Geometry::Line& line) {

}

void ICanvas::draw_rect(QPainter& painter, Math::Geometry::AABBRect& rect) {

}

void ICanvas::draw_point(QPainter& painter, Math::Geometry::Point& point) {

}

void ICanvas::draw_bezier(QPainter& painter, Math::Geometry::Bezier& bezier) {

}

void ICanvas::draw_circle(QPainter& painter, Math::Geometry::Circle& circle) {

}

void ICanvas::draw_polygon(QPainter& painter, Math::Geometry::Polygon& polygon) {

}

void ICanvas::draw_polyline(QPainter& painter, Math::Geometry::Polyline& polyline) {

}

void ICanvas::draw_triangle(QPainter& painter, Math::Geometry::Triangle& triangle) {
    
}