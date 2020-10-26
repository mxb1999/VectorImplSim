#include "icf.hpp"

/*Goal::
  Using the electron gradient, calculate the electric field at each location in the mesh
  Used to aid in ray tracking, determine force on photon at any given point

*/
//force due to electron gradient
//NOTE:: Implement FDTD method here later

//Fills in electron gradient for a given function
//Default:: Linear density gradient
double edenFunc(double x, double z)
{
  double temp = fmax(0.0,((0.3*ncrit-0.1*ncrit)/(xmax-xmin))*(x-xmin)+(0.1*ncrit));
  return temp;
}
double* eDensity()
{
  double* result = new double[nx*nz];
  for(int i = 0; i < nx;i++)
  {
    for(int j = 0; j < nz; j++)
    {
      result[i*nz+j] = edenFunc(dx*i+xmin, dz*j+zmin);
    }
  }
  return result;
}
double** calculateForce()
{
  double* eden = eDensity();
  double** result = new double*[2];
  result[0] = new double[nx*nz];
  result[1] = new double[nx*nz];
  for (size_t i = 0; i < nx-1; i++) {
    for (size_t j = 0; j < nz-1; j++) {
      result[0][i*nz + j] = pow(c,2.0)/(2.0*ncrit)*(eden[(i+1)*nz+j]-eden[i*nz+j])/(dx);
      result[1][i*nz + j] = pow(c,2.0)/(2.0*ncrit)*(eden[i*nz+j+1]-eden[i*nz+j])/(dz);
    }
  }
  for(int i = 0; i < fmax(nx,nz);i++)
  {
    if(i < nx)
    {
      result[0][i*nz + nz - 1] = result[0][i*nz + nz - 2];

    }
    if(i < nz)
    {
      result[1][(nx-1)*nz + i] = result[1][(nx-2)*nz + i];
    }
  }
  /*
  for(int i = 0; i < nx; i++)
  {
    for(int j = 0; j < nz; j++)
    {
      result[0][i*nz + j] = (i < nx-1) * pow(c,2.0)/(2.0*ncrit)*(eden[(i+1)*nz + j] - eden[i*nz + j])/dx + (i == nx - 1)*result[0][(i-1)*nz + j];
      result[1][i*nz + j] = (j < nz-1) * pow(c,2.0)/(2.0*ncrit)*(eden[i*nz + j + 1] - eden[i*nz + j])/dz + (j == nz - 1)*result[1][i*nz + j - 1];
      printf("%e\n", result[i*nz]);
    }
  }*/
  return result;
}
