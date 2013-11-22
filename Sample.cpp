#include "Sample.h"

Sample::Sample() : x(0.5), y(0.5){}
Sample::Sample(float _x, float _y) : x(_x), y(_y) {}
float Sample::getX() { return x; }
float Sample::getY() { return y; }