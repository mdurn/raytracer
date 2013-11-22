#include "RayTracer.h"

RayTracer::RayTracer(int _maxdepth, vector<Primitive*> &primitives,
    vector<Light*> &lights) : maxdepth(_maxdepth) {
  this->primitives = &primitives;
  this->lights = &lights;
}


void RayTracer::trace(Ray& ray, int depth, vec3* color) {
  if (depth > maxdepth) { return; }
  float thit = INFINITY;
  Intersection in;
  bool hit = false;
  //find nearest object intersection
  for(int i = 0; i < primitives->size(); i++) {
    if ((*primitives)[i]->intersect(ray, &thit, &in)){ hit = true; }
  }

  //calculate lighting against intersection
  if (hit) {
    *color += in.primitive->getAmbient() + in.primitive->getEmission();
    //check rays to all light sources
    for(int i = 0; i < lights->size(); i++) {
      Ray lray;
      Intersection lin;
      (*lights)[i]->generateLightRay(in.localGeo, &lray, color);
      thit = lray.getMaxT();
      bool blocked = false;
      //only use lights that are not blocked by objects
      for(int j = 0; j < primitives->size(); j++) {
        if ((*primitives)[j]->intersect(lray, &thit, &lin)){
          blocked = true;
          break;
        }
      }
      if (!blocked) {
        *color += calculateColor(in, *(*lights)[i], ray, lray);
      }

    }
    if (glm::length(in.primitive->getShininess()) != 0.0) {
      vec3 reflectNormal = glm::normalize(ray.getDir() - 2.0f * in.localGeo.normal *
        (glm::dot(ray.getDir(), in.localGeo.normal)));
      vec3 reflectPos = in.localGeo.pos;
      Ray reflectRay(reflectPos, reflectNormal, 0.0, INFINITY);
      vec3 *tmpColor = new vec3();
      trace(reflectRay, depth + 1, tmpColor);
      *color += in.primitive->getSpecular() * *tmpColor;
    }
  }
}

vec3 RayTracer::calculateColor(Intersection &in, Light &light, Ray &cameraRay, Ray &lray) {
  vec3 halfvec = glm::normalize(lray.getDir() - cameraRay.getDir());
  float nDotL = max(glm::dot(in.localGeo.normal, lray.getDir()), 0.0f);
  vec3 lambert = in.primitive->getDiffuse() * max(nDotL, 0.0f);
  float nDotH = max(glm::dot(in.localGeo.normal, halfvec), 0.0f);
  vec3 phong = in.primitive->getSpecular() *
    pow(max(nDotH, 0.0f), in.primitive->getShininess());
  float r = (lray.getMaxT() == INFINITY) ? numeric_limits<float>::max() :
    glm::length(lray.getDir()*lray.getMaxT());
  vec3 attn = light.getLightAttn();
  vec3 color = light.getLightColor()/(attn[0] + attn[1]*r + attn[2]*r*r);
  color *= (lambert + phong);
  return color;
}
