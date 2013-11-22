#include "Intersection.h"

Intersection::Intersection() {}

Intersection::Intersection(LocalGeo localGeo, Primitive &primitive) {
  this->localGeo = localGeo;
  this->primitive = &primitive;
}