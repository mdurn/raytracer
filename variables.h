#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include <vector>
#include <string>
#include "Ray.h"
#include "Sample.h"
#include "Camera.h"
#include "LocalGeo.h"
#include "Light.h"
#include "Intersection.h"
#include "Primitive.h"
#endif

string fname;

vec3 eyeinit ; 
vec3 upinit ; 
vec3 center ; 
int w, h ; 
float fovy ; 

Camera *camera;

// Raytracer settings
int maxdepth = 5 ; // Max number of bounces

// Geometry settings
int maxverts;
int numverts;
int maxvertnorms;
int numvertnorms;
vec3 * vertices;
vec3 * normvertices;
struct vertexnormal {
  vec3 v ;
  vec3 n ;
} *vertexnormals ;

// Lighting
vector<Light*> lights;
vec3 attenuation(1.0, 0.0, 0.0);

// Materials (read from file) 
// With multiple objects, these are colors for each.
vec3 ambient(0.2, 0.2, 0.2) ; 
vec3 diffuse ; 
vec3 specular ; 
vec3 emission ; 
float shininess ; 

// Primitives  
vector<Primitive*> primitives; 