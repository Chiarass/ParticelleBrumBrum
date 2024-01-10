# High Energy Physics Simulator by Chiara Baldelli, Elisa Barilari, Alida Castagnoli, Ilaria Core from Unibo (Physics bachelor degree, Lab 2)

This project wants to simulate a detector observing the traces of the following particles:

1. Pion (with associated antiparticle)
2. Kaon (with associated antiparticle)
3. Proton (with associated antiparticle)

It also simulates the decay and resonance phenomenons of neutral Kaons by turning it into decay products. In order to start the program, please follow the instructions below.

In order to run it you need ROOT and a GUI on you terminal (You can install MobaXTerm). You also have to specify your ROOT path in Libraries.cmake file
----
**The program uses doctest.h and CMake to test/compile/debug/run. Actually on my pc CMake doesn't get to write/read .root files and I had to load manually libreries on root terminal. instructions for both ways are written below.**

To run the program in shell by using CMake (not recommended, your editor has easy buttons):

```
cmake -S ./ -B build/debug -DBUILD_TESTING=True -DCMAKE_BUILD_TYPE=Debug
```

Then:

```
cmake --build build/debug
```

To run the program:

```
build/debug/main/main.bin
```

To run the test:

```
build/debug/tests.t
```

To not build the test, set:

```
-DBUILD_TESTING=False
```
**One can also build in release mode for better performance.**
----
To run the program by using CMake and your editor (pay attention as I said):

1. In main/CMakeLists.txt select lines 10-13 
2. Press Compile button (in VScode it's bottom left)
3. Press Run botton (in VScode it's bottom left)
4. Select your executable (you can choice between main.bin and tests.t)
----
To run the program in shell by using ROOT terminal to execute:

1. In main/CMakeLists.txt select lines 15-18
2. Press Compile button
3. In main/CMakeLists.txt select lines 20-23
4. Press Compile button
5. Open you ROOT terminal INSIDE your working directory

Then:

```
.L ParticleType.cpp+
.L ResonanceType.cpp+
.L Particle.cpp+
.L Simulation.cpp+
.L Analysis.cpp+
```

Execute functions:

```
simulation()
analysis()
```

To open .root files:

```
TBrowser b
```

Then search your files and open them on canvas

**These instructions needs a GUI to work. If your linux distro doesn't have a default one you can set your display on MobaXTerm and run ROOT terminal there**
----
