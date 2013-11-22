// Ray representation

#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#endif

class Ray {
  vec3 pos, dir;
  float t_min, t_max;
  public:
    Ray();
    Ray(vec3 pos, vec3 dir, float t_min, float t_max);
    vec3 getPos();
    vec3 getDir();
    float getMaxT();
    Ray transform(mat4 &matrix);
    friend class Camera;
    friend class PointLight;
    friend class DirectionalLight;
};