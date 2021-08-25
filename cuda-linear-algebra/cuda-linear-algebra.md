# CUDA Linear Algebra Tools

[cuda-linear-algebra](https://developer.nvidia.com/gpu-accelerated-libraries)

## `cuBLAS`

> The `cuBLAS` library is an implementation of `BLAS` (Basic Linear Algebra Subprograms)
on top of the NVIDIA®`CUDA`™ runtime. It allows the user to access the computational
resources of NVIDIA Graphics Processing Unit (GPU).

### important notes❗

- `cuBLAS` uses column-major matrix storage for "maximum compatibility with existing
Fortran environments"
  - NVIDIA suggests the usage of the macro `#define IDX2C(i,j,ld) (((j)*(ld))+(i))` but
    always remember
    [**ES.31: Don’t use macros for constants or “functions”**](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es31-dont-use-macros-for-constants-or-functions)
  - use a `constexpr` (constexpr are implicitly `inline`d so they nicely replace the
    macro, also `constexpr` is valid in `CUDA`) function like:
    <br>`constexpr std::size_t blas_index( std::size_t line, std::size_t row, std::size_t number_lines)`
    <br>`{ return row * number_lines + line; }`
- tensor cores
  - > Starting with `cuBLAS` version 11.0.0, the library will automatically make use of
    Tensor Core capabilities wherever possible, unless they are explicitly disabled by selecting pedantic compute modes in `cuBLAS`
