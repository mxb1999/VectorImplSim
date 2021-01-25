#ifndef TRACE
#define TRACE
  #include "implSim.hpp"
  #include "customMath.hpp"
  extern void launchRays();
  extern void track(int raynum, int xinit, int zinit, int kxinit, int kzinit, double urayinit, int beam);
  extern omp_lock_t writelock;
  //
  struct rayinit//composite struct, compactly store necessary initial information
  {
      double xinit;
      double zinit;
      double kxinit;
      double kzinit;
      int beam;
      double urayinit;
      double wpeinit;
  };
#endif