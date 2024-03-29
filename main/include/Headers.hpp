#ifndef ROOT_TEMPLATE_PROJECT_HEADERS_HPP
#define ROOT_TEMPLATE_PROJECT_HEADERS_HPP

//HEADER TO DEFINE MACROS FOR THE TEMPLATE CODE

//base namespace name for root application
#define BASE_NS RootApplication
#define APP_NAME "RootTemplate"
#define PROGRAM_ATTACH_CLING
#define PROGRAM_USE_LOCAL_OWNERSHIP

#ifdef PROGRAM_ATTACH_CLING
#define APP_TYPE TRint
#else
#define APP_TYPE TApplication
#endif

#endif //ROOT_TEMPLATE_PROJECT_HEADERS_HPP
