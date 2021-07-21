#include "dgemm.h"

void omp_dgemm(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int rows, int middle, int columns)
{
}

void cuda_dgemm(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int rows, int middle, int columns)
{
}

void check(const std::vector<double>& C, int middle)
{
    // for (double value : C)
    //     if (value != middle * 2)
    //         throw std::runtime_error("Incorrect result: " + std::to_string(value));
}