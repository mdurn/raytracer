// Sample represents a window pixel coordinate.

class Sample {
  float x, y;
  public:
    friend class Sampler;
    Sample();
    Sample(float x, float y);
    float getX();
    float getY();
};