#include "LocalGeo.h"

LocalGeo::LocalGeo() {}

LocalGeo::LocalGeo(vec3 pos, vec3 normal) {
  this->pos = pos;
  this->normal = normal;
}