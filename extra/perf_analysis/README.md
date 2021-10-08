# Introduction 

Performance Analysis is an essential step to help improving applications performance. Especially on complex applications and platforms.

Code optimization is a **cyclic** process:


```
First Implementation -> measure -> analyze -> optimize -> Faster Code
                          ^                    |
                          |____________________|
```

There is a wide variety of different tools and techniques to perform these steps. But they all depend start with the **measure** step, for which we can use different **instrumentation** techniques.   
    
    Instrumentation is the act of modifying a program, either actively or automatically, for an alternative purpose, in our case, collect performance data.

Let's go through some techniques.

Technique | Description  | Detail Level | Overhead | Highlight | 
-|-|-|-|-|
Profiling    | Collects sampled data through the code execution, following a fixed time interval between measurements. |  🔴 Low    |  🟢 Low    | Hotspot analysis |
Interception | Event-based instrumentation technique. Wrap function calls to collect data for specific functions. Collect timing data, hardware counters, and context-specific data like function parameters.  |       Medium 🟡    | Medium 🟡 | Versatility |
Tracing      |  Uses Interception to track entry and exit times of application events. Enables a reconstruction of application behavior through time and among computational resources. |  🟢 High           | 🔴 High   | Spatial and Temporal Analysis |

# Tools list 
List of tools we can take a look:

CPU:
- [x] Intel VTune/oneAPI Base Toolkit (Intel CPUs only)
- [ ] Scalasca + CUBE + SCORE-P + PAPI (Only Linux)
- [ ] HPCToolkit (hpcviewer and hpctraceviewer) - Windows and Linux

