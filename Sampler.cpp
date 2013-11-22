#include "Sampler.h"

Sampler::Sampler(int w, int h) {
  this->w = w;
  this->h = h;
  i = 0.5;
  j = 0.5;
}

bool Sampler::getSample(Sample &sample) {
  if (i > h) { return false; }

  sample.x = j;
  sample.y = i;
  if (j > w-1) {
      i++;
      j = 0.5;
  } else { j++; }
  return true;
}