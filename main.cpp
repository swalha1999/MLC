
#include <iostream>
#include "mlc.h"


#define PRINT_M(m) std::cout << #m << " := " << std::endl; (m).print();std::cout << std::endl;
#define PRINT_I(i) std::cout << #i << " = " << i << std::endl
#define DELETE(m) delete m; std::cout << #m << " and it was deleted" << std::endl
#define number 0


int main(){

    Matrix<long int> m1 = Matrix<long int>(10, 10);
    m1.Identity();
    PRINT_M(m1);
    Matrix<long int> m2 = m1;
    m1 *= 2;
    PRINT_M(m1);
    m2*=m1;
    PRINT_M(m1); 
    PRINT_M(m2);   

}