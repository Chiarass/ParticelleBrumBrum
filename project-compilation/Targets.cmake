# Target configuration file

#Add subdirectories
add_subdirectory(${CMAKE_SOURCE_DIR}/main)

#Add tests
if(BUILD_TESTING)
    add_subdirectory(${PROGRAM_TEST_UNIT}/sample) #add example test
endif()