GPU: 
- [x] NVIDIA Visual Profiler (nvvp + nvprof)
- [ ] Nsight systems + Nsight Compute (Only newer GPUs)

        Supported NVIDIA GPU architectures (https://developer.nvidia.com/nsight-compute):
        - Ampere: A100 with Multi-Instance GPU, GA10x
        - Turing: TU1xx
        - Volta: GV100[1], GV10B[2]

One good summary of the many performance analysis tools that are available out there can be found found in this page: http://pramodkumbhar.com/2017/04/summary-of-profiling-tools

# Intel VTune/oneAPI Base Toolkit (Linux)

## Download and install:
```bash
wget https://registrationcenter-download.intel.com/akdlm/irc_nas/17977/l_BaseKit_p_2021.3.0.3219_offline.sh
sudo bash l_BaseKit_p_2021.3.0.3219_offline.sh
```
Typically, the installation will be located in '/opt/intel' when installed with sudo.

## Using VTune
Recommends compiling with `-g`
```bash
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CUDA_COMPILER=$CUDA_PATH_V11_1/bin/nvcc DCUDA_TOOLKIT_ROOT_DIR=$CUDA_PATH_V11_1 CMAKE_BUILD_TYPE=Debug CMAKE_CXX_FLAGS="-g" ..
```

Start Intel vtune:
```bash
/opt/intel/oneapi/vtune/latest/bin64/vtune-gui
```

We need to set the environment to run our application. Intel VTune allows us to configure a wrapper script, to prepare the env before running, for example.
```bash
#!/bin/bash

# Prefix script
echo "Target process PID: $VTUNE_TARGET_PID"

conda activate dem_pg
export LIBRARY_PATH=$CONDA_PREFIX/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=$CONDA_PREFIX/lib:$LD_LIBRARY_PATH

# Run VTune collector
"$@"

# Postfix script
echo "Done, results are in: $VTUNE_RESULT_DIR"
```

# nvprof + Nvidia Visual Profiler

These tools already come installed with the cuda toolkit.

To enable track performance metrics in the code, compile with `--generate-line-info (-lineinfo)`
```bash
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CUDA_COMPILER=$CUDA_PATH_V11_1/bin/nvcc -DCUDA_TOOLKIT_ROOT_DIR=$CUDA_PATH_V11_1 CMAKE_BUILD_TYPE=Debug CMAKE_CXX_FLAGS="-g" CUDA_NVCC_FLAGS='-gencode=arch=compute_35,code="sm_35,compute_35" -lineinfo' ..
```

## Generate a simple profile
Default mode only produces a summary
```bash
$HOME/Shared/cuda/v11.1/bin/nvprof ./dem_pg 1024 1024 1024
```
## Generate a GPU trace profile
```bash
$HOME/Shared/cuda/v11.1/bin/nvprof --print-gpu-trace ./dem_pg 1024 1024 1024
```

## Export nvprof results

### Export to Nvidia Visual Profiler:
```bash
sudo -E LD_LIBRARY_PATH=$LD_LIBRARY_PATH $HOME/Shared/cuda/v11.1/bin/nvprof \
 --print-gpu-trace --print-api-trace --metrics "achieved_occupancy,l1_cache_local_hit_rate" 
 -o results_%p.nvvp \
./dem_pg 1024 1024 1024
```

### Export to CSV:
```bash
sudo -E LD_LIBRARY_PATH=$LD_LIBRARY_PATH $HOME/Shared/cuda/v11.1/bin/nvprof --csv \
 --metrics "achieved_occupancy,l1_cache_local_hit_rate,l2_utilization" \
 ./dem_pg 1024 1024 1024
```

## Run our application with NVVP

Open Nvidia Visual Profiler and configure a project to run the **guided analysis**.
```bash
export PATH=$PATH:$HOME/Shared/cuda/v11.1/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/Shared/cuda/v11.1/lib64
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/Shared/cuda/v11.1/extras/CUPTI/lib64
export PATH=$PATH:$HOME/Shared/cuda/v11.1/libnvvp

# run with sudo is needed for collecting performance metrics
sudo nvvp -vm /usr/lib/jvm/java-8-openjdk-amd64/jre/bin/java
```

Unlike Intel VTune, we do not have the option for using a wrapper or prefix script, so I believe we neet to set LD_LIBRARY_PATH variable and what else env variables are needed manually.

## Using NVTX

NVidia Tools Extension SDK: C-based Application Programming Interface (API) for annotating events, code ranges, and resources in your applications. NVTX can use NVIDIA Nsight and Visual Profiler to capture and visualize these events and ranges.

Add to CMakeLists.txt:
```bash
find_library(LIBNVTOOLSEXT nvToolsExt PATHS ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
target_link_libraries(
        dem_pg_cuda
            -L$HOME/Shared/cuda/v11.1/lib64 nvToolsExt
)
```

Add to env:
```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/Shared/cuda/v11.1/lib64
```

Code sample to use NVTX:
```cpp
// Used only to trace CPU execution
#ifdef USE_NVTX
#include "nvToolsExt.h"

const uint32_t colors[] = { 0xff00ff00, 0xff0000ff, 0xffffff00, 0xffff00ff, 0xff00ffff, 0xffff0000, 0xffffffff };
const int num_colors = sizeof(colors)/sizeof(uint32_t);

#define PUSH_RANGE(name,cid) { \
    int color_id = cid; \
    color_id = color_id%num_colors;\
    nvtxEventAttributes_t eventAttrib = {0}; \
    eventAttrib.version = NVTX_VERSION; \
    eventAttrib.size = NVTX_EVENT_ATTRIB_STRUCT_SIZE; \
    eventAttrib.colorType = NVTX_COLOR_ARGB; \
    eventAttrib.color = colors[color_id];    \
    eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; \
    eventAttrib.message.ascii = name; \
    nvtxRangePushEx(&eventAttrib); \
}
#define POP_RANGE nvtxRangePop();
#else
#define PUSH_RANGE(name,cid)
#define POP_RANGE
#endif
```

## Reading/Support Materials

### Fundamental Optimizations - CUDA architecture overview, memory hierarchy, access patterns: 
 - http://developer.download.nvidia.com/GTC/PDF/1083_Wang.pdf
 - Part 2: https://www.olcf.ornl.gov/wp-content/uploads/2020/04/04-CUDA-Fundamental-Optimization-Part-2.pdf
 - In-depth optimization: https://on-demand.gputechconf.com/gtc/2013/presentations/S3466-Programming-Guidelines-GPU-Architecture.pdf

### Local Memory and Register Spilling:
https://on-demand.gputechconf.com/gtc-express/2011/presentations/register_spilling.pdf
- Local mem access usually when one runs out of SM resources
  - Local mem bytes are stored in global mem
  - Stores are cached in L1, lmem cache lines can be evicted and end up in global mem
- Hurt performance causing increased *memory traffic* or increased *instruction count*

### CUDA Optimization Tips and Tricks
https://on-demand.gputechconf.com/gtc/2017/presentation/s7122-stephen-jones-cuda-optimization-tips-tricks-and-techniques.pdf

### Analysis Driven Optimization
https://developer.download.nvidia.com/GTC/PDF/1082_Wang.pdf

### List of tools and usage:
https://www.vi-hps.org/cms/upload/material/general/ToolsGuide.pdf