#include

/*Goal::
  Using the electron gradient, calculate the electric field at each location in the mesh
  Used to aid in ray tracking, determine force on photon at any given point

*/
//calculates change in electron gradient, used in calculating the deflection
double* calculateDeflection(int x, int z, double* dist)
{
  double* result = new double[nx*nz*2];
  for(int i = 0; i < nx;i++)
  {
    for(int j = 0; j < nz; j++)
    {
      result[i*nz+j*2] =
      result[i*nz+j*]
    }
  }
}
//Fills in electron gradient for a given function
//Default:: Linear density gradient
double edenFunc(double x, double z)
{
  return ((0.3*ncrit-0.1*ncrit)/(xmax-xmin))*(x-xmin)+(0.1*ncrit);
}
double* eDensity()
{
  double* result = new double[nx*nz];
  for(int i = 0; i < nx;i++)
  {
    for(int j = 0; j < nz; j++)
    {
      result[i*nz+j] = edenFunc(dx*i, dz*j);
    }
  }
}
