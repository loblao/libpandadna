
#include "dtoolbase.h"
#include "interrogate_request.h"

#undef _POSIX_C_SOURCE
#include "py_panda.h"

IMPORT_THIS LibraryDef base_moddef;
IMPORT_THIS LibraryDef components_moddef;
IMPORT_THIS LibraryDef suit_moddef;

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef py_libpandadna_module = {
  PyModuleDef_HEAD_INIT,
  "libpandadna",
  NULL,
  -1,
  NULL,
  NULL, NULL, NULL, NULL
};

#ifdef _WIN32
extern "C" __declspec(dllexport) PyObject *PyInit_libpandadna();
#else
extern "C" PyObject *PyInit_libpandadna();
#endif

PyObject *PyInit_libpandadna() {
  LibraryDef *defs[] = {&base_moddef, &components_moddef, &suit_moddef, NULL};

  return Dtool_PyModuleInitHelper(defs, &py_libpandadna_module);
}

#else  // Python 2 case

#ifdef _WIN32
extern "C" __declspec(dllexport) void initlibpandadna();
#else
extern "C" void initlibpandadna();
#endif

void initlibpandadna() {
  LibraryDef *defs[] = {&base_moddef, &components_moddef, &suit_moddef, NULL};

  Dtool_PyModuleInitHelper(defs, "libpandadna");
}
#endif

