#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include "Ray.h"
#include "Sample.h"
#endif

typedef glm::vec3 vec3;

class Camera {
    vec3 eye, center, up, u, v, w;
    float fovy, fovx;
    int screenW, screenH;
  public:
    Camera(vec3 eye, vec3 center, vec3 up,
      float fovy, int screenW, int screenH);
    void generateRay(Sample& sample, Ray* ray);
};