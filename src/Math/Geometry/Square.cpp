#include "Math/Geometry/Square.hpp"


using namespace ToyGameEngine::Math;

Geometry::Square::Square()
{

}

Geometry::Square::Square(const double x, const double y, const double w)
    : Geometry::Rectangle(x, y, w, w)
{

}

Geometry::Square::Square(const Point &center, const double w)
    : Geometry::Rectangle(center, w, w)
{

}

Geometry::Square::Square(const Square &square)
    : Geometry::Rectangle(square)
{

}

Geometry::Square &Geometry::Square::operator=(const Square &square)
{
    if (this != &square)
    {
        Geometry::Rectangle::operator=(square);
    }
    return *this;
}

Geometry::Square *Geometry::Square::clone() const
{
    return new Geometry::Square(*this);
}

Geometry::Type Geometry::Square::type() const
{
    return Geometry::Type::SQUARE;
}

double Geometry::Square::inner_cicle_radius() const
{
    return width() / 2;
}