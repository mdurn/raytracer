raytracer
=========

A multi-threaded ray tracer with lighting and reflections built for Mac in C++.

## Compilation

```bash
make
```

* Compilation tested in Mac OSX Mountain Lion and Mavericks with g++-4.6.
  GCC 4.6 can be installed via homebrew (brew install gcc-4.6). Due to the
  dependencies, other compilers may fail.
* Issues may arise with an incompatible freeimage library. If this occurs, 
  install freeimage (brew install freeimage) and replace the libfreeimage.a file
  contained in the repository.

## Execution

Single thread:
```bash
raytrace input.scene
```

Multi-threaded ("$num_threads" may be replaced by an integer):
```bash
OMP_NUM_THREADS=$num_threads raytrace input.scene
```

* Example input files are located in "examples/input/".
* Output files will be written into the same directory as the input file as PNGs.
* Example output files are located in "examples/output/"

## Examples

* Examples of input text files can be found in examples/input
* Examples of output images can be found in examples/output
