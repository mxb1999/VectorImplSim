#include "icf.hpp"

void track(Ray ray, int* count)
{

  double rayV[] = {(*(ray.getKin()))*pow(c,2)/omega, (*(ray.getKin()+1))*pow(c,2)/omega};
  double x = *ray.getPos();
  double z = *(ray.getPos()+1);
  int currX = (int)(x*nx/(xmax-xmin));
  int currZ = (int)(z*nz/(zmax-zmin));
  int prevX = 0;
  int prevZ = 0;
  double deltaX;
  double deltaZ;
  int i = 0;
  while(abs(x) < xmax && abs(z) < zmax)
  {
    //If the ray enters a new cell
    if(prevX != currX || prevZ != currZ)
    {

      deltaX = x-dx*currX;
      deltaZ = z-dz*currZ;
      ray.addPath(currX, currZ);

      count[currX*nz+currZ]++;
    //If the ray spends multiple iterations in the same cell
    }else
    {
      addMag(ray.getLast(), sqrt(pow(deltaX, 2) + pow(deltaZ, 2)));
      deltaX = rayV[0]*dt;
      deltaZ = rayV[1]*dt;
    }
    //printf("%(x,z): (%e,%i)\n", dt, nt);
    //Update position variables for comparison in the next iteration
    prevX = currX;
    prevZ = currZ;
    x += rayV[0]*dt;
    z += rayV[1]*dt;
    currX = (int)(x*nx/(xmax-xmin));
    currZ = (int)(z*nz/(zmax-zmin));
    //printf("%d\n", ++i);
  }
}
void getPaths(Ray* rays)
{
  int** beam1 = new int*[nx];
  int** beam2 = new int*[nx];
  for(int i = 0; i < nrays; i++)
  {
    beam1[i] = new int[nz];
    beam2[i] = new int[nz];
    crossing* path1 = rays[i].getPath();
    crossing* path2 = rays[i+nrays].getPath();
    for(int j = 0; j < numstored;j++)
    {
      #pragma omp atomic update
      beam1[getX(&path1[j])][getZ(&path1[j])]++;
      #pragma omp atomic update
      beam2[getX(&path2[j])][getZ(&path2[j])]++;
    }
  }
}
//void get_track
void init_Track()
{

  //Initialize rays for each beam
  Ray* rays = new Ray[nbeams*nrays];
  //For beam 1::
  double dx = (xmax-xmin)/nrays;
  double dphase = (beam_max_z - beam_min_z)/nrays;
  int** count = new int*[nbeams];
  for (size_t i = 0; i < nbeams; i++) {
    count[i] = new int[nrays];
  }
  //#pragma omp parallel for num_threads(12)
  for(int i = 0; i < nrays; i++)
  {
    double k[2] = {0.0,1.0};
    double pos[2] =  {dx*i,0};
    rays[i] = *(new Ray(k, pos, dphase*i, exp(-1*pow(pow(dphase*i/sigma,2.0),4.0/2.0))));
    track(rays[i], count[0]);
  }
  double dz = (zmax-zmin)/nrays;
  //#pragma omp parallel for num_threads(12)
  for(int i = 0; i < nrays; i++)
  {

    double k[2] = {1.0,0.0};
    double pos[2] =  {0,dz*i};
    rays[nrays+i] = *(new Ray(k, pos, dphase*i, exp(-1*pow(pow(dphase*i/sigma,2.0),4.0/2.0))));
    track(rays[nrays+i], count[1]);
  }
}
