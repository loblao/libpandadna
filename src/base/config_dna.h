#ifndef _H_DNA_CONFIG_
#define _H_DNA_CONFIG_

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <pandabase.h>
#include <dconfig.h>
#include <configVariableBool.h>
#include <configVariableInt.h>
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
extern ConfigVariableBool want_depth_offset_fix;
extern ConfigVariableBool want_door_fix;
extern void init_libpandadna();

#endif
