
#include "dtoolbase.h"
#include "interrogate_request.h"

#undef _POSIX_C_SOURCE
#include "py_panda.h"

extern LibraryDef base_moddef;
extern void Dtool_base_RegisterTypes();
extern void Dtool_base_ResolveExternals();
extern void Dtool_base_BuildInstants(PyObject *module);
extern LibraryDef components_moddef;
extern void Dtool_components_RegisterTypes();
extern void Dtool_components_ResolveExternals();
extern void Dtool_components_BuildInstants(PyObject *module);
extern LibraryDef suit_moddef;
extern void Dtool_suit_RegisterTypes();
extern void Dtool_suit_ResolveExternals();
extern void Dtool_suit_BuildInstants(PyObject *module);

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
  Dtool_base_RegisterTypes();
  Dtool_components_RegisterTypes();
  Dtool_suit_RegisterTypes();
  Dtool_base_ResolveExternals();
  Dtool_components_ResolveExternals();
  Dtool_suit_ResolveExternals();

  LibraryDef *defs[] = {&base_moddef, &components_moddef, &suit_moddef, NULL};

  PyObject *module = Dtool_PyModuleInitHelper(defs, &py_libpandadna_module);
  if (module != NULL) {
    Dtool_base_BuildInstants(module);
    Dtool_components_BuildInstants(module);
    Dtool_suit_BuildInstants(module);
  }
  return module;
}

#else  // Python 2 case

#ifdef _WIN32
extern "C" __declspec(dllexport) void initlibpandadna();
#else
extern "C" void initlibpandadna();
#endif

void initlibpandadna() {
  Dtool_base_RegisterTypes();
  Dtool_components_RegisterTypes();
  Dtool_suit_RegisterTypes();
  Dtool_base_ResolveExternals();
  Dtool_components_ResolveExternals();
  Dtool_suit_ResolveExternals();

  LibraryDef *defs[] = {&base_moddef, &components_moddef, &suit_moddef, NULL};

  PyObject *module = Dtool_PyModuleInitHelper(defs, "libpandadna");
  if (module != NULL) {
    Dtool_base_BuildInstants(module);
    Dtool_components_BuildInstants(module);
    Dtool_suit_BuildInstants(module);
  }
}
#endif

