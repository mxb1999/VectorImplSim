#include <cuda/cuda_runtime.h>
#include "icf.hpp"


class cudaHandler
{
    private:
        int T = 1024;//number of threads per block called by default  
        __global__ void placeRaysOnGrid(double* grid, Ray* rays, int num);//function to place incoming rays on grid, utilize CUDA parallelism
    public:
        double* get_RayGrid(Ray* rays, int num);//wrapper function for calling placeRaysOnGrid 
};