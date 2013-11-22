#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include "LocalGeo.h"
#endif

class Primitive;
class Intersection {
  public:
    LocalGeo localGeo;
    Primitive* primitive;
    Intersection();
    Intersection(LocalGeo localGeo, Primitive &primitive);
};