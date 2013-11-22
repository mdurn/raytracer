#include "DirectionalLight.h"
#include <iostream>

DirectionalLight::DirectionalLight(vec3 _lightposn, vec3 _lightcolor) :
    Light(_lightposn, _lightcolor) {
  lightattn = vec3(1.0, 0.0, 0.0);
}

void DirectionalLight::generateLightRay(LocalGeo& local, Ray* lray, vec3* lcolor) {
  lray->dir = glm::normalize(lightposn); 
  lray->pos = local.pos;
  lray->t_max = INFINITY;
}
