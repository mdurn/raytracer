#include "Sphere.h"
#include <iostream>

Sphere::Sphere(vec3 pos, float radius, vec3 ambient,
    vec3 diffuse, vec3 specular, vec3 emission,
    float shininess, mat4 transform) : 
      Primitive(ambient, diffuse, specular,
        emission, shininess, transform) {
  this->pos = pos;
  this->radius = radius;
}

bool Sphere::intersect(Ray& _ray, float* thit, Intersection* in) {
  Ray ray = _ray.transform(inverseTransform);
  if (!intersectP(ray)) { return false; }

  float t1 = (-b - sqrt(disc))/(2*a);
  float t2 = (-b + sqrt(disc))/(2*a);

  float t;
  if (t1 > 0 && t2 > 0) { t = (t1 < t2) ? t1 : t2; }
  else if (t1 == t2) { t = t1; }
  else if (t1 > 0) { t = t1; }
  else if (t2 > 0) { t = t2; }
  else { return false; }

  if (*thit < t) { return false; }

  *thit = t;
  in->localGeo.pos = mat4TimesVec3(getTransform(),
    (ray.getPos() + t * ray.getDir()), 1.0);
  in->localGeo.normal = glm::normalize(mat4TimesVec3(
    glm::transpose(inverseTransform), 
    mat4TimesVec3(inverseTransform, in->localGeo.pos, 1.0) - pos, 0.0));
  //shift position slightly towards normal (epsilon shift)
  in->localGeo.pos = in->localGeo.pos + in->localGeo.normal * epsilon;

  in->primitive = this;

  return true;
}

bool Sphere::intersectP(Ray& ray) {
  a = glm::dot(ray.getDir(), ray.getDir());
  b = 2.0f * glm::dot(ray.getDir(), ray.getPos() - pos);
  c = glm::dot(ray.getPos() - pos, ray.getPos() - pos) - radius*radius;
  disc = b*b - 4*a*c;
  if (disc < 0) { return false; }

  return true;
}
