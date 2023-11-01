include_guard(GLOBAL)
include(${CONFIG_BUILD_DIR}/ProgramModules.cmake)

set(PROGRAM_TARGET_TEST_SAMPLE sample.t )

add_executable(${PROGRAM_TARGET_TEST_SAMPLE} sample.test.cpp) #add also equired program modules

# target_link_libraries#link needed libraries
target_include_directories(${PROGRAM_TARGET_TEST_SAMPLE}
                            PRIVATE ${PROGRAM_HEADERS})

#Generate root dictionary if needed

#Register test
add_test(NAME Sample COMMAND sample.t)