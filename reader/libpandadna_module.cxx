
#include "dtoolbase.h"
#include "interrogate_request.h"

#undef _POSIX_C_SOURCE
#include "py_panda.h"

extern LibrayDef libpandadna_moddef ;
#ifdef _WIN32
extern "C" __declspec(dllexport) void initlibpandadna();
#else
extern "C" void initlibpandadna();
#endif

void initlibpandadna() 
{
  LibrayDef   *defs[] = {&libpandadna_moddef, NULL };
   Dtool_PyModuleInitHelper( defs, "libpandadna");



}
