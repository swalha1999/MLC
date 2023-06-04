#include "mlc.h"

int main(int argc, char *argv[])
{
    // Create a new Matrix
    Matrix* A = matrix_alloc(3, 3);
    matrix_fill(A, 69.0);

    PRINT_MATRIX(A);
    return 0;
}
