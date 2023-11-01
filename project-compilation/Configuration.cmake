#File to configure project source files
include_guard(GLOBAL)

#Process Headers.hpp.in
if(DEFINED PROGRAM_NAMESPACE AND
        DEFINED PROGRAM_NAME #AND
        #DEFINED PROGRAM_ATTACH_CLING AND
        #DEFINED PROGRAM_USE_LOCAL_OWNERSHIP
        )
    configure_file(${PROGRAM_CODE_TEMPLATES}/Headers.hpp.in
            ${PROGRAM_HEADERS}/Headers.hpp)
else()
    message(FATAL_ERROR "Missing application configuration variables!")
endif()