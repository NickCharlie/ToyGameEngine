#include "Canvas/Canvas.hpp"
#include "Resource/ResManager.hpp"
#include "Math/Geometry/Point.hpp"

#include <vector>
#include <iostream>
#include <QSize>
#include <QTransform>
#include <future>

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

    if (sp->get_pixmaps_strings().size() <= 0) 
    {
        return;
    }

    QPixmap* map = Resource::ResManager::get_instance().get_pixmap_resource(sp->get_pixmaps_strings()[0]);

    if (map == nullptr)
    {
        std::cout << "cant find sp->_pixmap_state " << sp->get_pixmaps_strings()[0] << std::endl;
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

void ICanvas::draw_background(QPainter &painter, BackGrounds::BackGroundGroup bg)
{

    // if (bg.size() <= 0)
    // {
    //     std::cerr << "bg.size() <= 0" << std::endl;
    //     return;
    // }

    // std::vector<std::vector<Math::Geometry::Point>> points;
    // std::vector<std::vector<QPixmap*>> maps(bg.size());
    
    // for (size_t i = 0; i < bg.size(); ++i)
    // {
    //     for (size_t j = 0; j < bg[i]->get_pixmaps_strings().size(); ++j)
    //     {
    //         maps[i].push_back(bg[i]->get_pixmap(bg[i]->get_pixmaps_strings()[j]));
    //     }
    //     points.push_back(bg[i]->get_points());
    // }

    // for (size_t i = 0; i < maps.size(); ++i)
    // {

    //     const auto& pixmap_strings = bg[i]->get_pixmaps_strings();
    //     if (pixmap_strings.empty()) 
    //     {
    //         std::cerr << "Error: pixmap_strings is empty for background " << i << std::endl;
    //         continue;
    //     }
        
    //     for (size_t j = 0; j < maps[i].size(); ++j)
    //     {

    //         if (maps[i][j] == nullptr)
    //         {
    //             std::cout << "cant find bg pixmap" << std::endl;
    //             continue;
    //         }

    //         QPixmap scaled_map = *(maps[i][j]);

    //         QTransform transform;  
    //         transform.rotate(180);
    //         scaled_map = scaled_map.transformed(QTransform().scale(-1, 1));
    //         scaled_map = scaled_map.transformed(transform, Qt::SmoothTransformation);

    //         painter.drawPixmap(points[i][j].x, points[i][j].y, scaled_map.width(), scaled_map.height(), scaled_map);
    //     }

        if (bg.size() <= 0)
        {
            std::cerr << "bg.size() <= 0" << std::endl;
            return;
        }

        std::vector<std::vector<QPixmap*>> maps(bg.size());
    

        for (size_t i = 0; i < bg.size(); ++i)
        {   
            const auto& pixmapStrings = bg[i]->get_pixmaps_strings();

            // pixmapStrings.size() == 168
            for (size_t j = 0; j < pixmapStrings.size(); ++j)
            {
                maps[i].push_back(bg[i]->get_pixmap(pixmapStrings[j]));
            }
        }

        // for (size_t m = 0; m < maps[0].size(); ++m)
        // {
        //     QPixmap* tmp = maps[0][m];
        //     maps[0][m] = new QPixmap(*maps[0][maps[0].size() - 1]);
        //     maps[0][maps[0].size() - 1] = new QPixmap(*tmp);
        // }

        for (size_t i = 0; i < maps.size(); ++i)
        {
            const auto& points = bg[i]->get_points();
            
            if (maps[i].size() != points.size())
            {
                std::cerr << "Mismatch between maps size (" << maps[i].size() << ") and points size (" << points.size() << ") for background " << i << std::endl;
                continue;
            }

            for (size_t j = 0; j < maps[i].size(); ++j)
            {

                if (j >= points.size())
                {
                    std::cerr << "Index j (" << j << ") out of range in points vector for background " << i << std::endl;
                    continue;
                }

                if (maps[i][j] == nullptr)
                {
                    std::cerr << "can't find bg pixmap: " << bg[i]->get_pixmaps_strings()[j] << std::endl;
                    continue;
                }

                const Math::Geometry::Point& point = points[j];

                QPixmap* map = maps[i][j];

                QPixmap scaled_map = *map;

                // QTransform transform;  
                // transform.rotate(180);
                // scaled_map = scaled_map.transformed(QTransform().scale(-1, 1));
                // scaled_map = scaled_map.transformed(transform, Qt::SmoothTransformation);

                // painter.drawPixmap(0, 0, scaled_map.width(), scaled_map.height(), scaled_map);

                painter.drawPixmap(point.x, point.y, 50, 50, scaled_map);
            }
        }

    // QPixmap* map = (bg[0]->get_pixmap(bg[0]->get_pixmap_state()));
    // for (QPixmap* map : maps)
    // {
    //     if (map == nullptr)
    //     {
    //         std::cout << "cant find bg->_pixmap_state " << std::endl;
    //         return;
    //     }

    //     // QPixmap scaled_map = map->scaled(QWidget::size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //     QPixmap scaled_map = *map;

    //     QTransform transform;  
    //     transform.rotate(180);
    //     scaled_map = scaled_map.transformed(QTransform().scale(-1, 1));
    //     scaled_map = scaled_map.transformed(transform, Qt::SmoothTransformation);

    //     painter.drawPixmap(0, 0, scaled_map.width(), scaled_map.height(), scaled_map);
    // }
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

    // 绘制背景
    std::future<void> background_painter = _canvas_thread_pool->enqueue(
        [this, &painter]() 
        {
             draw_background(painter, _scene->background_groups()[0]); 
        }
    );
    background_painter.get();
    // draw_background(painter, _scene->background_groups()[0]);

    // std::vector<std::future<void>> spirits_painter;

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

                // spirits_painter.push_back(
                //     _canvas_thread_pool->enqueue(
                //         [this, &painter, &spirit]() 
                //         { 
                //             draw_rectangle(painter, static_cast<ShapedSpirit<Geometry::Rectangle> *>(spirit)->shape());
                //             draw_pixmap(painter, spirit,
                //                 static_cast<ShapedSpirit<Geometry::Rectangle> *>(spirit)->shape().width(),
                //                 static_cast<ShapedSpirit<Geometry::Rectangle> *>(spirit)->shape().height());
                //         }
                // ));

                draw_rectangle(painter, static_cast<ShapedSpirit<Geometry::Rectangle> *>(spirit)->shape());
                draw_pixmap(painter, spirit,
                 static_cast<ShapedSpirit<Geometry::Rectangle> *>(spirit)->shape().width(),
                 static_cast<ShapedSpirit<Geometry::Rectangle> *>(spirit)->shape().height());
                break;
            case Geometry::Type::SQUARE:

                // spirits_painter.push_back(
                //     _canvas_thread_pool->enqueue(
                //         [this, &painter, &spirit]() 
                //         { 
                //             draw_rectangle(painter, static_cast<ShapedSpirit<Geometry::Square> *>(spirit)->shape());
                //             draw_pixmap(painter, spirit,
                //                 static_cast<ShapedSpirit<Geometry::Square> *>(spirit)->shape().width(),
                //                 static_cast<ShapedSpirit<Geometry::Square> *>(spirit)->shape().height());
                //         }
                // ));
                draw_rectangle(painter, static_cast<ShapedSpirit<Geometry::Square> *>(spirit)->shape());
                draw_pixmap(painter, spirit,
                 static_cast<ShapedSpirit<Geometry::Square> *>(spirit)->shape().width(),
                 static_cast<ShapedSpirit<Geometry::Square> *>(spirit)->shape().height());
                break;
            case Geometry::Type::AABBRECT:
                draw_rectangle(painter, static_cast<ShapedSpirit<Geometry::AABBRect> *>(spirit)->shape());
                draw_pixmap(painter, spirit,
                 static_cast<ShapedSpirit<Geometry::AABBRect> *>(spirit)->shape().width(),
                 static_cast<ShapedSpirit<Geometry::AABBRect> *>(spirit)->shape().height());
                break;
            case Geometry::Type::CIRCLE:
                draw_circle(painter, static_cast<ShapedSpirit<Geometry::Circle> *>(spirit)->shape());
                draw_pixmap(painter, spirit,
                 static_cast<ShapedSpirit<Geometry::Circle> *>(spirit)->shape().radius,
                 static_cast<ShapedSpirit<Geometry::Circle> *>(spirit)->shape().radius);
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

    // 等待所有线程完成
    // for (auto& future : spirits_painter)
    // {
    //     future.get();
    // }
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