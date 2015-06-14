#ifndef _H_DNA_CONFIG_
#define _H_DNA_CONFIG_

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <pandabase.h>
#include <notifyCategoryProxy.h>

#pragma warning (disable : 4273)
#pragma warning (disable : 4275)

#if (defined(WIN32_VC) || defined(WIN64_VC)) && !defined(CPPPARSER) && !defined(LINK_ALL_STATIC)
    #ifdef BUILDING_DNA
        #define EXPCL_DNA __declspec(dllexport)
        #define EXPTP_DNA
    #else
        #define EXPCL_DNA __declspec(dllimport)
        #define EXPTP_DNA extern
    #endif
#else
    #define EXPCL_DNA
    #define EXPTP_DNA
#endif

NotifyCategoryDecl(dna, EXPCL_DNA, EXPTP_DNA);
extern void init_libpandadna();

#endif
