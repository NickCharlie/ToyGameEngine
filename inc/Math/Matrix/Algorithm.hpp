#pragma once
#include "Matrix/Matrix.hpp"


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Matrix
        {
            double solve_linear_equations(double a, double b);

            std::tuple<double, double> solve_linear_equations(double a0, double b0, double c0, double a1, double b1, double c1);

            bool solve_linear_equations(double *data, const size_t n);

            std::tuple<double, double, double> solve_linear_equations(double a0, double b0, double c0, double d0,
                double a1, double b1, double c1, double d1, double a2, double b2, double c2, double d2);
        }
    }
}