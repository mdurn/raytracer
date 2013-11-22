#include "Camera.h"
#include <iostream>

Camera::Camera(vec3 eye, vec3 center, vec3 up,
    float fovy, int screenW, int screenH) {
  this->eye = eye;
  this->center = center;
  this->up = up;
  this->screenW = screenW;
  this->screenH = screenH;
  this->fovy = fovy;
  this->fovx = 2 * atan(tan(fovy * 0.5) * screenW/screenH);
  w = glm::normalize(eye - center);
  u = glm::normalize(glm::cross(up, w));
  v = glm::cross(w, u);
}

void Camera::generateRay(Sample& sample, Ray* ray) {
  float x = (sample.getX() - screenW/2.0)/(screenW/2.0);
  float y = (screenH/2.0 - sample.getY())/(screenH/2.0);;
  float a = tan(fovx/2) * x;
  float b = tan(fovy/2) * y;
  ray->pos = eye;
  ray->dir = glm::normalize(a*u + b*v - w);
}