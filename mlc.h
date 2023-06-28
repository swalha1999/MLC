#pragma once
#define DEBUG // remove this line to disable debug messages

#include <iostream>
#include <memory>

typedef unsigned long int size_m;

template <typename T = double>
class Matrix {
private:
    size_m _rows;
    size_m _cols;
    size_m _start_row;
    size_m _start_col;
    size_m _skip;
    bool _is_slice;
    std::shared_ptr<T> _data = nullptr;
    
public:
    
    Matrix(){
        _rows = 0;
        _cols = 0;
        _start_row = 0;
        _start_col = 0;
        _skip = 0;
        _is_slice = false;
        _data = nullptr;
    }

    Matrix(size_m rows, size_m cols){
        _rows = rows;
        _cols = cols;
        _skip = cols;
        _start_row = 0;
        _start_col = 0;
        _is_slice = false;
        #ifdef DEBUG
            
            _data = std::shared_ptr<T>(new T[rows*cols], [](T* ptr) {
                delete[] ptr;
                std::cout << "Memory freed on addreas: " << ptr << std::endl;
            });

        #else
            
            _data = std::shared_ptr<T>(new T[rows*cols]);
        
        #endif

    }

    Matrix(const Matrix<T>& m){
        _rows = m._rows;
        _cols = m._cols;
        _start_row = m._start_row;
        _start_col = m._start_col;
        _skip = m._skip;
        _is_slice = m._is_slice;
        _data = m._data;
    }

    ~Matrix(){
        
        #ifdef DEBUG
        
            std::cout << "Matrix destructor called on tha matrix with address " << this << std::endl;
            std::cout << "the data is shared with " << _data.use_count() << " other matrices on addreas " << _data.get() << std::endl;
        
        #endif

    }

    size_m rows() const {
        return _rows;
    }

    size_m cols() const {
        return _cols;
    }

    std::shared_ptr<T> data() const {
        return _data;
    }
    
    T& operator()(size_m row, size_m col) const {
        size_m row_idx = row + _start_row;
        size_m col_idx = col + _start_col;
        return _data.get()[row_idx*_skip + col_idx];
    }

    T& operator[](size_m idx) const {
        return _data.get()[ _start_row*_skip + _start_col + idx];
    } 
    
    //+= operator
    void operator+=(const Matrix<T>& m){
        if (_rows != m._rows || _cols != m._cols){
            throw std::invalid_argument("Matrix dimensions must agree");
        }
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                (*this)(i, j) += m(i, j);
            }
        }
    }

    //+= operator with scalar
    void operator+=(const T& s){
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                (*this)(i, j) += s;
            }
        }
    }

    //-= operator
    void operator-=(const Matrix<T>& m){
        if (_rows != m._rows || _cols != m._cols){
            throw std::invalid_argument("Matrix dimensions must agree");
        }
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                (*this)(i, j) -= m(i, j);
            }
        }
    }

    //-= operator with scalar
    void operator-=(const T& s){
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                (*this)(i, j) -= s;
            }
        }
    }

    //*= operator with scalar
    void operator*=(const T& s){
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                (*this)(i, j) *= s;
            }
        }
    }

    //*= operator with matrix
    void operator*=(const Matrix<T>& m){

        if (_cols != m._rows){
            throw std::invalid_argument("Can't mutiply Matrix with dimensions " + std::to_string(_rows) + "x" + std::to_string(_cols) + " with Matrix with dimensions " + std::to_string(m._rows) + "x" + std::to_string(m._cols));
        }

        Matrix<T> temp(_rows, m._cols);
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < m._cols; j++){
                for (size_m k = 0; k < _cols; k++){
                    temp(i, j) += (*this)(i, k) * m(k, j);
                }
            }
        }

        *this = temp;
    }

    ///= operator with scalar
    void operator/=(const T& s){
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                (*this)(i, j) /= s;
            }
        }

    }

    //+ operator
    Matrix<T> operator+(const Matrix<T>& m) const {
        Matrix<T> temp = this->copy();
        temp += m;
        return temp;
    }

    Matrix<T> operator+(const T& s) const {
        Matrix<T> temp = this->copy();
        temp += s;
        return temp;
    }

    //- operator
    Matrix<T> operator-(const Matrix<T>& m) const {
        Matrix<T> temp = Matrix<T>(this->_rows, this->_cols);
        temp -= m;
        temp -= *this;
        return temp;
    }

    Matrix<T> operator-(const T& s) const {
        Matrix<T> temp = this->copy();
        temp -= s;
        return temp;
    }

    //* operator with scalar
    Matrix<T> operator*(const T& s) const {
        Matrix<T> temp = this->copy();
        temp *= s;
        return temp;
    }

    //* operator with matrix
    Matrix<T> operator*(const Matrix<T>& m) const {
        Matrix<T> temp = this->copy();
        temp *= m;
        return temp;
    }

    Matrix<T> slice(size_m start_row, size_m start_col, size_m end_row, size_m end_col){
        Matrix<T> m = Matrix<T>();
        m._rows = end_row - start_row;
        m._cols = end_col - start_col;
        m._start_row = this->_start_row + start_row;
        m._start_col = this->_start_col + start_col;
        m._skip = this->_skip;
        m._is_slice = true;
        m._data = this->_data;
        return m;
    }

    void Identity(){
        // check if the matrix is square
        if (_rows != _cols){
            throw std::invalid_argument("Matrix must be square");
        }
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                if (i == j){
                    (*this)(i, j) = 1;
                }
                else{
                    (*this)(i, j) = 0;
                }
            }
        }
    }

    void print() const {
        for (size_m i = 0; i < _rows; i++){
            std::cout << "  | ";
            for (size_m j = 0; j < _cols; j++){
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << "|";
            std::cout << std::endl;
        }
    }

    Matrix<T> copy() const {
        // make a deep copy of the matrix
        Matrix<T> m = Matrix<T>(_rows, _cols);
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                (m)(i, j) = (*this)(i, j);
            }
        }
        return m; 
    }

};

