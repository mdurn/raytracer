#include "Scene.h"

Scene::Scene(const char* filename) {
  maxdepth = 5;
  attenuation = vec3(1.0, 0.0, 0.0);
  ambient = vec3(0.2, 0.2, 0.2);
  readfile(filename);
  if (fname.empty()) { fname = (string) filename  + ".png"; }
}

void Scene::rightmultiply(const mat4 & M, stack<mat4> &transfstack) 
{
  mat4 &T = transfstack.top(); 
  T = T * M; 
}

bool Scene::readvals(stringstream &s, const int numvals, float* values) 
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i]; 
    if (s.fail()) {
      cout << "Failed reading value " << i << " will skip\n"; 
      return false;
    }
  }
  return true; 
}

void Scene::readfile(const char* filename) 
{
  string str, cmd; 
  ifstream in;
  in.open(filename); 
  if (in.is_open()) {

    stack <mat4> transfstack; 
    transfstack.push(mat4(1.0));  // identity

    getline (in, str); 
    while (in) {
      if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
        // Ruled out comment and blank lines 

        stringstream s(str);
        s >> cmd; 
        int i; 
        float values[10]; // Position and color for light, colors for others
                            // Up to 10 params for cameras.  
        bool validinput; // Validity of input 

        // Lighting Command
        if (cmd == "point" || cmd == "directional") {
            validinput = readvals(s, 6, values); // Position/color for lts.
            if (validinput) {
              vec3 lightposn, lightcolor;
              for (i = 0; i < 3; i++) {
                lightposn[i] = values[i];
                lightcolor[i] = values[i + 3];
              }
              if (cmd == "point") { lights.push_back(new PointLight(lightposn, lightcolor, attenuation));
              } else { lights.push_back(new DirectionalLight(lightposn, lightcolor)); }
            }
          }
          else if (cmd == "attenuation") {
            validinput = readvals(s, 3, values);
            if (validinput) {
              for (i = 0; i < 3; i++) {
                attenuation[i] = values[i];
              }
            }
          }

        // Material Commands 
        // Ambient, diffuse, specular, shininess properties for each object.
          else if (cmd == "ambient") {
          validinput = readvals(s, 3, values); // colors 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              ambient[i] = values[i]; 
            }
          }
        } else if (cmd == "diffuse") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              diffuse[i] = values[i]; 
            }
          }
        } else if (cmd == "specular") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              specular[i] = values[i]; 
            }
          }
        } else if (cmd == "emission") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              emission[i] = values[i]; 
            }
          }
        } else if (cmd == "shininess") {
          validinput = readvals(s, 1, values); 
          if (validinput) {
            shininess = values[0]; 
          }
        } else if (cmd == "size") {
          validinput = readvals(s,2,values); 
          if (validinput) { 
            w = (int) values[0]; h = (int) values[1]; 
          } 
        } else if (cmd == "camera") {
          validinput = readvals(s,10,values); // 10 values eye cen up fov
          if (validinput) {
            eyeinit = vec3(values[0], values[1], values[2]);
            center = vec3(values[3], values[4], values[5]);
            upinit = vec3(values[6], values[7], values[8]);
            fovy = values[9];
          }
        }

        // raytracer bounces
        else if (cmd == "maxdepth") {
          validinput = readvals(s,1,values);
          if (validinput) {
            maxdepth = (int) values[0];
          }
        }

        // Vertex info for tris (triangles) and trinormals (triangles
        // with specified vertex normals).
        else if (cmd == "maxverts") {
          validinput = readvals(s,1,values);
          if (validinput) {
            maxverts = (int) values[0];
            vertices = new vec3[maxverts];
          }
        } else if (cmd == "maxvertnorms") {
          validinput = readvals(s,1,values);
          if (validinput) {
            maxvertnorms = (int) values[0];
            vertexnormals = new vertexnormal[maxvertnorms];
          }
        } else if (cmd == "vertex") {
          if (numverts == maxverts) { 
            cerr << "Reached Maximum Number of Vertices " << numverts << " Will ignore further vertices\n";
          } else {
            validinput = readvals(s,3,values);
            if (validinput) {
              vertices[numverts] = vec3(values[0], values[1], values[2]);
              ++numverts;
            }
          }
        } else if (cmd == "vertexnormal") {
          if (numvertnorms == maxvertnorms) { 
            cerr << "Reached Maximum Number of VertexNormals " << numvertnorms << " Will ignore further vertices\n";
          } else {
            validinput = readvals(s,3,values);
            if (validinput) {
              vertexnormals[numvertnorms].v = vec3(values[0], values[1], values[2]);
              vertexnormals[numvertnorms].n = vec3(values[3], values[4], values[5]);
              ++numvertnorms;
            }
          }
        }

        else if (cmd == "sphere" || cmd == "tri" || cmd == "trinormal") {
          int numvals = (cmd == "sphere") ? 4 : 3;
          validinput = readvals(s, numvals, values);
          if (validinput) {
            vec3 _pos;
            float _radius, _shininess;
            mat4 _transform;

            vec3 _ambient, _diffuse, _specular, _emission;
            vec3* _vertices = new vec3[3];
            vec3* _normals = new vec3[3];

            if (cmd == "sphere") {
              _pos = vec3(values[0], values[1], values[2]);
              _radius = values[3];
            } else if (cmd == "tri") {
              for (int i = 0; i < 3; i++) {
                _vertices[i] = vertices[(int)values[i]];
              }
            } else {
              for (int i = 0; i < 3; i++) {
                _vertices[i] = vertexnormals[(int)values[i]].v;
                _normals[i] = vertexnormals[(int)values[i]].n;
              }
            } 

            // Set the object's light properties
            _ambient = ambient; 
            _diffuse = diffuse; 
            _specular = specular; 
            _emission = emission;
            _shininess = shininess; 

            // Set the object's transform
            _transform = transfstack.top(); 

            if (cmd == "sphere") {
              primitives.push_back(
                new Sphere(_pos, _radius, _ambient, _diffuse,
                  _specular, _emission, _shininess, _transform)); 
            } else if (cmd == "tri") {
              primitives.push_back(
                new Tri(_vertices, _ambient, _diffuse,
                  _specular, _emission, _shininess, _transform));
            } else if (cmd == "trinormal") {
              primitives.push_back(
                new Trinormal(_vertices, _normals, _ambient, _diffuse,
                  _specular, _emission, _shininess, _transform)); 
            }
          }
        }

        else if (cmd == "translate") {
          validinput = readvals(s,3,values); 
          if (validinput) {
            rightmultiply(Transform::translate(values[0], values[1], values[2]), transfstack);
          }
        }
        else if (cmd == "scale") {
          validinput = readvals(s,3,values); 
          if (validinput) {
            rightmultiply(Transform::scale(values[0], values[1], values[2]), transfstack);
          }
        }
        else if (cmd == "rotate") {
          validinput = readvals(s,4,values); 
          if (validinput) {
            vec3 normalized = glm::normalize(vec3(values[0], values[1], values[2]));
            mat4 mat4rotate(Transform::rotate(values[3], normalized));
            rightmultiply(mat4rotate, transfstack);
          }
        }

        // I include the basic push/pop code for matrix stacks
        else if (cmd == "pushTransform") {
          transfstack.push(transfstack.top()); 
        } else if (cmd == "popTransform") {
          if (transfstack.size() <= 1) {
            cerr << "Stack has no elements.  Cannot Pop\n"; 
          } else {
            transfstack.pop(); 
          }
        }

        else if (cmd == "output") {
          s >> fname;
        }

        else {
          cerr << "Unknown Command: " << cmd << " Skipping \n"; 
        }
      }
      getline (in, str); 
    }

    camera = new Camera(eyeinit, center, upinit, pi/180.0*fovy, w, h);

  } else {
    cerr << "Unable to Open Input Data File " << filename << "\n"; 
    throw 2;
  }
}

int Scene::getW() { return w; }
int Scene::getH() { return h; }
int Scene::getMaxDepth() { return maxdepth; }
vector<Primitive*>* Scene::getPrimitivesRef() { return &primitives; }
vector<Light*>* Scene::getLightsRef() { return &lights; }
Camera Scene::getCamera() { return *camera; }
string Scene::getFileName() { return fname; }

Scene::~Scene() {
  delete camera;
  delete vertices;
  delete normvertices;
  for (int i = 0; i < lights.size(); i++) {
    delete lights[i];
  }
  for (int i = 0; i < primitives.size(); i++) {
    delete primitives[i];
  }
}
