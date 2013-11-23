#include "Tri.h"

Tri::Tri(vec3 vertices[3], vec3 ambient,
    vec3 diffuse, vec3 specular, vec3 emission,
    float shininess, mat4 transform) : 
      Primitive(ambient, diffuse, specular,
        emission, shininess, transform) {
  a = vertices[0];
  b = vertices[1];
  c = vertices[2];
  u = b - a;
  v = c - a;
  planeNormal = glm::normalize(glm::cross(u, v));
  vCrossU = glm::cross(v, u);
  uCrossV = glm::cross(u, v);
  denom = glm::length(vCrossU);
}

bool Tri::intersect(Ray& _ray, float* thit, Intersection* in) {
  Ray ray = _ray.transform(inverseTransform);
  if (!intersectP(ray)) { return false; }
  if (*thit < t) { return false; }

  p = ray.getPos() + ray.getDir() * t;
  w = p - a;
  vCrossW = glm::cross(v, w);
  uCrossW = glm::cross(u, w);

  if (glm::dot(vCrossW, vCrossU) < 0) { return false; }
  if (glm::dot(uCrossW, uCrossV) < 0) { return false; }

  beta = glm::length(vCrossW)/denom;
  gamma = glm::length(uCrossW)/denom;
  alpha = 1 - beta - gamma;

  if (!(beta <= 1 && gamma <= 1 && beta + gamma <= 1)) { return false; }

  *thit = t;
  in->localGeo.pos = mat4TimesVec3(getTransform(),
    (ray.getPos() + t * ray.getDir()), 1.0);
  in->localGeo.normal = getNormal();
  //shift position slightly towards normal (epsilon shift)
  in->localGeo.pos = in->localGeo.pos + in->localGeo.normal * epsilon;
  in->primitive = this;

  return true;
}

bool Tri::intersectP(Ray& ray) {
  t = (glm::dot(a, planeNormal) - glm::dot(ray.getPos(), planeNormal)) /
    glm::dot(ray.getDir(), planeNormal);
  if (t > 0) { return true; }
  else { return false; }
}

vec3 Tri::getNormal() {
  return glm::normalize(mat4TimesVec3(
    glm::transpose(inverseTransform), planeNormal, 0.0));
}
