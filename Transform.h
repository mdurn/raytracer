#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#endif

class Transform  
{
public:
	Transform();
	virtual ~Transform();
  static mat3 rotate(const float degrees, const vec3& axis) ;
  static mat4 scale(const float &sx, const float &sy, const float &sz) ; 
  static mat4 translate(const float &tx, const float &ty, const float &tz);
};

