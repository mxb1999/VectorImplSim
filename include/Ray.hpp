#include "simConst.hpp"
#define path(i, j) [i*numstored+j]
#ifndef RAY
  struct crossing
  {
    int x;
    int z;
    float mag;//magnitude of ray displacement vector in sector
    int flags;//determine which side of zone the ray entered in/exited
  };
  crossing* newCrossing(int x, int z);

  int getX(crossing* cross);

  int getZ(crossing* cross);

  double getMag(crossing* cross);
  double getIn(crossing* cross);
  double getOut(crossing* cross);

  int addMag(crossing* cross,double inc);

  class Ray
  {
  private:
    crossing* path;
    double* k;
    double* pos;
    double phase;
    double pow;
    float* mult;//multiplicative adjustment due
    int last;
  public:
    Ray(double* k, double* p, double phase, double pow);
    Ray();
    ~Ray();
    double getIntensity(int crossing);
    void setMultiplier(double newmult, int crossing);
    //accessor functions
    double* getKin();
    int getRayX(int loc);
    int getRayZ(int loc);
    int getInd();
    double* getPos();
    crossing* getLast();
    double getPhase();
    double getPow();
    int addPath(int x, int z, int high, int side);
    crossing* getPath();//pathLen, 2 -> store x and z coordinates for each grid square passed through
    void setIntensity();

    //Mapping tree::
  };
#endif
