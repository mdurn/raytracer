// Readfile definitions 

#ifndef INCLUDES
#define INCLUDES
//still issues with multithreading
// #ifdef _OPENMP
// #include <omp.h>
// #endif
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <vector>
#include "definitions.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Transform.h" 
#include "Sample.h"
#include "Sampler.h"
#include "Intersection.h"
#include "Primitive.h"
#include "Sphere.h"
#include "Tri.h"
#include "Trinormal.h"
#include "Camera.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "RayTracer.h"
#include "Film.h"

//global variables
#include "variables.h"
#endif

void matransform (stack<mat4> &transfstack, float * values) ;
void rightmultiply (const mat4 & M, stack<mat4> &transfstack) ;
bool readvals (stringstream &s, const int numvals, float * values) ;
void readfile (const char * filename) ;
