#include "Film.h"

Film::Film(int width, int height) {
  w = width;
  h = height;
  image = new BYTE[w*h*3];
}

Film::~Film() {
  delete image;
}

void Film::commit(Sample &sample, vec3 &color) {
  int i = sample.getY();
  int j = sample.getX();
  cout << "COMMITTING PIXEL: " << i << "," << j << "\n";
  // reverse order of colors since FreeImage uses BGR
  for (int k = 0; k < 3; k++) {
    image[i*w*3+j*3+k] = min((int)(color[2-k] * 255), 255);
  }
}

void Film::writeImage(string fname) {
  FreeImage_Initialise();
  FIBITMAP *img = FreeImage_ConvertFromRawBits(image, w, h, w * 3, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, true);

  cout << "Saving screenshot: " << fname << "\n";

  FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
  FreeImage_DeInitialise();
}
