cmake_minimum_required(VERSION 3.16)
project(Root_template_project VERSION 0.0.1)

include(CTest)
# Specifica il compilatore C++
set(CMAKE_CXX_COMPILER g++-11)  # Imposta il compilatore su g++-11

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set config base path
set(CONFIG_BUILD_DIR ${CMAKE_SOURCE_DIR}/project-compilation)

# Config files
# Include configuration files
include(${CMAKE_SOURCE_DIR}/project-compilation/Setting.cmake)


# Compiler flags
# NOTE: must be placed after config as variables needed are defined there
include(${CONFIG_BUILD_DIR}/Flags.cmake)

#Libraries
include(${CONFIG_BUILD_DIR}/Libraries.cmake)

#Configure project files
include(${CONFIG_BUILD_DIR}/Configuration.cmake)

#Targets
#Include target configuration
include(${CONFIG_BUILD_DIR}/Targets.cmake)

