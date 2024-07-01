#pragma once
#include <tuple>
#include <vector>
#include <cassert>
#include <iostream>


namespace ToyGameEngine
{
    namespace Math
    {
        namespace Matrix
        {
            template <typename T, size_t ROW, size_t COL>
            class Mat
            {
                using MatType = Mat<T, ROW, COL>;

            private:
                T data[ROW * COL] = {0};

            public:
                // 代数余子式法
                struct AlgebraicCofactor
                {
                    static T det(const T *nums, const size_t n)
                    {
                        T *temp = new T[n * n - 2 * n + 1];
                        T result = 0;
                        for (size_t i = 0; i < n; ++i)
                        {
                            for (size_t j = 0; j < i; ++j)
                            {
                                for (size_t k = 1; k < n; ++k)
                                {
                                    temp[(n - 1) * j + k - 1] = nums[n * j + k];
                                }
                            }
                            for (size_t j = i + 1; j < n; ++j)
                            {
                                for (size_t k = 1; k < n; ++k)
                                {
                                    temp[(n - 1) * (j - 1) + k - 1] = nums[n * j + k];
                                }
                            }

                            if (i % 2 == 1)
                            {
                                result += (nums[i * n] * det(temp, n - 1));
                            }
                            else
                            {
                                result -= (nums[i * n] * det(temp, n - 1));
                            }
                        }
                        delete[] temp;
                        return result;
                    }
                };

                // 三角矩阵法
                struct TriangularDeterminant
                {
                    static T det(const T *nums, const size_t n)
                    {
                        T temp[ROW * COL];
                        std::memmove(temp, nums, ROW * COL * sizeof(T));
                        T result;
                        for (size_t i = 0; i < ROW - 1; ++i)
                        {
                            if (temp[ROW * i + i] == 0)
                            {
                                for (size_t j = i + 1; j < ROW; ++j)
                                {
                                    if (temp[j * ROW] != 0)
                                    {
                                        for (size_t k = i; k < COL; ++k)
                                        {
                                            temp[ROW * i + k] += temp[ROW * j + k];
                                        }
                                        break;
                                    }
                                }
                                if (temp[ROW * i + i] == 0)
                                {
                                    continue;
                                }
                            }

                            for (size_t j = i + 1; j < ROW; ++j)
                            {
                                result = temp[ROW * j + i] / temp[ROW * i + i];
                                for (size_t k = i; k < COL; ++k)
                                {
                                    temp[ROW * j + k] -= (temp[ROW * i + k] * result);
                                }
                            }
                        }
                        for (size_t i = 0; i < ROW * COL; ++i)
                        {
                            if (std::isnan(temp[i]) || std::isinf(temp[i]))
                            {
                                temp[i] = 0;
                            }
                        }
                        result = 1;
                        for (size_t i = 0; i < ROW; ++i)
                        {
                            result *= temp[ROW * i + i];
                        }
                        return result == -0 ? 0 : result;
                    }
                };

                friend std::ostream &operator<<(std::ostream &o, const MatType &mat)
                {
                    o << "Type: " << typeid(T).name() << ", Size: " << ROW << ',' << COL << " Data:\n[";
                    size_t index = 0;
                    for (size_t i = 0; i < ROW - 1; ++i)
                    {
                        o << '[';
                        for (size_t j = 0; j < COL - 1; ++j)
                        {
                            o << mat.data[index++] << ',';
                        }
                        o << mat.data[index++] << "],\n";
                    }
                    o << '[';
                    for (size_t j = 0; j < COL - 1; ++j)
                    {
                        o << mat.data[index++] << ',';
                    }
                    o << mat.data[index++] << "]]";
                    return o;
                }

            public:
                // 默认填充0的矩阵
                Mat() {}

                // 用value填充的矩阵
                Mat(const T value)
                {
                    std::fill_n(this->data, ROW * COL, value);
                }

