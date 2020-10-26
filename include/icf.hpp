#ifndef ICF
#define ICF
  #include "Ray.hpp"
  #include <cstdlib>
  #include "H5Cpp.h"
  #include <Python.h>
  #include <chrono>
  //#include <mpi/mpi.h>
  #include <omp.h>
  #include <cuda_runtime.h>
  /*Overarching software structure:
  Most efficient implementation of ray location storage?
  Needs::
    - Must be able to update ray intensities throughout the CBET calcu+lation
    - Must be able to retrieve the rays at a given location
    - Best data storage method for rays?
    - Must be able to determine what rays intersect each other
    - Data Stuctures:
        - Each ray will possess a list of its path through the grid
        - Can calculate trajectory via myx/myz to find current grid square w/ boundary info
        - After ray tracing -> how to get crossing information efficiently?
        - Store ray path as array, not linkedlist
        - Can implement naive approach first then improve
        - Don't store unique ray ids for spatial tracking, just store the intensity of the ray at that grid position, update after each update stage and after ray tracking
        - Also need to store number of rays in each grid square for each beam
  */
  //Ray Tracing Functions
  /*
    Essential functionality:
      - Divide initial beam workload amongst nodes in system
      - Initialize each ray and pass to GPU for tracking
        - Store path of each ray in local object
        - Iterate over time for each ray, find trajectory
        - Pass rays back to host -> initialize intensity sampling array
        - Pass sampling arrays and rays from compute nodes up to host node
  */
  extern int** count;
  void init_Track();
  void sampleIntensity();
  double** calculateForce();
  double* eDensity();
  void updateH5(void* arr1, char* arrName1, void* arr2, char* arrName2);
#endif
