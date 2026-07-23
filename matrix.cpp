#include <iostream>
#include <vector>
#include <stdexcept>

class Matrix {
private:
    std::vector<std::vector<int>> mtr;
    size_t rows;
    size_t cols;

public:
    Matrix() : rows(0), cols(0) {} // Конструктор по умолчанию

    Matrix(size_t r, size_t c) : rows(r), cols(c), mtr(r, std::vector<int>(c, 0)) {} // Конструктор с размерами

    Matrix(size_t r, size_t c, int value) : rows(r), cols(c), mtr(r, std::vector<int>(c, value)) {} // Конструктор с инициализированным значением

    Matrix(const std::vector<std::vector<int>>& data) : mtr(data), rows(data.size()), cols(data.empty() ? 0 : data[0].size()) {}

    Matrix(const Matrix& other) : mtr(other.mtr), rows(other.rows), cols(other.cols) {} // Конструктор копирования

    Matrix(Matrix&& other) noexcept : mtr(std::move(other.mtr)), rows(other.rows), cols(other.cols) { // Конструктор перемещения
        other.rows = 0;
        other.cols = 0;
    }

    Matrix& operator=(const Matrix& other) { // Копирующее присваивание
        if (this != &other) {
            mtr = other.mtr;
            rows = other.rows;
            cols = other.cols;
        }
        return *this;
    }

    Matrix& operator=(Matrix&& other) noexcept { // Присваивание перемещения
        if (this != &other) {
            mtr = std::move(other.mtr);
            rows = other.rows;
            cols = other.cols;
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }

    int getRows() const { return rows; } // Получить количество строк

    int getCols() const { return cols; } // Получить количество столбцов

    int& operator()(size_t r, size_t c) { // Оператор доступа
        if (r >= rows || c >= cols) throw std::out_of_range("Index out of range");
        return mtr[r][c];
    }

    const int& operator()(size_t r, size_t c) const { // Константный оператор доступа
        if (r >= rows || c >= cols) throw std::out_of_range("Index out of range");
        return mtr[r][c];
    }

    std::vector<int>& operator[](size_t r) { // Оператор доступа к строке
        if (r >= rows) throw std::out_of_range("Index out of range");
        return mtr[r];
    }

    const std::vector<int>& operator[](size_t r) const { // Константный оператор доступа к строке
        if (r >= rows) throw std::out_of_range("Index out of range");
        return mtr[r];
    }

    Matrix operator+(const Matrix& other) const { // Сложение
        if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Matrix sizes do not match for addition");
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = mtr[i][j] + other(i, j);
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const { // Умножение матриц
        if (cols != other.rows) throw std::invalid_argument("Matrix sizes do not match for multiplication");
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    result(i, j) += mtr[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const { // Вычитание
        if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Matrix sizes do not match for subtraction");
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = mtr[i][j] - other(i, j);
            }
        }
        return result;
    }

    Matrix operator*(int scalar) const { // Скалярное умножение
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = mtr[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix& operator+=(const Matrix& other) { // Сложение на месте
        if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Matrix sizes do not match for addition");
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                mtr[i][j] += other(i, j);
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& other) { // Вычитание на месте
        if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Matrix sizes do not match for subtraction");
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                mtr[i][j] -= other(i, j);
            }
        }
        return *this;
    }

    Matrix& operator*=(const Matrix& other) { // Умножение на месте
        return *this = *this * other;
    }

    Matrix& operator*=(int scalar) { // Скалярное умножение на месте
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                mtr[i][j] *= scalar;
            }
        }
        return *this;
    }

    bool operator==(const Matrix& other) const { // Проверка на равенство
        return mtr == other.mtr;
    }

    bool operator!=(const Matrix& other) const { // Проверка на неравенство
        return !(*this == other);
    }

    Matrix transpose() const { // Транспонирование матрицы
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(j, i) = mtr[i][j];
            }
        }
        return result;
    }

    // В данном контексте `mutual` переименован в `inverse`
    Matrix inverse() const {
        // Обработка обратной матрицы (не реализовано в данном примере для упрощения)
        throw std::logic_error("Inverse not implemented");
    }

    static Matrix identity(int size) { // Создание единичной матрицы
        Matrix result(size, size);
        for (int i = 0; i < size; ++i) {
            result(i, i) = 1;
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) { // Вывод в поток
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << matrix.mtr[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Matrix& matrix) { // Ввод из потока
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                is >> matrix.mtr[i][j];
            }
        }
        return is;
    }

    void print() const { // Функция для печати
        std::cout << *this;
    }
};