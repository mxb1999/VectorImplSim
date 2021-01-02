#include <iostream>
#include <cstdlib>
#include <omp.h>

template <typename T>

class threadStack
{
private:
  T* head;
  int lastThreadID;
public:
  threadStack();
  int push();
  int pop();
  void debug();
}
