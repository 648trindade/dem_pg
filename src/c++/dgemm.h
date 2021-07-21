#include <vector>

void omp_dgemm(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int rows, int middle, int columns);

void cuda_dgemm(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int rows, int middle, int columns);

void check(const std::vector<double>& C, int middle);