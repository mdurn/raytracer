#include "Ray.h"

Ray::Ray() {
  pos = vec3();
  dir = vec3();
  t_min = 0.0;
  t_max = INFINITY;
}

Ray::Ray(vec3 _pos, vec3 _dir, float _t_min, float _t_max) :
    pos(_pos), dir(_dir), t_min(_t_min), t_max(_t_max) {}

vec3 Ray::getPos() { return pos; }
vec3 Ray::getDir() { return dir; }
Ray Ray::transform(mat4 &matrix) {
  vec4 p0(pos[0], pos[1], pos[2], 1.0);
  vec4 p1(dir[0], dir[1], dir[2], 0.0);
  p0 = matrix * p0;
  p1 = matrix * p1;
  vec3 _pos(vec3(p0[0]/p0.w, p0[1]/p0.w, p0[2]/p0.w));
  vec3 _dir(vec3(p1[0], p1[1], p1[2]));
  return Ray(_pos, _dir, t_min, t_max);
}
float Ray::getMaxT() { return t_max; }
