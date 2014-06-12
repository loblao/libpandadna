#pragma warning (disable: 4273)

// Define these constants for interrogate
#ifdef P3_INTERROGATE
#define WIN32
#define WIN32_VC
#define _WINDOWS
#endif

#include "dtool_config.h"
#undef DO_MEMORY_USAGE

#include "pandabase.h"

#ifndef DNABASE_H
#define DNABASE_H

#include <string>
#include <datagramIterator.h>
#include <lvector4.h>

inline std::string dgi_extract_string8(DatagramIterator& dgi)
{
	size_t s = dgi.get_uint8();
	std::string v = dgi.extract_bytes(s);
	return v;
};

inline LVector4f* dgi_extract_color(DatagramIterator& dgi)
{
	float r = dgi.get_uint8() / 255.0;
	float g = dgi.get_uint8() / 255.0;
	float b = dgi.get_uint8() / 255.0;
	float a = dgi.get_uint8() / 255.0;
	return new LVector4f(r, g, b, a);
};

#endif

#undef EXPCL_PANDASKEL
#define EXPCL_PANDASKEL
