#include "DNAWindows.h"

DNAWindows::DNAWindows(string name) : DNAGroup(name), m_color(new LVector4f(1)) {}
DNAWindows::~DNAWindows(void) {}

void DNAWindows::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNAGroup::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
	m_window_count = dgi.get_uint8();
};