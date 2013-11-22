#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Intersection.h"
#endif

class Primitive {
  protected:
    vec3 ambient, diffuse, specular, emission;
    float shininess;
    mat4 transform, inverseTransform;
  public:
    Primitive(vec3 ambient, vec3 diffuse, vec3 specular,
      vec3 emission, float shininess, mat4 transform);
    virtual ~Primitive();
    virtual bool intersect(Ray& _ray, float* thit, Intersection* in) = 0;   
    virtual bool intersectP(Ray& ray) = 0;
    vec3 getAmbient();
    vec3 getDiffuse();
    vec3 getSpecular();
    vec3 getEmission();
    vec3 mat4TimesVec3(mat4 matrix, vec3 vec, float w);
    float getShininess();
    mat4 getTransform();
};