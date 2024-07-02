#pragma once
#include <QPen>
#include <QWidget>
#include "Canvas_Impl.hpp"
#include "GeometryGroup.hpp"

namespace ToyGameEngine {

	namespace Canvas {
		
		template<typename Shape>
		class ICanvasT : public ICanvas_Impl, public QWidget {
		public:

			ICanvasT(QWidget *parent = nullptr) : QWidget(parent) {}

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

			void draw(QPainter& painter, const Shape &shape);

			void draw_graph() override;

			GeometryGroup& get_group();

			void push_to_group(Math::Geometry::GeometryObject* o);

		private:
            GeometryGroup group;

            void init();

            void draw_cache();

            void draw_select_rect();

        protected:

            void mousePressEvent(QMouseEvent *event) override;

            void mouseReleaseEvent(QMouseEvent *event) override;

            void mouseMoveEvent(QMouseEvent *event) override;

            void wheelEvent(QWheelEvent *event) override;

            void mouseDoubleClickEvent(QMouseEvent *event) override;

            void resizeEvent(QResizeEvent *event) override;

		};

		template<typename Shape>
		void ICanvasT<Shape>::push_to_group(Math::Geometry::GeometryObject* o) {
    		if (group.size() >= 70) {
				return;
			}
			group.append(o);
		}

		template<typename Shape>
		void ICanvasT<Shape>::paintEvent(QPaintEvent *event) {
    		Q_UNUSED(event);
		
		
		}

		template<typename Shape>
		void ICanvasT<Shape>::draw_graph() {
		}

		template<typename Shape>
		void ICanvasT<Shape>::draw_cache() {
			
		}

		template<typename Shape>
		void ICanvasT<Shape>::draw_select_rect() {
			
		}

		template<typename Shape>
		void ICanvasT<Shape>::init() {
			
		}

		template<typename Shape>
		void ICanvasT<Shape>::mousePressEvent(QMouseEvent *event) {

		}

		template<typename Shape>
		void ICanvasT<Shape>::mouseReleaseEvent(QMouseEvent *event) {
			
		}

		template<typename Shape>
		void ICanvasT<Shape>::mouseMoveEvent(QMouseEvent *event) {
			
		}

		template<typename Shape>
		void ICanvasT<Shape>::wheelEvent(QWheelEvent *event) {
			
		}

		template<typename Shape>
		void ICanvasT<Shape>::mouseDoubleClickEvent(QMouseEvent *event) {
			
		}

		template<typename Shape>
		void ICanvasT<Shape>::resizeEvent(QResizeEvent *event) {
			
		}

		template <>
		void ICanvasT<Math::Geometry::Polygon>::draw(QPainter& painter, const Math::Geometry::Polygon& polygon) {
			
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

		template <>
		void ICanvasT<Math::Geometry::Line>::draw(QPainter& painter, const Math::Geometry::Line& line) {
			painter.drawLine(QLineF(QPointF(line.front().x, line.front().y), QPointF(line.back().x, line.back().y)));
		}

		template <>
		void ICanvasT<Math::Geometry::AABBRect>::draw(QPainter& painter, const Math::Geometry::AABBRect& rect) {
			painter.drawRect(QRectF(rect.left(), rect.top(), rect.right(), rect.bottom()));
		}

		template <>
		void ICanvasT<Math::Geometry::Bezier>::draw(QPainter& painter, const Math::Geometry::Bezier& bezier) {
			
			const auto& shape = bezier.shape();

			for (size_t i = 0; i < shape.size() - 1; ++i) {
				const auto& pos1 = shape[i];
				const auto& pos2 = shape[i + 1];

				painter.drawLine(QPointF(pos1.x, pos1.y), QPointF(pos2.x, pos2.y));
			}
		}

		template <>
		void ICanvasT<Math::Geometry::Circle>::draw(QPainter& painter, const Math::Geometry::Circle& circle) {
			
			double centerX = circle.x;
			double centerY = circle.y;
			double radius = circle.radius;

			painter.drawEllipse(QPointF(centerX, centerY), radius, radius);
		}

		template <>
		void ICanvasT<Math::Geometry::Polyline>::draw(QPainter& painter, const Math::Geometry::Polyline& polyline) {
			
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

		template <>
		void ICanvasT<Math::Geometry::Triangle>::draw(QPainter& painter, const Math::Geometry::Triangle& triangle) {
			QPointF points[3] = {
				QPointF(triangle[0].x, triangle[0].y),
				QPointF(triangle[1].x, triangle[1].y),
				QPointF(triangle[2].x, triangle[2].y)
			};

			painter.drawPolygon(points, 3);
		}

		template<>
		void ICanvasT<Math::Geometry::Point>::draw(QPainter& painter, const Math::Geometry::Point& point) {
			painter.drawPoint(QPointF(point.x, point.y));
		}

		template<typename Shape>
		void ICanvasT<Shape>::draw_line(QPainter& painter, Math::Geometry::Line& line) {

    		painter.drawLine(QLineF(QPointF(line.front().x, line.front().y), QPointF(line.back().x, line.back().y)));
		}

		template<typename Shape>
		void ICanvasT<Shape>::draw_rect(QPainter& painter, Math::Geometry::AABBRect& rect) {

			painter.drawRect(QRectF(rect.left(), rect.top(), rect.right(), rect.bottom()));
		}

		template<typename Shape>
		void ICanvasT<Shape>::draw_point(QPainter& painter, Math::Geometry::Point& point) {

			painter.drawPoint(QPointF(point.x, point.y));
		}


		template<typename Shape>
		void ICanvasT<Shape>::draw_bezier(QPainter& painter, Math::Geometry::Bezier& bezier) {

			const auto& shape = bezier.shape();

			for (size_t i = 0; i < shape.size() - 1; ++i) {
				const auto& pos1 = shape[i];
				const auto& pos2 = shape[i + 1];

				painter.drawLine(QPointF(pos1.x, pos1.y), QPointF(pos2.x, pos2.y));
			}
		}

		template<typename Shape>
		void ICanvasT<Shape>::draw_circle(QPainter& painter, Math::Geometry::Circle& circle) {

			double centerX = circle.x;
			double centerY = circle.y;
			double radius = circle.radius;

			painter.drawEllipse(QPointF(centerX, centerY), radius, radius);
		}

		template<typename Shape>
		void ICanvasT<Shape>::draw_polygon(QPainter& painter, Math::Geometry::Polygon& polygon) {

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

		template<typename Shape>
		void ICanvasT<Shape>::draw_polyline(QPainter& painter, Math::Geometry::Polyline& polyline) {

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

		template<typename Shape>
		void ICanvasT<Shape>::draw_triangle(QPainter& painter, Math::Geometry::Triangle& triangle) {
			QPointF points[3] = {
				QPointF(triangle[0].x, triangle[0].y),
				QPointF(triangle[1].x, triangle[1].y),
				QPointF(triangle[2].x, triangle[2].y)
			};

			painter.drawPolygon(points, 3);
		}
	}
}