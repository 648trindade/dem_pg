# DEM PlayGround

## Creating conda environment

```
conda devenv
conda activate dem_pg
export LIBRARY_PATH=$CONDA_PREFIX/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=$CONDA_PREFIX/lib:$LD_LIBRARY_PATH
```

## Building playground

On a machine with cuda provisioned with fett:

```
mkdir build && cd build
cmake -DCMAKE_CXX_COMPILER=clang -DCMAKE_CUDA_COMPILER=$HOME/Shared/cuda/v11.1/bin/nvcc -DCUDA_TOOLKIT_ROOT_DIR=$HOME/Shared/cuda/v11.1 ..
make -j
make install
```