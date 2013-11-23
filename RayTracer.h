// Raytracing functionality.

#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include <vector>
#include <iostream>
#include "Ray.h"
#include "LocalGeo.h"
#include "Light.h"
#include "Intersection.h"
#include "Primitive.h"
#include "Sphere.h"
#include "Tri.h"
#include "Trinormal.h"
#endif

typedef glm::vec3 vec3;

class RayTracer {
  int maxdepth;
  vector<Primitive*>* primitives;
  vector<Light*>* lights;
  public:
    RayTracer(int _maxdepth, vector<Primitive*> &primitives, vector<Light*> &lights);
    void trace(Ray& ray, int depth, vec3* color);
    vec3 calculateColor(Intersection &in, Light &light, Ray &cameraRay, Ray &lray);
};