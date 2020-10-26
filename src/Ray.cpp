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
  if(cross == NULL)
  {
    std::cout << "NULL Attempt" << std::endl;
    return -1;
  }
  return cross->x;
}
int Ray::getRayX(int loc)
{
  if(loc < currInd)
  {
    return getX(&path[loc]);
  }
  //std::cout << "LOC:: " << loc << "  ::  currInd: " << currInd << std::endl;

  return -1;
}
int Ray::getRayZ(int loc)
{
  if(loc < currInd)
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
int Ray::getInd()
{
  return currInd;
}
crossing* Ray::getLast()
{
  return &this->path[this->currInd];
}
int Ray::addPath(int x, int z)
{
  if(this->currInd >= numstored-1)
  {
    printf("No further storage available in Ray path\n");
    return -1;
  }
  this->path[this->currInd] = *newCrossing(x,z);
  this->currInd++;
  return 0;
}
