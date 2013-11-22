#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include "Ray.h"
#include "LocalGeo.h"
#endif

class Light {
  protected:
    vec3 lightposn, lightcolor, lightattn;
  public:
    enum Type { point, direction };
    Light(vec3 _lightposn, vec3 _lightcolor, vec3 _lightattn);
    Light(vec3 _lightposn, vec3 _lightcolor);
    vec3 getLightPos();
    vec3 getLightColor();
    vec3 getLightAttn();
    virtual void generateLightRay(LocalGeo& local, Ray* lray, vec3* lcolor) = 0;
};