                // 对角矩阵,value是对角线值,other是填充值
                template <typename = std::enable_if_t<ROW == COL>>
                Mat(const T value, const T other)
                {
                    std::fill_n(this->data, ROW * COL, other);
                    for (size_t i = 0; i < ROW; ++i)
                    {
                        this->data[ROW * i + i] = value;
                    }
                }

                Mat(const std::initializer_list<T> &numbers)
                {
                    assert(numbers.size() >= ROW * COL);
                    size_t index = 0;
                    for (T number : numbers)
                    {
                        this->data[index++] = number;
                        if (index >= ROW * COL)
                        {
                            break;
                        }
                    }
                }

                Mat(const std::vector<T> &numbers)
                {
                    assert(numbers.size() >= ROW * COL);
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        this->data[i] = numbers[i];
                    }
                }

                Mat(const T numbers[ROW * COL])
                {
                    std::memmove(data, numbers, sizeof(T) * ROW * COL);
                }

                Mat(const MatType &mat)
                {
                    std::memmove(this->data, mat.data, sizeof(T) * ROW * COL);
                }

                template <typename R>
                Mat(const Mat<R, ROW, COL> &mat)
                {
                    for (size_t i = 0; i < ROW; ++i)
                    {
                        for (size_t j = 0; j < COL; ++j)
                        {
                            this->data[COL * i + j] = mat.get(i, j);
                        }
                    }
                }

                bool set(const size_t row, const size_t col, const T value)
                {
                    if (row < ROW && col < COL)
                    {
                        this->data[row * COL + col] = value;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }

                // 尝试获取矩阵元素
                T get(const size_t row, const size_t col) const
                {
                    assert(row < ROW && col < COL);
                    return this->data[row * COL + col];
                }

                // 尝试获取矩阵元素,若不存在则返回value
                T get(const size_t row, const size_t col, const T value) const
                {
                    if (row < ROW && col < COL)
                    {
                        return this->data[row * COL + col];
                    }
                    else
                    {
                        return value;
                    }
                }

                // 元素全部置为0
                void clear()
                {
                    std::fill_n(this->data, ROW * COL, 0);
                }

                // 用value填充矩阵
                void fill(const T value)
                {
                    std::fill_n(this->data, ROW * COL, value);
                }

                // 将inf值改为value
                void clear_inf(const T value = 0)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        if (std::isinf(this->data[i]))
                        {
                            this->data[i] = value;
                        }
                    }
                }

