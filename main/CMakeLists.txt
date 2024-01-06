#Configure main target
# Get program modules
include_guard(GLOBAL)
include(${CONFIG_BUILD_DIR}/ProgramModules.cmake)

set(PROGRAM_TARGET_MAIN main.bin)

# Register the executable
add_executable(${PROGRAM_TARGET_MAIN} ${PROGRAM_MODULES_MAIN})

target_include_directories(${PROGRAM_TARGET_MAIN} PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(${PROGRAM_TARGET_MAIN} ${PROGRAM_LIBRARIES_DEFAULT})

add_executable(da_debuggare src/ParticleType.cpp src/ResonanceType.cpp src/Particle.cpp src/Simulation.cpp)

target_include_directories(da_debuggare PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(da_debuggare ${PROGRAM_LIBRARIES_DEFAULT})

#Generate root dictionary
ROOT_GENERATE_DICTIONARY(main_dictionary
        #Add header files here
        MODULE ${PROGRAM_TARGET_MAIN}
        LINKDEF dictionary/Linkdef.h)