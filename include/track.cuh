#include <cuda_runtime.h>
#include <cufft.h>          // CUDA FFT Libraries
#include <helper_cuda.h>    // Helper functions for CUDA Error handling

__global__ void trackRay();
__device__ void
