#include "Matrix.h"

template <typename T>
Matrix<T>::Matrix() : rows(0), cols(0) {}

template <typename T>
Matrix<T>::Matrix(size_t r, size_t c) : rows(r), cols(c), mtr(r, std::vector<T> (c)) {}

template <typename T>
Matrix<T>::Matrix(size_t r, size_t c, T value) : rows(r), cols(c), mtr(r, std::vector<T> (c, value)) {} //сделать черещ resize

template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> &other){
    size_t temp = other[0].size();
    for(std::vector<T> row : other){
        if(row.size() != temp){
            throw std::invalid_argument("isnt matrix");
        }
    }
    this->mtr = other;
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) : mtr(other.mtr), rows(other.rows), cols(other.cols) {}

template <typename T>
Matrix<T>::Matrix(Matrix&& other)noexcept : mtr(std::move(other.mtr)), rows(other.rows), cols(other.cols){
    other.rows = 0;
    other.cols = 0;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other){
    if(this != &other){
        mtr = other.mtr;
        rows = other.rows;
        cols = other.cols;
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other)noexcept{
    if(this != &other){
        mtr = std::move(other.mtr);
        rows = other.rows;
        cols = other.cols;
        other.cols = 0;
        other.rows = 0;
    }
    return *this;
}

template <typename T>
size_t Matrix<T>::getRows() const{
    return rows;
}

template <typename T>
size_t Matrix<T>::getCols() const{
    return cols;
}

template <typename T>
T& Matrix<T>::operator()(size_t r, size_t c){
    if(r >= rows || c >= cols){
        throw std::out_of_range("Out of range");
    }
    return mtr[r][c];
}

template <typename T>
const T& Matrix<T>::operator()(size_t r, size_t c) const{
    if(r >= rows || c >= cols){
        throw std::out_of_range("Out of range");
    }
    return mtr[r][c];
}

template <typename T>
std::vector<T> Matrix<T>::operator[](size_t r){
    return mtr[r];
}

template <typename T>
const std::vector<T> Matrix<T>::operator[](size_t r) const{
    return mtr[r];
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const{
    if(rows != other.rows || cols != other.cols){
        throw std::invalid_argument("Rows or Cols don't match");
    }
    Matrix result(*this);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            result[i][j] += other[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const{
    if(cols != other.rows){
        throw std::invalid_argument("don't match rows and cols for multiply matrix");
    }
    Matrix result(rows, other.cols);
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < other.cols; ++j){
            for(int k = 0; k < cols; ++k)
            result[i][j] = mtr[i][k] * other.mtr[k][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const{
    if(rows != other.rows || cols != other.cols){
        throw std::invalid_argument("Rows or Cols don't match");
    }
    Matrix result(*this);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            result[i][j] -= other[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T num) const{
    Matrix result(*this);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            result[i][j] *= num;
        }
    }
    return result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& other){
    if(rows != other.rows || cols != other.cols){
        throw std::invalid_argument("Rows or Cols don't match");
    }
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            mtr[i][j] += other[i][j];
        }
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& other){
    if(rows != other.rows || cols != other.cols){
        throw std::invalid_argument("Rows or Cols don't match");
    }
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            mtr[i][j] -= other[i][j];
        }
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix& other){
    if(cols != other.rows){
        throw std::out_of_range("Rows or Cols don't match");
    }
    Matrix result(*this);
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            mtr[i][j] *= other[i][j];
        }
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T num){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mtr[i][j] *= num;
        }
    }
    return *this;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& other){
    if(rows != other.rows || cols != other.cols){
        return false;
    }
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            if(mtr[i][j] == other[i][j]){
                return true;
            }
        }
    }
    return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix& other){ return !(*this == other);}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mtr) {
    for (size_t i = 0; i < mtr.getRows(); i++) {
        for (size_t j = 0; j < mtr.getCols(); j++) {
            os << mtr(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& mtr) {
    for (size_t i = 0; i < mtr.getRows(); i++) {
        for (size_t j = 0; j < mtr.getCols(); j++) {
            is >> mtr(i, j);
        }
    }
    return is;
}





















template <typename T>
void Matrix<T>::print() const{
    for( std::vector<T> i : mtr ){
        for( int j : i ){
            std::cout << j << '\t';
        }
        std::cout <<std::endl;
    }
}
