#pragma once

#include <QPainter>
#include "Math/Geometry/Line.hpp"
#include "Math/Geometry/AABBRect.hpp"
#include "Math/Geometry/Bezier.hpp"
#include "Math/Geometry/Circle.hpp"
#include "Math/Geometry/Polygon.hpp"
#include "Math/Geometry/Triangle.hpp"
#include "Math/Geometry/Square.hpp"
#include "Math/Geometry/GeometryObject.hpp"
#include "Scene/Scene.hpp"

namespace ToyGameEngine 
{

	namespace Canvas 
	{

		class ICanvas_Impl 
		{

		protected:
			Scenes::Scene *_scene = nullptr;

		public:
			virtual ~ICanvas_Impl() {}

			virtual void draw_line(QPainter& painter, const Math::Geometry::Line& line) = 0;

			virtual void draw_rectangle(QPainter& painter, const Math::Geometry::AABBRect& rect) = 0;

			virtual void draw_rectangle(QPainter& painter, const Math::Geometry::Rectangle& rect) = 0;

			virtual void draw_point(QPainter& painter, const Math::Geometry::Point& point) = 0;

			virtual void draw_bezier(QPainter& painter, const Math::Geometry::Bezier& bezier) = 0;

			virtual void draw_circle(QPainter& painter, const Math::Geometry::Circle& circle) = 0;

			virtual void draw_polygon(QPainter& painter, const Math::Geometry::Polygon& polygon) = 0;

			virtual void draw_polyline(QPainter& painter, const Math::Geometry::Polyline& polyline) = 0;

			virtual void draw_triangle(QPainter& painter, const Math::Geometry::Triangle& triangle) = 0;

			virtual void draw_scene() = 0;

			virtual void load_scene(Scenes::Scene *scene)
			{
				_scene = scene;
			}

		};
	}

}
