#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include "Sample.h"
#include <iostream>
#include <string>
#endif

#include <FreeImage.h>

class Film {
  int w, h;
  BYTE *image;
  public:
    Film(int width, int height);
    ~Film();
    void commit(Sample &sample, vec3 &color);
    void writeImage(string fname);
};