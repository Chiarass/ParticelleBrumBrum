include(CMakeListsCustom.txt)
include_directories(${ROOT_INCLUDE_DIRS})


cmake_minimum_required(VERSION 3.16)
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Tree MathCore Hist)
include(${ROOT_USE_FILE})

project(particles VERSION 0.1.0)

# Specifica il compilatore C++
set(CMAKE_CXX_COMPILER g++-11)  # Imposta il compilatore su g++-11

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

add_executable(particles ParticleType.cpp ResonanceType.cpp Particle.cpp main.cpp)

target_link_libraries(particles ${ROOT_LIBRARIES})

# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione

if (BUILD_TESTING)

  # aggiungi l'eseguibile boid.t
  add_executable(particles.t ParticleType.cpp ResonanceType.cpp particles.test.cpp)
  # aggiungi l'eseguibile boid.t alla lista dei test
  add_test(NAME particles.t COMMAND particles.t)


endif()