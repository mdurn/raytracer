#include "Trinormal.h"

Trinormal::Trinormal(vec3 vertices[3], vec3 normals[3], vec3 ambient,
    vec3 diffuse, vec3 specular, vec3 emission,
    float shininess, mat4 transform) : 
      Tri(vertices, ambient, diffuse,
        specular, emission, shininess, transform) {
  this->normals = normals;
}

vec3 Trinormal::getNormal() {
  return (normals[0] * alpha) +
    (normals[1] * beta) + (normals[2] * gamma);
}