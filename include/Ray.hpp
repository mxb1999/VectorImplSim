#include "simConst.hpp"
#define path(i, j) [i*numstored+j]
#ifndef RAY
  struct crossing
  {
    double mag;
    int x;
    int z;
  };
  crossing* newCrossing(int x, int z);

  int getX(crossing* cross);

  int getZ(crossing* cross);

  double getMag(crossing* cross);

  void addMag(crossing* cross,double inc);

  class Ray
  {
  private:
    double inten;
    crossing* path;
    double* k;
    double* pos;
    double phase;
    double pow;
    int currInd;
  public:
    Ray(double* k, double* p, double phase, double pow);
    Ray();
    ~Ray();
    double getIntensity();
    void setIntensity(double newInten);
    //accessor functions
    double* getKin();
    double* getPos();
    crossing* getLast();
    double getPhase();
    double getPow();
    void addPath(int x, int z);
    crossing* getPath();//pathLen, 2 -> store x and z coordinates for each grid square passed through
    void setIntensity();

    //Mapping tree::
  };
#endif
