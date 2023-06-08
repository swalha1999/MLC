#pragma once

#include <iostream>

typedef unsigned long size_m;

class Matrix {
private:
    size_m _rows;
    size_m _cols;
    size_m _skip;
    bool _is_slice;
    double* _data = nullptr;
    
public:

    Matrix(){
        _rows = 0;
        _cols = 0;
        _skip = 0;
        _is_slice = false;
        _data = nullptr;
    }

    Matrix(int rows, int cols){
        _rows = rows;
        _cols = cols;
        _skip = cols;
        _is_slice = false;
        _data = new double[rows*cols];
    }

    Matrix(const Matrix& m){
        _rows = m._rows;
        _cols = m._cols;
        _skip = m._skip;
        _is_slice = m._is_slice;
        _data = m._data;
    }

    ~Matrix(){
        if (_data != nullptr && !_is_slice) delete[] _data;
    }

    Matrix& operator=(const Matrix& m){
        if (this != &m){
            
            if (_data != nullptr && !_is_slice){
                delete[] _data;
            }
            
            _rows = m._rows;
            _cols = m._cols;
            _skip = m._skip;
            _data = m._data;
            _is_slice = m._is_slice;

        }

        return *this;
    }
    
    Matrix& operator+(const Matrix& m) const {
        if (_rows != m._rows || _cols != m._cols){
            throw std::invalid_argument("Matrix dimensions must agree");
        }
        Matrix* result = new Matrix(_rows, _cols);
        for (size_m i = 0; i < _rows; ++i){
            for (size_m j = 0; j < _cols; ++j){
                (*result)(i,j) = (*this)(i,j) + m(i,j);
            }
        }
        return *result;
    }

    Matrix& operator-(const Matrix& m) const {
        if (_rows != m._rows || _cols != m._cols){
            throw std::invalid_argument("Matrix dimensions must agree");
        }
        Matrix* result = new Matrix(_rows, _cols);
        for (size_m i = 0; i < _rows; ++i){
            for (size_m j = 0; j < _cols; ++j){
                (*result)(i,j) = (*this)(i,j) - m(i,j);
            }
        }
        return *result;
    }
    
    Matrix& operator*(const Matrix& m) const{
        Matrix* result = new Matrix(_rows, m._cols);
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < m._cols; j++){
                double sum = 0;
                for (size_m k = 0; k < _cols; k++){
                    sum += _data[i*_skip + k] * m._data[k*m._skip + j];
                }
                result->_data[i* result->_skip + j] = sum;
            }
        }
        return *result;
    }

    Matrix& operator*(double d) const {
        Matrix* result = new Matrix(_rows, _cols);
        for (size_m row = 0; row < _rows; row++){
            for (size_m col = 0; col < _cols; col++){
                (*result)(row,col) = (*this)(row,col) * d;
            }
        }
        return *result;
    }
    
    Matrix& operator/(double d) const {
        Matrix* result = new Matrix(_rows, _cols);
        for (size_m row = 0; row < _rows; row++){
            for (size_m col = 0; col < _cols; col++){
                (*result)(row,col) = (*this)(row,col) / d;
            }
        }
        return *result;
    }

    Matrix& operator+=(const Matrix& m){
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                _data[i*_skip + j] += m._data[i*_skip + j];
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& m){
       for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                _data[i*_skip + j] -= m._data[i*_skip + j];
            }
        }
        return *this;
    }

    Matrix& operator*=(const Matrix& m){
        Matrix result(_rows, m._cols);
        
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < m._cols; j++){
                double sum = 0;
                for (size_m k = 0; k < _cols; k++){
                    sum += _data[i*_skip + k] * m._data[k*m._skip + j];
                }
                result._data[i*result._skip + j] = sum;
            }
        }

        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < m._cols; j++){
                (*this)(i,j) = result(i, j);
            }
        }
        
        return *this;
    }

    double& operator()(size_m i, size_m j) const{
        if (i >= _rows || j >= _cols){
            throw std::out_of_range("Index out of range");
        }
        return _data[i*_skip + j];
    }

    int rows() const {
        return _rows;
    }

    int cols() const {
        return _cols;
    }
    
    int skip() const {
        return _skip;
    }

    double* data() const {
        return _data;
    }

    void print() const{
        for (size_m i = 0; i < _rows; i++){
            std::cout << "      | ";
            for (size_m j = 0; j < _cols; j++){
                std::cout << std::to_string(_data[i*_skip + j]) << " ";
            }
            std::cout <<"|" << std::endl;
        }
    }

    Matrix& slice(size_m row_start, size_m row_end, size_m col_start, size_m col_end) const{
        Matrix* result = new Matrix();

        result->_rows = row_end - row_start;
        result->_cols = col_end - col_start;
        result->_skip = _skip;
        result->_is_slice = true;
        result->_data = _data + (row_start * _skip) + col_start;
        
        return *result;
    }

    Matrix& copy() const{
        Matrix* result = new Matrix(_rows, _cols);
        for (size_m i = 0; i < _rows; i++){
            for (size_m j = 0; j < _cols; j++){
                (*result)(i,j) = (*this)(i,j);
            }
        }
        return *result;
    }

};