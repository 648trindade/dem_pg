#include "dgemm.h"

#include <omp.h>

#include <iostream>
#include <string>
#include <stdexcept>

__global__ void do_dgemm(double* A, double* B, double* C, int rows, int middle, int columns)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    if (i < rows && j < columns)
        for (int k = 0; k < middle; k++)
            C[i * columns + j] += A[i * middle + k] * B[k * columns + j];
}

void cuda_dgemm(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int rows, int middle, int columns)
{
    double *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, sizeof(double) * rows * middle);
    cudaMalloc(&d_B, sizeof(double) * middle * columns);
    cudaMalloc(&d_C, sizeof(double) * rows * columns);

    cudaMemcpy(d_A, A.data(), sizeof(double) * rows * middle, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B.data(), sizeof(double) * middle * columns, cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, C.data(), sizeof(double) * rows * columns, cudaMemcpyHostToDevice);

    dim3 block(32, 32);
    dim3 grid(std::ceil(rows / 32.0), std::ceil(columns / 32.0));

    do_dgemm<<<grid, block>>>(d_A, d_B, d_C, rows, middle, columns);

    cudaMemcpy(C.data(), d_C, sizeof(double) * rows * columns, cudaMemcpyDeviceToHost);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}

void check(const std::vector<double>& C, int middle)
{
    for (double value : C)
        if (value != middle * 2)
            throw std::runtime_error("Incorrect result: " + std::to_string(value));
}