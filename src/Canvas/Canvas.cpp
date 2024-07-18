#include "Canvas/Canvas.hpp"
#include "Resource/ResManager.hpp"

#include <iostream>
#include <QSize>
#include <QTransform>

using namespace ToyGameEngine::Canvas;
using namespace ToyGameEngine::Math;
using namespace ToyGameEngine::Spirits;

void ICanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    draw_scene();
}

void ICanvas::draw_pixmap(QPainter& painter, Spirit* sp,  double width, double height)
{
    QPixmap* map = Resource::ResManager.get_instance().get_pixmap_resource(sp->_pixmap_state);

    if (map == nullptr)
    {
        std::cout << "cant find sp->_pixmap_state " << sp->_pixmap_state << std::endl;
        return;
    }

    QPixmap scaled_map = map->scaled(QSize(width, height),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    QTransform transform;  
    transform.rotate(180);
    scaled_map = scaled_map.transformed(QTransform().scale(-1, 1));
    scaled_map = scaled_map.transformed(transform, Qt::SmoothTransformation);

    switch (sp->type())
    {
    case Geometry::Type::RECTANGLE:
        sp = static_cast<ShapedSpirit<Geometry::Rectangle> *>(sp);
        painter.drawPixmap(sp->x - width / 2, sp->y - height / 2, width, height, scaled_map);
        break;
    case Geometry::Type::SQUARE:
        sp = static_cast<ShapedSpirit<Geometry::Square> *>(sp);
        painter.drawPixmap(sp->x - width / 2, sp->y - height / 2, width, height, scaled_map);
        break;
    case Geometry::Type::AABBRECT:
        sp = static_cast<ShapedSpirit<Geometry::AABBRect> *>(sp);
        painter.drawPixmap(sp->x - width / 2, sp->y - height / 2, width, height, scaled_map);
        break;
    case Geometry::Type::CIRCLE:
        sp = static_cast<ShapedSpirit<Geometry::Circle> *>(sp);
        painter.drawPixmap(sp->x - width / 2, sp->y - height / 2, width, height, scaled_map);
        break;
    case Geometry::Type::POLYGON:
        sp = static_cast<ShapedSpirit<Geometry::Rectangle> *>(sp);
        painter.drawPixmap(sp->x - width / 2, sp->y - height / 2, width, height, scaled_map);
        break;
    case Geometry::Type::POLYLINE:
        sp = static_cast<ShapedSpirit<Geometry::Polyline> *>(sp);
        painter.drawPixmap(sp->x - width / 2, sp->y - height / 2, width, height, scaled_map);
        break;
    case Geometry::Type::BEZIER:
        sp = static_cast<ShapedSpirit<Geometry::Bezier> *>(sp);
        painter.drawPixmap(sp->x - width / 2, sp->y - height / 2, width, height, scaled_map);
        break;
    case Geometry::Type::POINT:
        sp = static_cast<ShapedSpirit<Geometry::Point> *>(sp);
        painter.drawPixmap(sp->x - width, sp->y - height, width, height, scaled_map);
        break;
    default:
        break;
    }
}

void ICanvas::draw_scene()
{
    if (_scene == nullptr)
    {
        return;
    }

    QPainter painter(this);
    painter.setWindow(0, this->height(), this->width(), -(this->height()));

    QPen pen;
    pen.setColor(QColor(Qt::blue)); //设置笔颜色
    pen.setWidth(2); //设置笔宽度
    painter.setPen(pen); //设置为要绘制的笔

    for (const Spirits::SpiritGroup &group : _scene->groups())
    {
        for (Spirits::Spirit *spirit : group)
        {
            if (!_scene->is_visible(spirit))
            {
                continue;
            }

            switch (spirit->type())
            {
            case Geometry::Type::RECTANGLE:
                draw_rectangle(painter, static_cast<ShapedSpirit<Geometry::Rectangle> *>(spirit)->shape());
                draw_pixmap(painter, spirit,
                 static_cast<ShapedSpirit<Geometry::Rectangle> *>(spirit)->shape().width(),
                 static_cast<ShapedSpirit<Geometry::Rectangle> *>(spirit)->shape().height(),
                 spirit->get_pixmap());
                break;
            case Geometry::Type::SQUARE:
                draw_rectangle(painter, static_cast<ShapedSpirit<Geometry::Square> *>(spirit)->shape());
                draw_pixmap(painter, spirit,
                 static_cast<ShapedSpirit<Geometry::Square> *>(spirit)->shape().width(),
                 static_cast<ShapedSpirit<Geometry::Square> *>(spirit)->shape().height(),
                 spirit->get_pixmap());
                break;
            case Geometry::Type::AABBRECT:
                draw_rectangle(painter, static_cast<ShapedSpirit<Geometry::AABBRect> *>(spirit)->shape());
                draw_pixmap(painter, spirit,
                 static_cast<ShapedSpirit<Geometry::AABBRect> *>(spirit)->shape().width(),
                 static_cast<ShapedSpirit<Geometry::AABBRect> *>(spirit)->shape().height(),
                 spirit->get_pixmap());
                break;
            case Geometry::Type::CIRCLE:
                draw_circle(painter, static_cast<ShapedSpirit<Geometry::Circle> *>(spirit)->shape());
                draw_pixmap(painter, spirit,
                 static_cast<ShapedSpirit<Geometry::Circle> *>(spirit)->shape().radius,
                 static_cast<ShapedSpirit<Geometry::Circle> *>(spirit)->shape().radius,
                 spirit->get_pixmap());
                break;
            case Geometry::Type::POLYGON:
                draw_polygon(painter, static_cast<ShapedSpirit<Geometry::Polygon> *>(spirit)->shape());
                // draw_pixmap(painter, static_cast<ShapedSpirit<Geometry::Polygon> *>(spirit),
                //  static_cast<ShapedSpirit<Geometry::Polygon> *>(spirit)->shape().width(),
                //  static_cast<ShapedSpirit<Geometry::Polygon> *>(spirit)->shape().height(),
                //  static_cast<ShapedSpirit<Geometry::Polygon> *>(spirit)->get_pixmap());
                break;
            case Geometry::Type::POLYLINE:
                draw_polyline(painter, static_cast<ShapedSpirit<Geometry::Polyline> *>(spirit)->shape());
                // draw_pixmap(painter, static_cast<ShapedSpirit<Geometry::Polyline> *>(spirit),
                //  static_cast<ShapedSpirit<Geometry::Polyline> *>(spirit)->shape().width(),
                //  static_cast<ShapedSpirit<Geometry::Polyline> *>(spirit)->shape().height(),
                //  static_cast<ShapedSpirit<Geometry::Polyline> *>(spirit)->get_pixmap());
                break;
            case Geometry::Type::BEZIER:
                draw_bezier(painter, static_cast<ShapedSpirit<Geometry::Bezier> *>(spirit)->shape());
                // draw_pixmap(painter, static_cast<ShapedSpirit<Geometry::Bezier> *>(spirit),
                //  static_cast<ShapedSpirit<Geometry::Bezier> *>(spirit)->shape().width(),
                //  static_cast<ShapedSpirit<Geometry::Bezier> *>(spirit)->shape().height(),
                //  static_cast<ShapedSpirit<Geometry::Bezier> *>(spirit)->get_pixmap());
                break;
            case Geometry::Type::POINT:
                draw_point(painter, static_cast<ShapedSpirit<Geometry::Point> *>(spirit)->shape());
                // draw_pixmap(painter, static_cast<ShapedSpirit<Geometry::Point> *>(spirit),
                //  static_cast<ShapedSpirit<Geometry::Point> *>(spirit)->shape().width(),
                //  static_cast<ShapedSpirit<Geometry::Point> *>(spirit)->shape().height(),
                //  static_cast<ShapedSpirit<Geometry::Point> *>(spirit)->get_pixmap());
                break;
            default:
                break;
            }
        }
    }
}

void ICanvas::draw_line(QPainter &painter, const Math::Geometry::Line &line)
{
    painter.drawLine(QPointF(line.front().x, line.front().y), QPointF(line.back().x, line.back().y));
}

void ICanvas::draw_rectangle(QPainter &painter, const Math::Geometry::AABBRect &rect)
{
    painter.drawRect(QRectF(rect.left(), rect.top(), rect.right(), rect.bottom()));
}

void ICanvas::draw_point(QPainter &painter, const Math::Geometry::Point &point)
{
    painter.drawPoint(point.x, point.y);
}

void ICanvas::draw_bezier(QPainter &painter, const Math::Geometry::Bezier &bezier)
{
    _qpoints.clear();
    for (const Geometry::Point &point : bezier.shape())
    {
        _qpoints.append(QPointF(point.x, point.y));
    }
    painter.drawPolyline(_qpoints);
}

void ICanvas::draw_circle(QPainter &painter, const Math::Geometry::Circle &circle)
{
    painter.drawEllipse(QPointF(circle.x, circle.y), circle.radius, circle.radius);
}

void ICanvas::draw_polygon(QPainter &painter, const Math::Geometry::Polygon &polygon)
{
    _qpoints.clear();
    for (const Geometry::Point &point : polygon)
    {
        _qpoints.append(QPointF(point.x, point.y));
    }
    painter.drawPolygon(_qpoints);
}

void ICanvas::draw_polyline(QPainter &painter, const Math::Geometry::Polyline &polyline)
{
    _qpoints.clear();
    for (const Geometry::Point &point : polyline)
    {
        _qpoints.append(QPointF(point.x, point.y));
    }
    painter.drawPolyline(_qpoints);
}

void ICanvas::draw_rectangle(QPainter &painter, const Math::Geometry::Rectangle &rectangle)
{
    _qpoints.clear();
    for (size_t i = 0; i < 4; ++i)
    {
        _qpoints.append(QPointF(rectangle[i].x, rectangle[i].y));
    }
    painter.drawPolygon(_qpoints);
}

void ICanvas::draw_triangle(QPainter &painter, const Math::Geometry::Triangle &triangle)
{
    QPointF points[3] = {
        QPointF(triangle[0].x, triangle[0].y),
        QPointF(triangle[1].x, triangle[1].y),
        QPointF(triangle[2].x, triangle[2].y)};
    painter.drawPolygon(points, 3);
}

void ICanvas::update()
{
    return QWidget::update();
}

void ICanvas::mousePressEvent(QMouseEvent *event)
{
}

void ICanvas::mouseReleaseEvent(QMouseEvent *event)
{
}

void ICanvas::mouseMoveEvent(QMouseEvent *event)
{
}

void ICanvas::wheelEvent(QWheelEvent *event)
{
}

void ICanvas::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void ICanvas::resizeEvent(QResizeEvent *event)
{
    _scene->set_viewport(0, this->height(), this->width(), 0);
    return QWidget::resizeEvent(event);
}

void ICanvas::keyPressEvent(QKeyEvent *event)
{
    this->key.insert(static_cast<Scenes::Key>(event->key()));
    Scenes::KeyEvent *key_event = new Scenes::KeyEvent(this->key);

    key_event->is_auto_repeat = event->isAutoRepeat();
    _scene->append_event(key_event);

    return QWidget::keyPressEvent(event);
}

void ICanvas::keyReleaseEvent(QKeyEvent *event)
{
    this->key.erase(static_cast<Scenes::Key>(event->key()));
    Scenes::KeyEvent *key_event = new Scenes::KeyEvent(this->key);

    key_event->is_auto_repeat = event->isAutoRepeat();
    _scene->append_event(key_event);

    return QWidget::keyReleaseEvent(event);
}