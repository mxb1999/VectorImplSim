#include "Ray.hpp"
//Ray Constructor, sets up initial values for ray and initializes data structures



crossing* newCrossing(int x, int z)
{
  crossing *result = new crossing;
  if(!result){
    return NULL;
  }
  result->x = x;
  result->z = z;
  result->mag = 0.0;
  return result;
}
int getX(crossing* cross)
{
  if(!cross)
  {
    return 0;
  }
  return cross->x;
}
int getZ(crossing* cross)
{
  if(!cross)
  {
    return 0;
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
void addMag(crossing* cross,double inc)
{
  if(cross == NULL)
  {
    return;
  }
  cross->mag+=inc;
}
Ray::~Ray()
{
  if(path)
    delete []path;
};
Ray::Ray()
{
  this->inten = 0;
  this->k = NULL;
  this->path = NULL;
  this->pos = NULL;
  this->phase = 0;
  this->pow = 0;
  this->currInd = 0;
}
Ray::Ray(double* k, double* p, double phase, double pow)
{
  this->inten = intensity;
  this->k = k;

  this->path = new crossing[numstored];
  this->pos = p;

  this->phase = phase;
  this->pow = pow;
  this->currInd = 0;
}

void Ray::setIntensity(double newInten)
{
  inten = newInten;
}
double Ray::getIntensity()
{
  return inten;
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
crossing* Ray::getLast()
{
  return &path[currInd];
}
void Ray::addPath(int x, int z)
{
  if(this->currInd >= numstored-1)
  {
    printf("No further storage available in Ray path\n");
    return;
  }
  this->currInd++;
  this->path[this->currInd] = *newCrossing(x,z);

}
