#include <iostream>
#include "mlc.hpp"

#ifndef number
#define number 0
#endif

#define PRINT_M(m) print(m, #m)
#define PRINT_I(i) std::cout << #i << " = " << i << std::endl
#define number 0

void print(const Matrix& m, std::string name){
    std::cout << name << " := "<< std::endl;
    m.print();
    std::cout << std::endl;
}

int main(){

    Matrix m1(10, 10);

    for (double i = 0; i < m1.rows(); i++){
        for (double j = 0; j < m1.cols(); j++){
            m1(i, j) += i + j/10;
        }
    }   

    PRINT_M(m1);
    PRINT_M(m1.slice(1, 4, 2, 5));


}