#ifndef _H_DNA_CONFIG_
#define _H_DNA_CONFIG_

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <pandabase.h>
#include <notifyCategoryProxy.h>

#pragma warning (disable : 4273)
#pragma warning (disable : 4275)

#ifdef BUILDING_DNA 
    #define EXPCL_DNA EXPORT_CLASS 
    #define EXPTP_DNA EXPORT_TEMPL 
#else 
   #define EXPCL_DNA IMPORT_CLASS 
   #define EXPTP_DNA IMPORT_TEMPL 
#endif 

NotifyCategoryDecl(dna, EXPCL_DNA, EXPTP_DNA);
extern void init_libpandadna();

#endif
