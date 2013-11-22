#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Intersection.h"
#include "Primitive.h"
#include "Tri.h"
#endif

class Trinormal : public Tri {
  vec3* normals;
  public:
    Trinormal(vec3 vertices[3], vec3 normals[3], vec3 ambient,
      vec3 diffuse, vec3 specular, vec3 emission,
      float shininess, mat4 transform);
    vec3 getNormal();  
};