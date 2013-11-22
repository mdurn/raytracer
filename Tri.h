#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Intersection.h"
#include "Primitive.h"
#endif

class Tri : public Primitive {
  protected:
    vec3 a, b, c;
    vec3 planeNormal;
    float t, alpha, beta, gamma; //frequently recalculated
    float denom; //calulated once
    vec3 w, p, vCrossW, uCrossW; //frequently recalculated
    vec3 u, v, uCrossV, vCrossU; //calculated once
  public:
    Tri(vec3 vertices[3], vec3 ambient,
      vec3 diffuse, vec3 specular, vec3 emission,
      float shininess, mat4 transform);
    bool intersect(Ray& _ray, float* thit, Intersection* in);    
    bool intersectP(Ray& ray);
    virtual vec3 getNormal();
};