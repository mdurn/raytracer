#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Intersection.h"
#include "Primitive.h"
#endif

class Sphere : public Primitive {
  vec3 pos;
  float radius;
  float a, b, c, disc; //updated by intersections (for quad formula)
  public:
    Sphere(vec3 pos, float radius, vec3 ambient,
      vec3 diffuse, vec3 specular, vec3 emission,
      float shininess, mat4 transform);
    bool intersect(Ray& _ray, float* thit, Intersection* in);   
    bool intersectP(Ray& ray);
};