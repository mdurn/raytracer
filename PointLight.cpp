#include "PointLight.h"

PointLight::PointLight(vec3 _lightposn, vec3 _lightcolor, vec3 _lightattn) :
    Light(_lightposn, _lightcolor, _lightattn) {}

void PointLight::generateLightRay(LocalGeo& local, Ray* lray, vec3* lcolor) {
  lray->dir = glm::normalize(lightposn - local.pos);
  lray->pos = local.pos;
  lray->t_max = glm::length(lightposn - local.pos);
}
