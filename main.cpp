#include "Scene.h"
// #ifdef _OPENMP
// #include <omp.h>
// #endif

int main(int argc, char* argv[]) {
  //omp_lock_t lock;
  //omp_init_lock(&lock);

  if (argc < 1) {
    cerr << "Usage: raytrace inputfile.test\n"; 
    exit(-1); 
  }

  cout << "Constructing Scene" << "\n";
  Scene scene(argv[1]);
  cout << "Finished Constructing Scene" << "\n";

  Sampler sampler = Sampler(scene.getW(), scene.getH());
  RayTracer raytracer = RayTracer(scene.getMaxDepth(),
    *(scene.getPrimitivesRef()), *(scene.getLightsRef()));
  Film film(scene.getW(), scene.getH());

  cout << "Initialized RayTracer Variables" << "\n";

  //#pragma omp parallel for
  for (int i = 0; i < scene.getW()*scene.getH(); ++i) {
    Ray ray;
    vec3 color;
    Sample sample;

    sampler.getSample(sample);
    scene.getCamera().generateRay(sample, &ray);
    raytracer.trace(ray, 0, &color);
    film.commit(sample, color);
  }
  //omp_destroy_lock(&lock);

  film.writeImage(scene.getFileName());

  return 0;
}
