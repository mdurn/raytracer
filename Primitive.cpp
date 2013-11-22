#include "Primitive.h"

Primitive::Primitive(vec3 ambient, vec3 diffuse, vec3 specular,
    vec3 emission, float shininess, mat4 transform) {
  this->ambient = ambient;
  this->diffuse = diffuse;
  this->specular = specular;
  this->emission = emission;
  this->shininess = shininess;
  this->transform = transform;
  this->inverseTransform = glm::inverse(transform);
}

vec3 Primitive::getAmbient() { return ambient; }
vec3 Primitive::getDiffuse() { return diffuse; }
vec3 Primitive::getSpecular() { return specular; }
vec3 Primitive::getEmission() { return emission; }
float Primitive::getShininess() { return shininess; }
mat4 Primitive::getTransform() { return transform; }

vec3 Primitive::mat4TimesVec3(mat4 matrix, vec3 vec, float w) {
  vec4 v4(vec[0], vec[1], vec[2], w);
  v4 = matrix * v4;
  vec3 transVec = (w == 0) ? vec3(v4[0], v4[1], v4[2]) :
    vec3(v4[0]/v4.w, v4[1]/v4.w, v4[2]/v4.w);
  return transVec;
}