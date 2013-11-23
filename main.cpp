#include "Scene.h"
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_max_threads() 1
#define omp_get_thread_num() 0
#endif

int main(int argc, char* argv[]) {
  if (argc < 1) {
    cerr << "Usage: raytrace inputfile.test\n";
    exit(-1);
  }

  int maxThreads = omp_get_max_threads();

  cout << "Constructing Scene" << "\n";

  vector<Scene*> scenes;
  vector<RayTracer*> raytracers;
  for (int i = 0; i < maxThreads; i++ ) {
    Scene *scene = new Scene(argv[1]);
    scenes.push_back(scene);
    RayTracer* raytracer = new RayTracer(scenes[i]->getMaxDepth(),
      *(scenes.back()->getPrimitivesRef()),
      *(scenes.back()->getLightsRef()));
    raytracers.push_back(raytracer);
  }

  int w = scenes[0]->getW();
  int h = scenes[0]->getH();

  cout << "Finished Constructing Scene" << "\n";

  Sampler sampler = Sampler(w, h);
  Film film(w, h);

  cout << "Initialized RayTracer Variables" << "\n";

  #pragma omp parallel for
  for (int i = 0; i < w*h; ++i) {
    Ray ray;
    vec3 color;
    Sample sample;
    int threadNum = omp_get_thread_num();

    #pragma omp critical
    sampler.getSample(sample);

    scenes[threadNum]->getCamera().generateRay(sample, &ray);
    raytracers[threadNum]->trace(ray, 0, &color);

    #pragma omp critical
    film.commit(sample, color);
  }

  film.writeImage(scenes[0]->getFileName());

  return 0;
}
