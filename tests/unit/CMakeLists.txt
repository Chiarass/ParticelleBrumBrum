#
# Test Cmakelists
# Add targets then add the test (only if unit: GUI test shall not be added to commands)
#
include_guard(GLOBAL)
include(${CONFIG_BUILD_DIR}/ProgramModules.cmake)

set(PROGRAM_TARGET_TEST_SAMPLE particles.t )

add_executable(${PROGRAM_TARGET_TEST_SAMPLE} 
    particles.test.cpp  
    ${PROGRAM_ALL_HEADERS}
    ${PROGRAM_MODULES_PARTICLES_SRC}) #add also equired program modules

# target_link_libraries#link needed libraries
target_include_directories(${PROGRAM_TARGET_TEST_SAMPLE}
                            PRIVATE ${PROGRAM_HEADERS})

#Generate root dictionary if needed

#Register test
add_test(NAME ParticlePrint COMMAND particles.t)