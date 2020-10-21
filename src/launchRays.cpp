#include "icf.hpp"
int** beam1;
int** beam2;
int printPath(Ray ray)
{
  crossing* path = ray.getPath();
  for(int i = 0; i < numstored; i++)
  {
    int x = ray.getRayX(i);
    int z = ray.getRayZ(i);
    if(x != -1 && z != -1)
    {
      //printf("(%d, %d)\n", ray.getRayX(i),  ray.getRayZ(i));
    }

  }
  return 0;
}
void track(Ray& ray, int* count, int raynum)
{
  //initialize ray variables
  double rayV[] = {(*(ray.getKin()))*pow(c,2)/omega, (*(ray.getKin()+1))*pow(c,2)/omega};//ray velocity
  double x = *ray.getPos();//initial x position
  double z = *(ray.getPos()+1);//initial z position
  int currX = (int)((x-xmin)*nx/(xmax-xmin));//initial x cell location
  int currZ = (int)((z-zmin)*nz/(zmax-zmin));//initial z cell location
  //storage variables to enable intelligent updates
  int prevX = 0;
  int prevZ = 0;
  double deltaX;
  double deltaZ;
  int i = 0;

  while(abs(x) <= xmax && abs(z) <= zmax)
  {
    //printf("%f  %f ||%f  %f\n", x, abs(x), z, abs(z));
    //If the ray enters a new cell
    if(prevX != currX || prevZ != currZ)
    {
      deltaX = x-dx*currX;
      deltaZ = z-dz*currZ;
      ray.addPath(currX, currZ);
      count[currX*nz+currZ]++;
      if(raynum == nrays)
      {
        //printf("(x_grid, z_grid): (%d, %d)|| (x,z): (%f, %f)\n", currX, currZ, x, z);
      }
    //If the ray spends multiple iterations in the same cell
    }else
    {
      addMag(ray.getLast(), sqrt(pow(deltaX, 2) + pow(deltaZ, 2)));
      deltaX = rayV[0]*dt;
      deltaZ = rayV[1]*dt;
    }

//    if(raynum == nrays)
//    {
//      printf("(x_grid, z_grid): (%d, %d)|| (x,z): (%f, %f)\n", currX, currZ, x, z);
//    }
    //
    //Update position variables for comparison in the next iteration
    prevX = currX;
    prevZ = currZ;
    x += rayV[0]*dt;
    z += rayV[1]*dt;
    currX = (int)((x-xmin)*nx/(xmax-xmin));
    currZ = (int)((z-zmin)*nz/(zmax-zmin));
    //printf("%d\n", ++i);
  }
  int a = (!raynum && printPath(ray));
  if(raynum == 0)
    printf("%d\n", a);
//  printf("(x,z): (%e,%e)\n", x, z);

}
void getPaths(Ray* rays)
{
  beam1 = new int*[nx];
  beam2 = new int*[nx];
  for(int i = 0; i < nrays; i++)
  {
    beam1[i] = new int[nz]{0};
    beam2[i] = new int[nz]{0};
  }
  for(int i = 0; i < nrays; i++)
  {
    if(i == 0)
    {
      printf("%s\n", "Printing ray in beam 2");
      printPath(rays[i+nrays]);
    }
    for(int j = 0; j < numstored;j++)
    {

      int x1 = rays[i].getRayX(j);
      int z1 = rays[i].getRayZ(j);
    //  std::cout << x1 << "  " << z1 << std::endl;

      int x2 = rays[i+nrays].getRayX(j);
      int z2 = rays[i+nrays].getRayZ(j);
      if(x1 != -1 && z1 != -1)
      {
        //std::cout << "adskjnd " << beam1[x1][z1] << std::endl;
        beam1[x1][z1]++;
      }
      if(x2 != -1 && z2 != -1)
          std::cout << beam1[x1][z1] << std::endl;
          beam2[x2][z2]++;

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
    double pos[2] =  {dx*i,zmin};
    Ray* p = rays + i;

    if(i == 0)
    {
      std::cout << "Pointer Test: " << p << std::endl;
    }
    rays[i] = Ray(k, pos, dphase*i, exp(-1*pow(pow(dphase*i/sigma,2.0),4.0/2.0)));
    track(rays[i], count[0], i);
  }
  double dz = (zmax-zmin)/nrays;
  //#pragma omp parallel for num_threads(12)
  for(int i = 0; i < nrays; i++)
  {

    double k[2] = {1.0,0.0};
    double pos[2] =  {xmin,dz*i};
    Ray* p = rays + i + nrays;
    rays[i+nrays] = Ray(k, pos, dphase*i, exp(-1*pow(pow(dphase*i/sigma,2.0),4.0/2.0)));

    track(rays[i+nrays], count[1],i+nrays);
  }
  getPaths(rays);
  std::cout << "Tester: " << rays<< std::endl;
  for(int i = 0; i < nrays; i++)
  {
    std::cout << "Tester: " << rays[i+nrays].getInd()<< std::endl;
  }

  updateH5(beam1, (char*)"Beam 1 Trajectory", beam2, (char*)"Beam 2 Trajectory");

}
