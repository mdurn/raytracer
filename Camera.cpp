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
  float x = (sample.getX() - screenW*0.5)/(screenW*0.5);
  float y = (screenH*0.5 - sample.getY())/(screenH*0.5);;
  float a = tan(fovx*0.5) * x;
  float b = tan(fovy*0.5) * y;
  ray->pos = eye;
  ray->dir = glm::normalize(a*u + b*v - w);
}