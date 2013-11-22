#include "Transform.h"

mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
  float rads = degrees * pi / 180.0;
  mat3 identity(1.0);
  vec3 normalized = glm::normalize(axis);
  mat3 aa_t(
    normalized.x * normalized.x, normalized.x * normalized.y, normalized.x * normalized.z,
    normalized.x * normalized.y, normalized.y * normalized.y, normalized.y * normalized.z,
    normalized.x * normalized.z, normalized.y * normalized.z, normalized.z * normalized.z);
  mat3 a_star(0.0, normalized.z, -normalized.y,
    -normalized.z, 0.0, normalized.x,
    normalized.y, -normalized.x, 0.0);
  return (cos(rads) * identity) + ((1 - cos(rads)) * aa_t) + (sin(rads) * a_star);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  return mat4(
    sx, 0.0, 0.0, 0.0,
    0.0, sy, 0.0, 0.0,
    0.0, 0.0, sz, 0.0,
    0.0, 0.0, 0.0, 1.0);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  return mat4(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    tx, ty, tz, 1.0);
}

Transform::Transform() {}

Transform::~Transform() {}