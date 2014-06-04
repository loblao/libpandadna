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

#ifndef DNABASE_H
#define DNABASE_H

#include <string>
#include <datagramIterator.h>
inline std::string dgi_extract_string8(DatagramIterator& dgi)
{
	size_t s = dgi.get_uint8();
	std::string v = dgi.extract_bytes(s);
	return v;
};

#endif
