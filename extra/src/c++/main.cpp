#include "dgemm.h"

#include <omp.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char *argv[]) {
  // parse command line arguments
  if (argc < 4) {
    std::cerr << "Usage: " << argv[0] << " <rows> <middle> <columns"
              << std::endl;
    return 1;
  }

  const int rows = atoi(argv[1]);
  const int middle = atoi(argv[2]);
  const int columns = atoi(argv[3]);

  // instantiate matrices
  std::vector<double> matrix_A(rows * middle, 1.0);
  std::vector<double> matrix_B(middle * columns, 2.0);
  std::vector<double> matrix_C(rows * columns, 0.0);

  // variables to control computation time
  double begin, end;

  /* ------------------------------- OpenMP
   * -----------------------------------------*/

  begin = omp_get_wtime();

  // call OpenMP double-precision general matrix-matrix multiplication
  omp_dgemm(matrix_A, matrix_B, matrix_C, rows, middle, columns);

  end = omp_get_wtime();
  check(matrix_C, middle);
  std::cout << " OMP: " << (end - begin) << " s" << std::endl;

  /* ------------------------------- CUDA
   * -----------------------------------------*/

  // reset result matrix
  matrix_C.assign(rows * columns, 0.0);

  begin = omp_get_wtime();

  // call CUDA double-precision general matrix-matrix multiplication
  cuda_dgemm(matrix_A, matrix_B, matrix_C, rows, middle, columns);

  end = omp_get_wtime();
  check(matrix_C, middle);
  std::cout << "CUDA: " << (end - begin) << " s" << std::endl;

  return 0;
}