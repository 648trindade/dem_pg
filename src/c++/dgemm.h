#include <vector>

void omp_dgemm(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int rows, int columns, int middle);

void cuda_dgemm(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int rows, int columns, int middle);