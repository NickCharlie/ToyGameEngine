#pragma once
#include <QPen>
#include <QWidget>
#include "Canvas_Impl.hpp"
#include "GeometryGroup.hpp"

namespace ToyGameEngine {

	namespace Canvas {
		
		template<typename Shape>
		class ICanvasT : public ICanvas_Impl, public QWidget {
			Q_OBJECT
		public:
			QPainter* m_painter;

			ICanvasT(QPainter* painter) : m_painter(painter) {}

			// 绘图事件
            void paintEvent(QPaintEvent *event) override;

			void draw(const Shape &shape);

			void draw_graph() override;

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

		template <>
		void ICanvasT<Math::Geometry::Polygon>::draw(const Math::Geometry::Polygon& polygon) {

		}

		template <>
		void ICanvasT<Math::Geometry::Line>::draw(const Math::Geometry::Line& line) {

		}

		template <>
		void ICanvasT<Math::Geometry::AABBRect>::draw(const Math::Geometry::AABBRect& rect) {

		}

		template <>
		void ICanvasT<Math::Geometry::Bezier>::draw(const Math::Geometry::Bezier& bezier) {

		}

		template <>
		void ICanvasT<Math::Geometry::Circle>::draw(const Math::Geometry::Circle& circle) {

		}

		template <>
		void ICanvasT<Math::Geometry::Polyline>::draw(const Math::Geometry::Polyline& polyline) {

		}

		template <>
		void ICanvasT<Math::Geometry::Triangle>::draw(const Math::Geometry::Triangle& triangle) {

		}

	}
}