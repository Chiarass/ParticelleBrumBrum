# Program modules configuration

include_guard(DIRECTORY)
 set(PROGRAM_MODULES_MAIN
        ${PROGRAM_SOURCES}/main.cpp
        ${PROGRAM_HEADERS}/Headers.hpp)

        set(PROGRAM_MODULES_PARTICLES_H
        ${PROGRAM_HEADERS}/Particle.hpp
        ${PROGRAM_HEADERS}/ParticleType.hpp
        ${PROGRAM_HEADERS}/ResonanceType.hpp)

        set(PROGRAM_MODULES_PARTICLES_SRC
        ${PROGRAM_SOURCES}/Particle.cpp
        ${PROGRAM_SOURCES}/ParticleType.cpp
        ${PROGRAM_SOURCES}/ResonanceType.cpp
        ${PROGRAM_SOURCES}/Simulation.cpp
        ${PROGRAM_SOURCES}/Analysis.cpp)
