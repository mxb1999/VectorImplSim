#include "Ray.hpp"
//Ray Constructor, sets up initial values for ray and initializes data structures



crossing* newCrossing(int x, int z, short xside , short zside)//xside = 0 for left, 1 for right, zside = 0 for bottom, zside = 1 for top
{
  crossing *result = new crossing;
  if(!result){
    return NULL;
  }
  result->x = x;
  result->z = z;
  result->mag = 0.0;
  result->flags = xside + 2*zside;//encodes entry/exit info, along with mag, uniquely defines path. Exit encoded in the next two higher bits
  return result;
};
void addExit(crossing* cross, short xside, short zside)//same encoding method
{
  if(cross == NULL)
  {
    return;
  }
  cross->flags = 4*xside + 8*zside;
}
int getX(crossing* cross)
{
  if(cross == NULL)
  {
    std::cout << "NULL Attempt" << std::endl;
    return -1;
  }
  return cross->x;
}
int Ray::getRayX(int loc)
{
  if(loc < last)
  {
    return getX(&path[loc]);
  }
  //std::cout << "LOC:: " << loc << "  ::  last: " << last << std::endl;

  return -1;
}
int Ray::getRayZ(int loc)
{
  if(loc < last)
  {
    return getZ(&path[loc]);
  }
  return -1;
}
int getZ(crossing* cross)
{
  if(!cross)
  {
    return -1;
  }
  return cross->z;
}
double getMag(crossing* cross)
{
  if(!cross)
  {
    return 0;
  }
  return cross->mag;
}
int addMag(crossing* cross,double inc)
{
  if(cross == NULL)
  {
    return -1;
  }
  cross->mag+=inc;
  return 0;
}
Ray::~Ray()
{
};
Ray::Ray()
{
  this->mult = new float[nrays]{1};
  this->k = NULL;
  this->path = NULL;
  this->pos = NULL;
  this->phase = 0;
  this->pow = 0;
  this->last = 0;
}
Ray::Ray(double* k, double* p, double phase, double pow)
{
  this->mult = new float[nrays]{1};
  this->k = k;

  this->path = new crossing[numstored];
  this->pos = p;

  this->phase = phase;
  this->pow = pow;
  this->last = 0;
}

void Ray::setMultiplier(double newmult, int crossing)
{
  mult[crossing] = newmult;
}
double Ray::getIntensity(int crossing)
{
  return intensity*mult[crossing];
};
crossing* Ray::getPath()
{
  return path;
};
double* Ray::getKin()
{
  return k;
};
double* Ray::getPos()
{
  return pos;
};
double Ray::getPhase()
{
  return phase;
};
double Ray::getPow()
{
  return pow;
};
int Ray::getInd()
{
  return last;
}
crossing* Ray::getLast()
{
  return &this->path[this->last];
}
int Ray::addPath(int x, int z, int high, int side)
{
  if(this->last >= numstored-1)
  {
    printf("No further storage available in Ray path\n");
    return -1;
  }
  this->path[this->last] = *newCrossing(x,z, side, high);
  this->last++;
  return 0;
}
