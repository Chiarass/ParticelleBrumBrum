# Path definitions

include_guard(DIRECTORY)

set(PROGRAM_SOURCES ${CMAKE_SOURCE_DIR}/main/src)
set(PROGRAM_HEADERS ${CMAKE_SOURCE_DIR}/main/include/particles)
#set(PROGRAM_COMPONENTS ${CMAKE_SOURCE_DIR}/components)
set(PROGRAM_CODE_TEMPLATES ${CMAKE_SOURCE_DIR}/templates)
set(PROGRAM_TEST ${CMAKE_SOURCE_DIR}/tests) #?
set(PROGRAM_TEST_UNIT ${PROGRAM_TEST}/unit) #?

set(PROGRAM_NAMESPACE RootApplication)
set(PROGRAM_NAME "RootTemplate")
set(PROGRAM_ATTACH_CLING TRUE)
set(PROGRAM_USE_LOCAL_OWNERSHIP TRUE)

# Root config
# C++ std autodetection
set(CONFIG_AUTODETECT_ROOT_STD OFF)