#pragma once

#include <iostream>

typedef unsigned long size_m;

class Matrix {
private:
    size_m _rows;
    size_m _cols;
    size_m _skip;
    double* _data = nullptr;
    
public:

    Matrix(int rows, int cols){
        _rows = rows;
        _cols = cols;
        _skip = cols;
        _data = new double[rows*cols];
    }

    Matrix(const Matrix& m){
        _rows = m._rows;
        _cols = m._cols;
        _skip = m._skip;
        _data = new double[_rows*_cols];
        for (size_m i = 0; i < _rows*_cols; i++){
            _data[i] = m._data[i];
        }
    }

    ~Matrix(){
        delete[] _data;
    }

    Matrix& operator=(const Matrix& m){
        if (this != &m){
            
            if (_data != nullptr){
                delete[] _data;
            }
            
            _rows = m._rows;
            _cols = m._cols;
            _skip = m._skip;
            _data = m._data;
        }
        return *this;
    }
    
    Matrix operator+(const Matrix& m) const {
        Matrix result(_rows, _cols);
        for (size_m i = 0; i < _rows*_cols; i++){
            result._data[i] = _data[i] + m._data[i];
        }
        return result;
    }

    Matrix operator-(const Matrix& m) const {
        Matrix result(_rows, _cols);
        for (size_m i = 0; i < _rows*_cols; ++i){
            result._data[i] = _data[i] - m._data[i];
        }
        return result;
    }
    
    Matrix operator*(const Matrix& m) const{
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
        return result;
    }
    
    Matrix operator*(double d) const {
        Matrix result(_rows, _cols);
        for (size_m i = 0; i < _rows*_cols; i++){
            result._data[i] = _data[i] * d;
        }
        return result;
    }
    
    Matrix operator/(double d) const {
        Matrix result(_rows, _cols);
        for (size_m i = 0; i < _rows*_cols; i++){
            result._data[i] = _data[i] / d;
        }
        return result;
    }

    Matrix& operator+=(const Matrix& m){
        for (size_m i = 0; i < _rows*_cols; i++){
            _data[i] += m._data[i];
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& m){
        for (size_m i = 0; i < _rows*_cols; i++){
            _data[i] -= m._data[i];
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

    void print() const{
        for (size_m i = 0; i < _rows; i++){
            std::cout << "      | ";
            for (size_m j = 0; j < _cols; j++){
                std::cout << std::to_string(_data[i*_skip + j]) << " ";
            }
            std::cout <<"|" << std::endl;
        }
    }

    Matrix slice(int row_start, int row_end, int col_start, int col_end) const{
        Matrix result(row_end - row_start, col_end - col_start);
        for (int i = row_start; i < row_end; i++){
            for (int j = col_start; j < col_end; j++){
                result(i - row_start, j - col_start) = (*this)(i, j);
            }
        }
        return result;
    }
};