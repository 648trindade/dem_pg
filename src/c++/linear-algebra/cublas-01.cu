#define _USE_MATH_DEFINES
#define FMT_HEADER_ONLY

#include "fmt/format.h"
#include "fmt/ranges.h"

#include "cuda_runtime.h"
#include "cublas_v2.h"

#include <array>
#include <cmath>
#include <cstdlib>

constexpr int blas_index(int row, int column, int number_rows) {
    return column * number_rows + row;
}

static __inline__ void modify (
    cublasHandle_t handle,
    float *matrix,
    int number_rows,
    int number_columns,
    int row,
    int column,
    float alpha,
    float beta
) {
    /*!
        `cublasSscal` Function to scale a vector by a given scalar (in-place).
    
        @param[in] handle:
            Handle of the cuBLAS instance.
        @param[in] n:
            Size of the vector.
        @param[in] alpha:
            Pointer to the constant to scale the vector with.
        @param[in,out] x:
            Pointer to the first element of the vector.
        @param[in] incx:
            Stride between consecutive elements of the vector.
        @return:
            Status of the operation (handler).
    */
    // Scale the elements in the given row after the given column by alpha.
    int size_alpha { number_columns - column };
    cublasSscal(
        handle,
        size_alpha,
        &alpha,
        &matrix[blas_index(row, column, number_rows)],
        number_rows
    );
    // Scale the elements in the given column after the given row by beta.
    int size_beta { number_rows - row };
    cublasSscal(
        handle,
        size_beta,
        &beta,
        &matrix[blas_index(row, column, number_rows)],
        1
    );
}

int main (void){
    constexpr int number_rows { 6 };
    constexpr int number_columns { 5 };
    cudaError_t cuda_status;
    cublasStatus_t blas_status;
    cublasHandle_t handle;
    std::array<float, number_rows * number_columns> matrix;
    float * device_matrix;

    fmt::print("\n...input:\n");
    for (int row { 0 }; row < number_rows; ++row) {
        for (int column { 0 }; column < number_columns; ++column) {
            matrix[blas_index(row, column, number_rows)] =
                static_cast<float>(row * number_columns + column + 1);
            fmt::print("{:10.2f}", matrix[blas_index(row, column, number_rows)]);
        }
        fmt::print("\n");
    }

    cuda_status = cudaMalloc(&device_matrix, number_rows * number_columns * sizeof(float));
    if (cuda_status != cudaSuccess) {
        fmt::print("...device memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    blas_status = cublasCreate(&handle);
    if (blas_status != CUBLAS_STATUS_SUCCESS) {
        fmt::print("...cuBLAS initialization failed!\n");
        return EXIT_FAILURE;
    }
    blas_status = cublasSetMatrix(
        number_rows,
        number_columns,
        sizeof(float),
        matrix.data(),
        number_rows,
        device_matrix,
        number_rows
    );
    if (blas_status != CUBLAS_STATUS_SUCCESS) {
        fmt::print("...data download failed!\n");
        cudaFree(device_matrix);
        cublasDestroy(handle);
        return EXIT_FAILURE;
    }

    modify(handle, device_matrix, number_rows, number_columns, 1, 2, 16.0f, 12.0f);

    blas_status = cublasGetMatrix(
        number_rows,
        number_columns,
        sizeof(float),
        device_matrix,
        number_rows,
        matrix.data(),
        number_rows
    );
    if (blas_status != CUBLAS_STATUS_SUCCESS) {
        fmt::print("...data upload failed!\n");
        cudaFree(device_matrix);
        cublasDestroy(handle);
        return EXIT_FAILURE;
    }

    cudaFree(device_matrix);
    cublasDestroy(handle);

    fmt::print("\n...output:\n");
    for (int row { 0 }; row < number_rows; ++row) {
        for (int column { 0 }; column < number_columns; ++column) {
            fmt::print("{:10.2f}", matrix[blas_index(row, column, number_rows)]);
        }
        fmt::print("\n");
    }
    
    return EXIT_SUCCESS;
}