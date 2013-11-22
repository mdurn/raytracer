#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Light.h"
#endif

class DirectionalLight : public Light {
  public:
    DirectionalLight(vec3 _lightposn, vec3 _lightcolor);
    void generateLightRay(LocalGeo& local, Ray* lray, vec3* lcolor);
};