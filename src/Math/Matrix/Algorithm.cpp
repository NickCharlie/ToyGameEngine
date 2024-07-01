#include "Matrix/Algorithm.hpp"


using namespace ToyGameEngine::Math;

double Matrix::solve_linear_equations(double a, double b)
{
    return -b / a;
}

std::tuple<double, double> Matrix::solve_linear_equations(double a0, double b0, double c0, double a1, double b1, double c1)
{
    if (a0 * a1 != 0)
    {
        const double y = (a0 * c1 - a1 * c0) / (a1 * b0 - a0 * b1);
        return std::make_tuple((-b0 * y - c0) / a0,  y);
    }
    else if (b0 * b1 != 0)
    {
        const double x = (b0 * c1 - b1 * c0) / (b1 * a0 - b0 * a1);
        return std::make_tuple(x,  (-a0 * x - c0) / b0);
    }
    else
    {
        if (b0 == 0 && a1 == 0 && a0 != 0 && b1 != 0)
        {
            return std::make_tuple(-c0 / a0, -c1 / b1);
        }
        else if (a0 == 0 && b1 == 0 && a1 != 0 && b0 != 0)
        {
            return std::make_tuple(-c1 / a1, -c0 / b0);
        }
        else
        {
            return std::make_tuple(std::nan("nan"), std::nan("nan"));
        }
    }
}

bool Matrix::solve_linear_equations(double *data, const size_t n)
{
    for (size_t i = 0; i < n - 1; ++i)
    {
        if (data[(n + 2) * i] == 0)
        {
            for (size_t j = i + 1; j < n + 1; ++j)
            {
                if (data[j * (n + 1)] != 0)
                {
                    for (size_t k = i; k < n + 1; ++k)
                    {
                        data[(n + 1) * i + k] += data[(n + 1) * j + k];
                    }
                    break;
                }
            }
            if (data[(n + 1) * i] == 0)
            {
                continue;
            }
        }

        for (size_t j = i + 1; j < n; ++j)
        {
            double temp = data[(n + 1) * j + i] / data[(n + 2) * i];
            for (size_t k = i; k < n + 1; ++k)
            {
                data[(n + 1) * j + k] -= (data[(n + 1) * i + k] * temp);
            }
        }
    }
    if (data[(n + 2) * n - 1] == 0)
    {
        return false;
    }

    for (size_t i = n; i < n * n + n; i += (n + 1))
    {
        data[i] = (-data[i]);
    }
    for (size_t i = n - 1; i > 0; --i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            data[(n + 1) * i + n] -= (data[(n + 1) * i + j] * data[(n + 1) * j + n]);
        }
        data[(n + 1) * i + n] /= data[(n + 2) * i];
    }
    for (size_t j = 1; j < n; ++j)
    {
        data[n] -= (data[j] * data[(n + 1) * j + n]);
    }
    data[n] /= data[0];
    for (size_t i = 0, j = n; j < n * n + n; j += (n + 1))
    {
        data[i++] = data[j];
    }
    return true;
}

std::tuple<double, double, double> Matrix::solve_linear_equations(double a0, double b0, double c0, double d0,
    double a1, double b1, double c1, double d1, double a2, double b2, double c2, double d2)
{
    double data[12] = {a0, b0, c0, d0, a1, b1, c1, d1, a2, b2, c2, d2};
    if (Matrix::solve_linear_equations(data, 3))
    {
        return std::make_tuple(data[0], data[1], data[2]);
    }
    else
    {
        return std::make_tuple(std::nan("nan"), std::nan("nan"), std::nan("nan"));
    }
}

