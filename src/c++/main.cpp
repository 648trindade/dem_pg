#include "dgemm.h"

#include <cstdlib>
#include <iostream>


void print(const std::vector<double>& matrix, int rows, int columns);

int main(int argc, char* argv[])
{
    // parse command line arguments
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <rows> <middle> <columns" << std::endl;
        return 1;
    }

    const int rows = atoi(argv[1]);
    const int middle = atoi(argv[2]);
    const int columns = atoi(argv[3]);

    // instantiate matrices
    std::vector<double> matrix_A(rows * middle, 1.0);
    std::vector<double> matrix_B(middle * columns, 2.0);
    std::vector<double> matrix_C(rows * columns, 0.0);

    // call OpenMP double-precision general matrix-matrix multiplication
    omp_dgemm(matrix_A, matrix_B, matrix_C, rows, middle, columns);
    print(matrix_C, rows, columns);

    // reset result matrix
    matrix_C.assign(rows * columns, 0.0);

    // call CUDA double-precision general matrix-matrix multiplication
    cuda_dgemm(matrix_A, matrix_B, matrix_C, rows, middle, columns);
    print(matrix_C, rows, columns);

    return 0;
}

void print(const std::vector<double>& matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << matrix[i * columns + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}