#pragma once

#include <iostream>
#include <memory>

typedef unsigned long size_m;

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
        _data = std::shared_ptr<T>(new T[rows*cols]);
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
        
        _data = nullptr;
        
        #ifdef DEBUG
        std::cout << "Matrix destructor called on " ;
        #endif

    }

    const size_m rows() const {
        return _rows;
    }

    const size_m cols() const {
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


    
    Matrix<T>& slice(size_m start_row, size_m start_col, size_m end_row, size_m end_col){
        Matrix<T>* m = new Matrix<T>();
        m->_rows = end_row - start_row;
        m->_cols = end_col - start_col;
        m->_start_row = this->_start_row + start_row;
        m->_start_col = this->_start_col + start_col;
        m->_skip = this->_skip;
        m->_is_slice = true;
        m->_data = this->_data;
        return *m;
    }

    void Identity(){
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



};