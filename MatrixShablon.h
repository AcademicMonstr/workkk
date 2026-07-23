#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

template <typename T>
class Matrix{
    private:
    std::vector<std::vector<T>> mtr;
    size_t rows;
    size_t cols;

    public:
    Matrix();
    Matrix(size_t, size_t);
    Matrix(size_t, size_t, T);
    ~Matrix() = default;
    Matrix(const std::vector<std::vector<T>> &);
    Matrix(const Matrix&);
    Matrix(Matrix&&)noexcept;
    Matrix& operator=(const Matrix&);
    Matrix& operator=(Matrix&&)noexcept;

    size_t getRows() const;
    size_t getCols() const;

    T& operator()(size_t, size_t);
    const T& operator()(size_t, size_t) const;
    std::vector<T> operator[](size_t);
    const std::vector<T> operator[](size_t) const;

    Matrix operator+(const Matrix&) const;
    Matrix operator*(const Matrix&) const;
    Matrix operator-(const Matrix&) const;
    Matrix operator*(T) const;

    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(const Matrix&);
    Matrix& operator*=(T);

    bool operator==(const Matrix&);
    bool operator!=(const Matrix&);

    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, const Matrix&);
    void print() const;
};

#endif