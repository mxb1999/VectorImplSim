#include "icf.hpp"
int** count;
int printPath(Ray& ray)
{
  printf("%p", &ray);
  crossing* path = ray.getPath();
  for(int i = 0; i < numstored; i++)
  {
    int x = ray.getRayX(i);
    int z = ray.getRayZ(i);
    if(x != -1 && z != -1)
    {
      printf("%p: (%d, %d)\n", &ray, ray.getRayX(i),  ray.getRayZ(i));
    }
  }int** beam2;

  return 0;
}
void track(Ray& ray, int** count, int raynum, double* eden, double** force)
{

  double x = *ray.getPos();//initial x position
  double z = *(ray.getPos()+1);//initial z position
  int currX = (int)((x-xmin)*nx/(xmax-xmin));//initial x cell location
  int currZ = (int)((z-zmin)*nz/(zmax-zmin));//initial z cell location
  double kxinit = *(ray.getKin());
  double kzinit = *(ray.getKin()+1);

  //initialize ray variables
  double wpeInit = sqrt(eden[currX*nz + currZ]*1e6*pow(ec,2.0)/(me*e0));
  double k = sqrt((pow(omega,2.0)-pow(wpeInit,2.0))/pow(c,2.0));
  double knorm = sqrt(pow(kxinit,2.0)+pow(kzinit,2.0));
  double kx = k*kxinit/knorm;
  double kz = k*kzinit/knorm;
  double rayV[] = {kx*pow(c,2)/omega, kz*pow(c,2)/omega};//ray velocity

  //storage variables to enable intelligent updates
  int prevX = 0;
  int prevZ = 0;
  double deltaX;
  double deltaZ;
  int i = 0;

  while(abs(x) <= xmax && abs(z) <= zmax)
  {
    //If the ray enters a new cell
    int cond = (prevX != currX || prevZ != currZ);
    if(prevX != currX || prevZ != currZ)
    {
      deltaX = x-dx*currX;
      deltaZ = z-dz*currZ;
      ray.addPath(currX, currZ);
      count[currX][currZ]++;
    //If the ray spends multiple iterations in the same cell
    }else
    {
      addMag(ray.getLast(), sqrt(pow(deltaX, 2) + pow(deltaZ, 2)));
    }
    rayV[0] -= force[0][currX*nz + currZ]*dt;
    rayV[1] -= force[1][currX*nz + currZ]*dt;
    deltaX = rayV[0]*dt;
    deltaZ = rayV[1]*dt;
    //Update position variables for comparison in the next iteration
    prevX = currX;
    prevZ = currZ;
    x += rayV[0]*dt;
    z += rayV[1]*dt;

    currX = (int)((x-xmin)*nx/(xmax-xmin));
    currZ = (int)((z-zmin)*nz/(zmax-zmin));
    //if(raynum > nrays)
      //printf("XF <%e,%e>, %d\n", rayV[0], rayV[1], raynum);

  }
}

void print2D(double* arr, int dim1, int dim2)
{
  for (size_t i = 0; i < dim1; i++) {
    for (size_t j = 0; j < dim2; j++) {
      printf("%e ", arr[i*dim2 + j]);
    }
  //  printf("%s\n", );
  }
}
//void get_track
void init_Track()
{
  int* startC1 = new int[nx];
  int* startC2 = new int[nz];
  //Initialize rays for each beam
  Ray* rays = new Ray[nbeams*nrays];
  //For beam 1::
  double dstep = (beam_max_z-beam_min_z)/nrays;
  double dphase = (beam_max_z - beam_min_z)/nrays;
  count = new int*[nx];
  double* eden = eDensity();
  for (size_t i = 0; i < nx; i++) {
    count[i] = new int[nz];
  }
  auto check1 = std::chrono::high_resolution_clock::now();
  double** force = calculateForce();
  #pragma omp parallel for num_threads(12)
  for(int i = 0; i < nrays; i++)
  {
    startC1[(int)(((beam_min_z+dstep*i)-xmin)/dx)]++;
    double k[2] = {0.0,1.0};
    double pos[2] =  {beam_min_z+dstep*i,zmin};
    rays[i] = Ray(k, pos, dphase*i, exp(-1*pow(pow(dphase*i/sigma,2.0),4.0/2.0)));
    track(rays[i], count, i, eden, force);
  }
  #pragma omp parallel for num_threads(12)
  for(int i = 0; i < nrays; i++)
  {

    double k[2] = {1.0,0.0};
    double pos[2] =  {xmin,beam_min_z+dstep*i};
    rays[i+nrays] = Ray(k, pos, dphase*i, exp(-1*pow(pow(dphase*i/sigma,2.0),4.0/2.0)));
    track(rays[i+nrays], count,i+nrays, eden, force);
  }
  //getPaths(rays);
  auto check2 = std::chrono::high_resolution_clock::now();
  std::cout << "Raylaunch: " << std::chrono::duration_cast<std::chrono::milliseconds>(check2-check1).count() << " ms" << std::endl;

  /*for (size_t i = 0; i < nx; i++) {
    for (size_t j = 0; j < nz; j++) {
      if(count[i][j] != 0)
        std::cout << count[i][j] << " ";
    }
    std::cout << std::endl;
  }*/

  updateH5(count, (char*)"Beam 1 Trajectory", count, (char*)"Beam 2 Trajectory");

}
