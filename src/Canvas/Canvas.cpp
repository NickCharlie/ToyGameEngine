#include "Canvas/Canvas.hpp"

using namespace ToyGameEngine::Canvas;

void ICanvas::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    draw_graph();
}

void ICanvas::push_to_group(Math::Geometry::GeometryObject* o) {
    group.append(o);
}

void ICanvas::draw_graph() {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 可选：设置抗锯齿

	QPen pen;
	pen.setColor(QColor(Qt::blue));//设置笔颜色
	pen.setWidth(4);//设置笔宽度
	painter.setPen(pen);//设置为要绘制的笔

    const auto& group = get_group();

    // 遍历绘图元素，依次绘制
    for (auto element : group) {
        if (auto line = dynamic_cast<Math::Geometry::Line*>(element)) {
            if (line == nullptr) {
                continue;
            }
            draw_line(painter, *line);
        } else if (auto rect = dynamic_cast<Math::Geometry::AABBRect*>(element)) {
            if (rect == nullptr) {
                continue;
            }
            draw_rect(painter, *rect);
        } else if (auto point = dynamic_cast<Math::Geometry::Point*>(element)) {
            if (point == nullptr) {
                continue;
            }
            draw_point(painter, *point);
        }
        // TODO
    }

}

GeometryGroup& ICanvas::get_group() {
    return group;
}

void ICanvas::draw_line(QPainter& painter, Math::Geometry::Line& line) {

    painter.drawLine(QLineF(QPointF(line.front().x, line.front().y), QPointF(line.back().x, line.back().y)));
}

void ICanvas::draw_rect(QPainter& painter, Math::Geometry::AABBRect& rect) {

    painter.drawRect(QRectF(rect.left(), rect.top(), rect.right(), rect.bottom()));
}

void ICanvas::draw_point(QPainter& painter, Math::Geometry::Point& point) {

    painter.drawPoint(QPointF(point.x, point.y));
}

void ICanvas::draw_bezier(QPainter& painter, Math::Geometry::Bezier& bezier) {

    const auto& shape = bezier.shape();

    for (size_t i = 0; i < shape.size() - 1; ++i) {
        const auto& pos1 = shape[i];
        const auto& pos2 = shape[i + 1];

        painter.drawLine(QPointF(pos1.x, pos1.y), QPointF(pos2.x, pos2.y));
    }
}

void ICanvas::draw_circle(QPainter& painter, Math::Geometry::Circle& circle) {

    double centerX = circle.x;
    double centerY = circle.y;
    double radius = circle.radius;

    painter.drawEllipse(QPointF(centerX, centerY), radius, radius);
}

void ICanvas::draw_polygon(QPainter& painter, Math::Geometry::Polygon& polygon) {

    const auto begin = polygon.begin();
    const auto end = polygon.end();

    if (std::distance(begin, end) < 2) {
        return;
    }

    QVector<QPointF> qpoints;
    for (auto it = begin; it != end; ++it) {
        qpoints.append(QPointF(it->x, it->y));
    }

    painter.drawPolygon(qpoints.data(), qpoints.size());
}

void ICanvas::draw_polyline(QPainter& painter, Math::Geometry::Polyline& polyline) {

    const auto begin = polyline.begin();
    const auto end = polyline.end();

    if (std::distance(begin, end) < 2) {
        return;
    }

    QVector<QPointF> qpoints;
    for (auto it = begin; it != end; ++it) {
        qpoints.append(QPointF(it->x, it->y));
    }

    painter.drawPolyline(qpoints.data(), qpoints.size());
}

void ICanvas::draw_triangle(QPainter& painter, Math::Geometry::Triangle& triangle) {
    QPointF points[3] = {
        QPointF(triangle[0].x, triangle[0].y),
        QPointF(triangle[1].x, triangle[1].y),
        QPointF(triangle[2].x, triangle[2].y)
    };

    painter.drawPolygon(points, 3);
}

void ICanvas::mousePressEvent(QMouseEvent *event) {

}

void ICanvas::mouseReleaseEvent(QMouseEvent *event) {

}

void ICanvas::mouseMoveEvent(QMouseEvent *event) {

}

void ICanvas::wheelEvent(QWheelEvent *event) {

}

void ICanvas::mouseDoubleClickEvent(QMouseEvent *event) {

}

void ICanvas::resizeEvent(QResizeEvent *event) {
    
}