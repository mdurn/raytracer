#include "scene.cpp"

int main(int argc, char* argv[]) {
  //omp_lock_t lock;
  //omp_init_lock(&lock);

  if (argc < 1) {
    cerr << "Usage: raytrace inputfile.test\n"; 
    exit(-1); 
  }

  cout << "READING FILE" << "\n";
  readfile(argv[1]);
  cout << "FINISHED READING FILE" << "\n";

  Sampler sampler = Sampler(w, h);
  RayTracer raytracer = RayTracer(maxdepth, primitives, lights);
  Film film(w, h);

  cout << "Initialized RayTracer Variables" << "\n";

  //#pragma omp parallel for
  for (int i = 0; i < w*h; ++i) {
    Ray ray;
    vec3 color;
    Sample sample;

    sampler.getSample(sample);
    camera->generateRay(sample, &ray);
    raytracer.trace(ray, 0, &color);
    film.commit(sample, color);
  }
  //omp_destroy_lock(&lock);

  if (fname.empty()) { fname = (string)argv[1] + ".png"; }
  film.writeImage(fname);

  return 0;
}
