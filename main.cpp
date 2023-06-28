
#include <iostream>
#include "mlc.h"


#define PRINT_M(m) std::cout << #m << " := " << std::endl; (m).print();std::cout << std::endl;
#define PRINT_I(i) std::cout << #i << " = " << i << std::endl
#define DELETE(m) delete m; std::cout << #m << " and it was deleted" << std::endl
#define number 0


int main(){

    // lets make tests for the matrix class

    // first lets make a matrix
    Matrix m1(3, 3);
    Matrix m2(3, 3);

    // lets fill it with some values
    for(int i = 0; i < m1.rows(); i++){
        for(int j = 0; j < m1.cols(); j++){
            m1(i, j) = i+j;
        }
    }

    // lets print it
    PRINT_M(m1);

    m2.Identity();
    PRINT_M(m2);


    // lets test the copy function
    Matrix m3 = m1.copy();
    PRINT_M(m3);

    // lets test the slice function
    Matrix m4 = m1.slice(1, 1, 3, 3);
    PRINT_M(m4);

    // lets test the * operator with scalar
    Matrix m5 = m1 * 2;
    PRINT_M(m5);

    // lets test the * operator with matrix
    Matrix m6 = m1 * m2;
    PRINT_M(m6);

    
}