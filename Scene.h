// Readfile definitions 

#ifndef INCLUDES
#define INCLUDES
#include "definitions.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <vector>
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
#endif

class Scene {
  //filename
  string fname;

  //camera
  vec3 eyeinit, upinit, center; 
  int w, h; 
  float fovy; 
  Camera *camera;

  // Raytracer settings
  int maxdepth; // Max number of bounces (default 5)

  // Geometry settings
  int maxverts, numverts, maxvertnorms, numvertnorms;
  vec3 *vertices, *normvertices;
  struct vertexnormal {
    vec3 v, n;
  } *vertexnormals;

  // Lighting
  vector<Light*> lights;
  vec3 attenuation; //default (1.0, 0.0, 0.0)

  // Materials (read from file) 
  // With multiple objects, these are colors for each.
  vec3 ambient; //default (0.2, 0.2, 0.2)
  vec3 diffuse, specular, emission; 
  float shininess; 

  // Primitives  
  vector<Primitive*> primitives; 

  public:
    Scene(const char* filename);
    ~Scene();
    void rightmultiply (const mat4 &M, stack<mat4> &transfstack);
    bool readvals (stringstream &s, const int numvals, float* values);
    void readfile (const char* filename);
    int getW();
    int getH();
    int getMaxDepth();
    vector<Primitive*>* getPrimitivesRef();
    vector<Light*>* getLightsRef();
    Camera getCamera();
    string getFileName();
};
