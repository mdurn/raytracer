#include "Light.h"

Light::Light(vec3 _lightposn, vec3 _lightcolor, vec3 _lightattn) {
  lightposn = _lightposn;
  lightcolor = _lightcolor;
  lightattn = _lightattn;
}

Light::Light(vec3 _lightposn, vec3 _lightcolor) {
  lightposn = _lightposn;
  lightcolor = _lightcolor;
  vec3 attn(1.0, 0.0, 0.0);
  lightattn = attn;
}

vec3 Light::getLightPos() { return lightposn; }
vec3 Light::getLightColor() { return lightcolor; }
vec3 Light::getLightAttn() { return lightattn; }