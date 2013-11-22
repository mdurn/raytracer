// Sampler iterates through and returns window pixel coordinate Sample.

#ifndef INCLUDES
#define INCLUDES
#include "Sample.h"
#endif

class Sampler {
  int w, h;
  float i, j;
public:
  Sampler(int w, int h);
  bool getSample(Sample &sample);
};