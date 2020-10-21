#include "icf.hpp"

int main(int argc, char** argv)
{
  init_Track();



  char filename[] = "src/plot.py";
    FILE* fp;
    Py_Initialize();

    fp = _Py_fopen(filename, "r");
    PyRun_SimpleFile(fp, filename);
    Py_Finalize();

  return 0;
}