                // 将nan值改为value
                void clear_nan(const T value = 0)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        if (std::isnan(this->data[i]))
                        {
                            this->data[i] = value;
                        }
                    }
                }

                bool has_inf() const
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        if (std::isinf(this->data[i]))
                        {
                            return true;
                        }
                    }
                    return false;
                }

                bool has_nan() const
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        if (std::isnan(this->data[i]))
                        {
                            return true;
                        }
                    }
                    return false;
                }

                bool is_all(const T value) const
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        if (this->data[i] != value)
                        {
                            return false;
                        }
                    }
                    return true;
                }

                bool has(const T value) const
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        if (this->data[i] == value)
                        {
                            return true;
                        }
                    }
                    return false;
                }

                size_t count(const T value) const
                {
                    size_t num = 0;
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        if (this->data[i] == value)
                        {
                            ++num;
                        }
                    }
                    return num;
                }

                template <typename UnaryPred>
                size_t count_if(UnaryPred p)
                {
                    size_t num = 0;
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        if (p(this->data[i]))
                        {
                            ++num;
                        }
                    }
                    return num;
                }

                template <typename UnaryPred>
                void for_each(UnaryPred p)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        this->data[i] = p(this->data[i]);
                    }
                }

                MatType &operator=(const MatType &mat)
                {
                    if (this != &mat)
                    {
                        std::memmove(this->data, mat.data, sizeof(T) * ROW * COL);
                    }
                    return *this;
                }

                bool operator==(const MatType &mat) const
                {
                    if (this == &mat)
                    {
                        return true;
                    }
                    else
                    {
                        return std::memcmp(this->data, mat.data, sizeof(T) * ROW * COL) == 0;
                    } 
                }

                MatType operator-() const
                {
                    MatType mat;
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        mat.data[i] = -(this->data[i]);
                    }
                    return mat;
                }

                // 各元素+value
                MatType operator+(const T value) const
                {
                    MatType result;
                    for (size_t i = 0; i < ROW * ROL; ++i)
                    {
                        result.data[i] = this->data[i] + value;
                    }
                    return result;
                }

                // 各元素-value
                MatType operator-(const T value) const
                {
                    MatType result;
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        result.data[i] = this->data[i] - value;
                    }
                    return result;
                }

                // 各元素*value
                MatType operator*(const T value) const
                {
                    MatType result;
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        result.data[i] = this->data[i] * value;
                    }
                    return result;
                }

                // 各元素/value
                MatType operator/(const T value) const
                {
                    MatType result;
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        result.data[i] = this->data[i] / value;
                    }
                    return result;
                }

                // 各元素对应+
                MatType operator+(const MatType &mat) const
                {
                    MatType result;
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        result.data[i] = this->data[i] + mat.data[i];
                    }
                    return result;
                }

                // 各元素对应-
                MatType operator-(const MatType &mat) const
                {
                    MatType result;
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        result.data[i] = this->data[i] - mat.data[i];
                    }
                    return result;
                }

                // 各元素对应*
                MatType mul(const MatType &mat) const
                {
                    MatType result;
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        result.data[i] = this->data[i] * mat.data[i];
                    }
                    return result;
                }

                // 各元素对应/
                MatType operator/(const MatType &mat) const
                {
                    MatType result;
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        result.data[i] = this->data[i] / mat.data[i];
                    }
                    return result;
                }

                // 各元素+value
                void operator+=(const T value)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        this->data[i] += value;
                    }
                }

                // 各元素-value
                void operator-=(const T value)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        this->data[i] -= value;
                    }
                }

                // 各元素*value
                void operator*=(const T value)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        this->data[i] *= value;
                    }
                }

                // 各元素/value
                void operator/=(const T value)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        this->data[i] /= value;
                    }
                }

                // 各元素对应+
                void operator+=(const MatType &mat)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        this->data[i] += mat.data[i];
                    }
                }

                // 各元素对应-
                void operator-=(const MatType &mat)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        this->data[i] -= mat.data[i];
                    }
                }

                // 各元素对应*
                void inplace_mul(const MatType &mat)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        this->data[i] *= mat.data[i];
                    }
                }

                // 各元素对应/
                void operator/=(const MatType &mat)
                {
                    for (size_t i = 0; i < ROW * COL; ++i)
                    {
                        this->data[i] /= mat.data[i];
                    }
                }

                // 矩阵乘法
                template <size_t M>
                Mat<T, ROW, M> operator*(const Mat<T, COL, M> &mat) const
                {
                    Mat<T, ROW, M> result;
                    for (size_t i = 0; i < ROW; ++i)
                    {
                        for (size_t k = 0; k < COL; ++k)
                        {
                            for (size_t j = 0; j < M; ++j)
                            {
                                result.set(i , j, result.get(i , j) + this->data[i * COL + k] * mat.get(k, j));
                            }
                        }
                    }
                    return result;
                }

                // 矩阵乘法
                void operator*=(const MatType &mat)
                {
                    T temp[ROW * COL];
                    std::memmove(temp, this->data, ROW * COL * sizeof(T));
                    for (size_t i = 0; i < ROW; ++i)
                    {
                        for (size_t k = 0; k < COL; ++k)
                        {
                            for (size_t j = 0; j < M; ++j)
                            {
                                this->data[i * M + j] += (temp[i * COL + k] * mat.data[k * COL + j]);
                            }
                        }
                    }
                }

                Mat<T, COL, ROW> transpose() const
                {
                    Mat<T, COL, ROW> result;
                    for (size_t i = 0; i < COL; ++i)
                    {
                        for (size_t j = 0; j < ROW; ++j)
                        {
                            result.set(i, j, this->data[j * COL + i]);
                        }
                    }
                    return result;
                }

                template <typename Algorithm = AlgebraicCofactor, typename = std::enable_if_t<ROW == COL>>
                T det() const
                {
                    if constexpr (ROW == 1)
                    {
                        return data[0];
                    }
                    else if constexpr (ROW == 2)
                    {
                        return data[0] * data[3] - data[1] * data[2];
                    }
                    else if constexpr (ROW == 3)
                    {
                        return data[0] * data[4] * data[8]
                            + data[1] * data[5] * data[6]
                            + data[2] * data[3] * data[7]
                            - data[2] * data[4] * data[6]
                            - data[1] * data[3] * data[8]
                            - data[0] * data[5] * data[7]; 
                    }
                    else
                    {
                        return Algorithm::det(this->data, ROW);
                    }
                }

                template <typename = std::enable_if_t<ROW == COL>>
                std::tuple<MatType, MatType> lower_upper_factorize() const
                {
                    MatType lower_mat(1, 0), upper_mat(*this);
                    for (size_t i = 0; i < ROW - 1; ++i)
                    {
                        if (upper_mat.data[ROW * i + i] == 0)
                        {
                            for (size_t j = i + 1; j < ROW; ++j)
                            {
                                if (upper_mat.data[j * ROW] != 0)
                                {
                                    for (size_t k = i; k < COL; ++k)
                                    {
                                        upper_mat.data[ROW * i + k] += upper_mat.data[ROW * j + k];
                                    }
                                    break;
                                }
                            }
                            if (upper_mat.data[ROW * i + i] == 0)
                            {
                                continue;
                            }
                        }

                        for (size_t j = i + 1; j < ROW; ++j)
                        {
                            lower_mat.data[ROW * j + i] = upper_mat.data[ROW * j + i] / upper_mat.data[ROW * i + i];
                            for (size_t k = i; k < COL; ++k)
                            {
                                upper_mat.data[ROW * j + k] -= (upper_mat.data[ROW * i + k] * lower_mat.data[ROW * j + i]);
                            }
                        }
                    }
                    lower_mat.clear_inf();
                    lower_mat.clear_nan();
                    upper_mat.clear_inf();
                    upper_mat.clear_nan();
                    return std::make_tuple(lower_mat, upper_mat);
                }

                template <typename = std::enable_if_t<ROW == COL>>
                MatType upper_triangular_matrix() const
                {
                    MatType mat(*this);
                    T temp;
                    for (size_t i = 0; i < ROW - 1; ++i)
                    {
                        if (mat.data[ROW * i + i] == 0)
                        {
                            for (size_t j = i + 1; j < ROW; ++j)
                            {
                                if (mat.data[j * ROW] != 0)
                                {
                                    for (size_t k = i; k < COL; ++k)
                                    {
                                        mat.data[ROW * i + k] += mat.data[ROW * j + k];
                                    }
                                    break;
                                }
                            }
                            if (mat.data[ROW * i + i] == 0)
                            {
                                continue;
                            }
                        }

                        for (size_t j = i + 1; j < ROW; ++j)
                        {
                            temp = mat.data[ROW * j + i] / mat.data[ROW * i + i];
                            for (size_t k = i; k < COL; ++k)
                            {
                                mat.data[ROW * j + k] -= (mat.data[ROW * i + k] * temp);
                            }
                        }
                    }
                    mat.clear_inf();
                    mat.clear_nan();
                    return mat;
                }

                template <typename = std::enable_if_t<ROW == COL>>
                MatType lower_triangular_matrix() const
                {
                    MatType mat(*this);
                    T temp;
                    for (size_t i = ROW - 1; i > 0; --i)
                    {
                        if (mat.data[ROW * i + i] == 0)
                        {
                            for (size_t j = 0; j < i; ++j)
                            {
                                if (mat.data[j * ROW] != 0)
                                {
                                    for (size_t k = i; k < COL; ++k)
                                    {
                                        mat.data[ROW * i + k] += mat.data[ROW * j + k];
                                    }
                                    break;
                                }
                            }
                            if (mat.data[ROW * i + i] == 0)
                            {
                                continue;
                            }
                        }

                        for (size_t j = 0; j < i; ++j)
                        {
                            temp = mat.data[ROW * j + i] / mat.data[ROW * i + i];
                            for (size_t k = 0; k <= i; ++k)
                            {
                                mat.data[ROW * j + k] -= (mat.data[ROW * i + k] * temp);
                            }
                        }
                    }
                    mat.clear_inf();
                    mat.clear_nan();
                    return mat;
                }

                template <typename = std::enable_if_t<ROW == COL>>
                void to_upper_triangular_matrix()
                {
                    T temp;
                    for (size_t i = 0; i < ROW - 1; ++i)
                    {
                        if (this->data[ROW * i + i] == 0)
                        {
                            for (size_t j = i + 1; j < ROW; ++j)
                            {
                                if (this->data[j * ROW] != 0)
                                {
                                    for (size_t k = i; k < COL; ++k)
                                    {
                                        this->data[ROW * i + k] += this->data[ROW * j + k];
                                    }
                                    break;
                                }
                            }
                            if (this->data[ROW * i + i] == 0)
                            {
                                continue;
                            }
                        }

                        for (size_t j = i + 1; j < ROW; ++j)
                        {
                            temp = this->data[ROW * j + i] / this->data[ROW * i + i];
                            for (size_t k = i; k < COL; ++k)
                            {
                                this->data[ROW * j + k] -= (this->data[ROW * i + k] * temp);
                            }
                        }
                    }
                    this->clear_inf();
                    this->clear_nan();
                }

                template <typename = std::enable_if_t<ROW == COL>>
                void to_lower_triangular_matrix()
                {
                    T temp;
                    for (size_t i = ROW - 1; i > 0; --i)
                    {
                        if (this->data[ROW * i + i] == 0)
                        {
                            for (size_t j = 0; j < i; ++j)
                            {
                                if (this->data[j * ROW] != 0)
                                {
                                    for (size_t k = i; k < COL; ++k)
                                    {
                                        this->data[ROW * i + k] += this->data[ROW * j + k];
                                    }
                                    break;
                                }
                            }
                            if (this->data[ROW * i + i] == 0)
                            {
                                continue;
                            }
                        }

                        for (size_t j = 0; j < i; ++j)
                        {
                            temp = this->data[ROW * j + i] / this->data[ROW * i + i];
                            for (size_t k = 0; k <= i; ++k)
                            {
                                this->data[ROW * j + k] -= (this->data[ROW * i + k] * temp);
                            }
                        }
                    }
                    this->clear_inf()
                    this->clear_nan();
                }

                template <typename = std::enable_if_t<ROW == COL>>
                size_t rank() const
                {
                    if constexpr (ROW == 0)
                    {
                        return 0;
                    }
                    else if constexpr (ROW == 1)
                    {
                        return this->data[0] == 0 ? 0 : 1;
                    }
                    else
                    {
                        T temp, nums[ROW * COL];
                        std::memmove(nums, this->data, ROW * COL * sizeof(T));
                        for (size_t i = 0; i < ROW - 1; ++i)
                        {
                            for (size_t j = i + 1; j < ROW; ++j)
                            {
                                temp = nums[ROW * j + i] / nums[ROW * i + i];
                                for (size_t k = i; k < COL; ++k)
                                {
                                    nums[ROW * j + k] -= (nums[ROW * i + k] * temp);
                                }
                            }
                        }
                        for (size_t i = 0; i < ROW * COL; ++i)
                        {
                            if (std::isnan(nums[i]) || std::isinf(nums[i]))
                            {
                                nums[i] = 0;
                            }
                        }

                        size_t result = 0;
                        for (size_t count = 0, i = 0; i < ROW * COL;)
                        {
                            if (nums[i++] == 0)
                            {
                                ++count;
                            }
                            if (i % COL == 0)
                            {
                                if (count < COL)
                                {
                                    ++result;
                                }
                                count = 0;
                            }
                        }
                        return result;
                    }
                }
            
                template <typename = std::enable_if_t<ROW == COL>>
                T cofactor(const size_t row, const size_t col) const
                {
                    Mat<T, ROW - 1, COL - 1> mat;
                    for (size_t i = 0; i < row; ++i)
                    {
                        for (size_t j = 0; j < col; ++j)
                        {
                            mat.set(i, j, this->data[COL * i + j]); 
                        }
                        for (size_t j = col + 1; j < COL; ++j)
                        {
                            mat.set(i, j - 1, this->data[COL * i + j]); 
                        }
                    }
                    for (size_t i = row + 1; i < ROW; ++i)
                    {
                        for (size_t j = 0; j < col; ++j)
                        {
                            mat.set(i - 1, j, this->data[COL * i + j]); 
                        }
                        for (size_t j = col + 1; j < COL; ++j)
                        {
                            mat.set(i - 1, j - 1, this->data[COL * i + j]); 
                        }
                    }
                    return mat.det();
                }

                template <typename = std::enable_if_t<ROW == COL>>
                T algebraic_cofactor(const size_t row, const size_t col) const
                {
                    return (row + col) % 2 == 0 ? cofactor(row, col) : -cofactor(row, col); 
                }

                template <typename = std::enable_if_t<ROW == COL>>
                MatType adjugate_matrix() const
                {
                    MatType mat;
                    for (size_t i = 0; i < ROW; ++i)
                    {
                        for (size_t j = 0; j < COL; ++j)
                        {
                            mat.data[COL * j + i] = algebraic_cofactor(i, j);
                        }
                    }
                    return mat;
                }

                template <typename = std::enable_if_t<ROW == COL>>
                MatType inverse() const
                {
                    if (det() == 0)
                    {
                        return MatType(std::nan("nan"));
                    }
                    MatType mat;
                    for (size_t i = 0; i < ROW; ++i)
                    {
                        for (size_t j = 0; j < COL; ++j)
                        {
                            mat.data[COL * j + i] = algebraic_cofactor(i, j);
                        }
                    }
                    mat /= det();
                    return mat;
                }
            };

            using Mat2d = Mat<double, 2, 2>;
            using Mat2i = Mat<int, 2, 2>;
            using Mat2f = Mat<float, 2, 2>;

            using Mat3d = Mat<double, 3, 3>;
            using Mat3i = Mat<int, 3, 3>;
            using Mat3f = Mat<float, 3, 3>;

            using Mat4d = Mat<double, 4, 4>;
            using Mat4i = Mat<int, 4, 4>;
            using Mat4f = Mat<float, 4, 4>;

            using Mat2d1 = Mat<double, 2, 1>;
            using Mat2i1 = Mat<int, 2, 1>;
            using Mat2f1 = Mat<float, 2, 1>;

            using Mat3d1 = Mat<double, 3, 1>;
            using Mat3i1 = Mat<int, 3, 1>;
            using Mat3f1 = Mat<float, 3, 1>;

            using Mat4d1 = Mat<double, 4, 1>;
            using Mat4i1 = Mat<int, 4, 1>;
            using Mat4f1 = Mat<float, 4, 1>;

            using Mat1d2 = Mat<double, 1, 2>;
            using Mat1i2 = Mat<int, 1, 2>;
            using Mat1f2 = Mat<float, 1, 2>;

            using Mat1d3 = Mat<double, 1, 3>;
            using Mat1i3 = Mat<int, 1, 3>;
            using Mat1f3 = Mat<float, 1, 3>;

            using Mat1d4 = Mat<double, 1, 4>;
            using Mat1i4 = Mat<int, 1, 4>;
            using Mat1f4 = Mat<float, 1, 4>;

        }
    }
}