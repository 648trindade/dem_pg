# DEM PlayGround

## Creating conda environment

From an CentOS 7 ESSS development environment with conda-devenv
```bash
conda devenv
conda activate dem_pg
export LIBRARY_PATH=$CONDA_PREFIX/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=$CONDA_PREFIX/lib:$LD_LIBRARY_PATH
```

From a debian-based environment with conda installed
```bash
# if you don't have conda-forge channel
conda config --add channels conda-forge
conda config --set channel_priority strict

conda create -y -n dem_pg
conda install -y clangxx==10 libcxx==10 llvm-openmp==10 clang-tools==10 "cmake>=3.8"
export LIBRARY_PATH=$CONDA_PREFIX/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=$CONDA_PREFIX/lib:$LD_LIBRARY_PATH
```

## Building playground

From an CentOS 7 ESSS development environment with CUDA provisioned by fett:
```bash
mkdir build && cd build
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CUDA_COMPILER=$CUDA_PATH_V11_1/bin/nvcc -DCUDA_TOOLKIT_ROOT_DIR=$CUDA_PATH_V11_1 ..
make -j
```

From a debian-based environment with CUDA installed at `/usr`
```bash
mkdir build && cd build
cmake -DCMAKE_CXX_COMPILER=clang++ ..
make -j
```

## Running playground

From build directory:
```bash
./dem_pg 3 3 3
```