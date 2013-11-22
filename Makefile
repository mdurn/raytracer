CC = g++-4.6
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -I./include/ -I/usr/X11/include -DOSX \
					 -I./glm-0.9.2.7
	LDFLAGS = -L./lib/mac/ -lm -lc++ -lfreeimage
else
	CFLAGS = -g -I./include/ -I/usr/X11R6/include -I/sw/include \
					 -I/usr/sww/include -I/usr/sww/pkg/Mesa/include \
					 -I./glm-0.9.2.7
	LDFLAGS = -L./lib/nix -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib \
						-L/usr/sww/bin -lX11 -lfreeimage
endif

RM = /bin/rm -f 

all: raytrace
raytrace: main.o Scene.o Ray.o LocalGeo.o Transform.o Sample.o Sampler.o Intersection.o Primitive.o Sphere.o Tri.o Trinormal.o Camera.o Light.o PointLight.o DirectionalLight.o RayTracer.o Film.o
	$(CC) $(CFLAGS) -fopenmp -o raytrace main.o Scene.o Ray.o LocalGeo.o Transform.o Sample.o Sampler.o Intersection.o Primitive.o Sphere.o Tri.o Trinormal.o Camera.o Light.o PointLight.o DirectionalLight.o RayTracer.o Film.o $(LDFLAGS)
main.o: main.cpp Scene.h definitions.h Ray.h LocalGeo.h Transform.h Sample.h Sampler.h Intersection.h Primitive.h Sphere.h Tri.h Trinormal.h Camera.h Light.h PointLight.h DirectionalLight.h RayTracer.h Film.h variables.h
	$(CC) $(CFLAGS) -fopenmp -c main.cpp
Scene.o: Scene.cpp Scene.h definitions.h Ray.h LocalGeo.h Transform.h Sample.h Sampler.h Intersection.h Primitive.h Sphere.h Tri.h Trinormal.h Camera.h Light.h PointLight.h DirectionalLight.h RayTracer.h Film.h variables.h
	$(CC) $(CFLAGS) -c Scene.cpp
RayTracer.o: RayTracer.cpp RayTracer.h Ray.h LocalGeo.h Intersection.h Primitive.h Sphere.h Tri.h Trinormal.h definitions.h
	$(CC) $(CFLAGS) -c RayTracer.cpp
PointLight.o: PointLight.cpp PointLight.h Light.h Ray.h LocalGeo.h
	$(CC) $(CFLAGS) -c PointLight.cpp
DirectionalLight.o: DirectionalLight.cpp DirectionalLight.h Light.h Ray.h LocalGeo.h
	$(CC) $(CFLAGS) -c DirectionalLight.cpp
Light.o: Light.cpp Light.h Ray.h LocalGeo.h
	$(CC) $(CFLAGS) -c Light.cpp
Trinormal.o: Trinormal.cpp Trinormal.h Tri.h Primitive.h Ray.h LocalGeo.h Intersection.h definitions.h
	$(CC) $(CFLAGS) -c Trinormal.cpp
Tri.o: Tri.cpp Tri.h Primitive.h Ray.h LocalGeo.h Intersection.h definitions.h
	$(CC) $(CFLAGS) -c Tri.cpp
Sphere.o: Sphere.cpp Sphere.h Primitive.h Ray.h LocalGeo.h Intersection.h definitions.h
	$(CC) $(CFLAGS) -c Sphere.cpp
Primitive.o: Primitive.cpp Primitive.h Ray.h LocalGeo.h Intersection.h definitions.h
	$(CC) $(CFLAGS) -c Primitive.cpp
Intersection.o: Intersection.cpp Intersection.h LocalGeo.h definitions.h
	$(CC) $(CFLAGS) -c Intersection.cpp
LocalGeo.o: LocalGeo.cpp LocalGeo.h definitions.h
	$(CC) $(CFLAGS) -c LocalGeo.cpp
Camera.o: Camera.cpp Camera.h Ray.h Sample.h definitions.h
	$(CC) $(CFLAGS) -c Camera.cpp
Film.o: Film.cpp Film.h Sample.h definitions.h
	$(CC) $(CFLAGS) -c Film.cpp
Sampler.o: Sampler.cpp Sampler.h Sample.h
	$(CC) $(CFLAGS) -c Sampler.cpp
Ray.o: Ray.cpp Ray.h definitions.h
	$(CC) $(CFLAGS) -c Ray.cpp
Sample.o: Sample.cpp Sample.h
	$(CC) $(CFLAGS) -c Sample.cpp
Transform.o: Transform.cpp Transform.h definitions.h
	$(CC) $(CFLAGS) -c Transform.cpp
clean: 
	$(RM) *.o raytrace *.png