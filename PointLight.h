#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Light.h"
#endif

class PointLight : public Light {
  public:
    PointLight(vec3 _lightposn, vec3 _lightcolor, vec3 _lightattn);
    void generateLightRay(LocalGeo& local, Ray* lray, vec3* lcolor);
};