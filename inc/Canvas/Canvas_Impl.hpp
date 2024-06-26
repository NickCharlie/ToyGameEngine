#pragma once
#include "Math/Geometry/Line.hpp"
#include "Math/Geometry/Point.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Bezier.hpp"
#include "Math/Geometry/Circle.hpp"
#include "Math/Geometry/Polygon.hpp"
#include "Math/Geometry/Polyline.hpp"
#include "Math/Geometry/Triangle.hpp"
#include "Math/Geometry/GeometryObject.hpp"

#include <QPainter>

namespace ToyGameEngine {

	namespace Canvas {

		class ICanvas_Impl {

		public:
			virtual ~ICanvas_Impl() = default;

			virtual void draw_line(QPainter& painter, Math::Geometry::Line& line) = false;

			virtual void draw_rect(QPainter& painter, Math::Geometry::AABBRect& rect) = false;

			virtual void draw_point(QPainter& painter, Math::Geometry::Point& point) = false;

			virtual void draw_bezier(QPainter& painter, Math::Geometry::Bezier& bezier) = false;

			virtual void draw_circle(QPainter& painter, Math::Geometry::Circle& circle) = false;

			virtual void draw_polygon(QPainter& painter, Math::Geometry::Polygon& polygon) = false;

			virtual void draw_polyline(QPainter& painter, Math::Geometry::Polyline& polyline) = false;

			virtual void draw_triangle(QPainter& painter, Math::Geometry::Triangle& triangle) = false;

			virtual void draw_graph() = false;

		};
	}

}
