# ParticelleBrumBrum

Particles project for unibo's physics course.
----
To build the program:

```
cmake -S ./ -B build/debug -DBUILD_TESTING=True -DCMAKE_BUILD_TYPE=Debug
```

Then:

```
cmake --build build/debug
```

To run the program:

```
build/debug/particles
```

To run the test:

```
build/debug/particles.t
```

To not build the test, set:

```
-DBUILD_TESTING=False
```
----
One can also build in release mode for better performance but it's not really necessary in this case