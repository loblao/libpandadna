#pragma warning (disable: 4273)

// Define these constants for interrogate
#ifdef P3_INTERROGATE
#define WIN32
#define WIN32_VC
#define _WINDOWS
#endif

#include "dtool_config.h"
#undef DO_MEMORY_USAGE
#undef NDEBUG

#include "pandabase.h"
