#include "dgemm.h"

#include <omp.h>

#include <stdexcept>
#include <string>

void omp_dgemm(const std::vector<double> &A, const std::vector<double> &B,
               std::vector<double> &C, int rows, int middle, int columns) {
#pragma omp parallel for schedule(static)
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      for (int k = 0; k < middle; k++) {
        C[i * columns + j] += A[i * middle + k] * B[k * columns + j];
      }
    }
  }
}