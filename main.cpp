#define DEBUG 1

#include <iostream>
#include "mlc.hpp"


#define PRINT_M(m) std::cout << #m << " := "<< std::endl; (m).print();std::cout << std::endl;
#define PRINT_I(i) std::cout << #i << " = " << i << std::endl
#define DELETE(m) delete m; std::cout << #m << " and it was deleted" << std::endl
#define number 0


int main(){

    Matrix<double>* m1 = new Matrix<double>(10, 10);

    for (double i = 0; i < m1->rows(); i++){
        for (double j = 0; j < m1->cols(); j++){
            (*m1)(i, j) += i + j/10;
        }
    }   

    PRINT_M(*m1);
    m1->Identity();

    

    PRINT_M(*m1);
    auto m2 = m1->slice(0, 0, 3, 3);

    // DELETE(m1);
    

    PRINT_M(m2);

    std::shared_ptr<double> data = m2.data();
    
    PRINT_M(m2.slice(1, 1, 2, 2));

    
    
    // try{
    //     std::cout << "d = " << d[0] << std::endl;
    // }
    // catch(std::exception& e){
    //     std::cout << e.what() << std::endl;
    // }
    

}