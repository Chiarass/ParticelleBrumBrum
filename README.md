# High Energy Physics Simulator

This project wants to simulate a detector observing the traces of the following particles:

1. Pion (with associated antiparticle)
2. Kaon (with associated antiparticle)
3. Proton (with associated antiparticle)

It also simulates the decay and resonance phenomenons of neutral Kaons by turning it into decay products. In order to start the program, please follow the instructions below. 
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